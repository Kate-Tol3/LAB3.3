#include "GUI.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

#include <vector>
#include <algorithm>
#include <array>
#include <string>
#include <optional>

#include "Person.h"
#include "../LAB3.3/Tasks/Cache.h"
#include "../LAB3.3/Tasks/Histogram.h"
#include "../LAB3.3/Sequence/MutableArraySequence.h"


PersonManagementApp::PersonManagementApp(QWidget* parent)
    : QWidget(parent), personCache(50, 50, "person_cache.txt") {
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Search bar
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchInput = new QLineEdit();
    searchInput->setPlaceholderText("Enter name or ID");
    searchButton = new QPushButton("Search");
    connect(searchButton, &QPushButton::clicked, this, &PersonManagementApp::searchPerson);
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);

    // Table to display persons
    personTable = new QTableWidget();
    personTable->setColumnCount(4);
    personTable->setHorizontalHeaderLabels({"First Name", "Last Name", "ID", "Birth Date"});

    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addPersonButton = new QPushButton("Add Person");
    deletePersonButton = new QPushButton("Delete Person");
    showHistogramButton = new QPushButton("Show Histograms");

    connect(addPersonButton, &QPushButton::clicked, this, &PersonManagementApp::addPerson);
    connect(deletePersonButton, &QPushButton::clicked, this, &PersonManagementApp::deletePerson);
    connect(showHistogramButton, &QPushButton::clicked, this, &PersonManagementApp::showHistograms);

    buttonLayout->addWidget(addPersonButton);
    buttonLayout->addWidget(deletePersonButton);
    buttonLayout->addWidget(showHistogramButton);

    // Add widgets to main layout
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(personTable);
    mainLayout->addLayout(buttonLayout);

    refreshTable();
    applyStyle();
}

void PersonManagementApp::refreshTable() {
    personTable->setRowCount(static_cast<int>(persons.getLength()));
    for (int i = 0; i < persons.getLength(); ++i) {
        const auto& person = persons[i];
        personTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(person.getFirstName())));
        personTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(person.getLastName())));
        personTable->setItem(i, 2, new QTableWidgetItem(QString::number(person.getID())));
        auto birthDate = person.getBirthDate();
        personTable->setItem(i, 3, new QTableWidgetItem(QString("%1/%2/%3").arg(birthDate[0]).arg(birthDate[1]).arg(birthDate[2])));
    }
}

void PersonManagementApp::addPerson() {
    bool ok;
    QString firstName = QInputDialog::getText(this, "Add Person", "Enter First Name:", QLineEdit::Normal, "", &ok);
    if (!ok || firstName.isEmpty()) return;

    QString lastName = QInputDialog::getText(this, "Add Person", "Enter Last Name:", QLineEdit::Normal, "", &ok);
    if (!ok || lastName.isEmpty()) return;

    int id = QInputDialog::getInt(this, "Add Person", "Enter ID:", 0, 0, 10000, 1, &ok);
    if (!ok) return;

    std::array<int, 3> birthDate;
    birthDate[0] = QInputDialog::getInt(this, "Add Person", "Enter Birth Day:", 1, 1, 31, 1, &ok);
    if (!ok) return;

    birthDate[1] = QInputDialog::getInt(this, "Add Person", "Enter Birth Month:", 1, 1, 12, 1, &ok);
    if (!ok) return;

    birthDate[2] = QInputDialog::getInt(this, "Add Person", "Enter Birth Year:", 1970, 1900, 2100, 1, &ok);
    if (!ok) return;

    Person newPerson(firstName.toStdString(), lastName.toStdString(), id, birthDate);
    persons.append(newPerson);
    personCache.put(id, newPerson);
    refreshTable();
}

void PersonManagementApp::deletePerson() {
    bool ok;
    int id = QInputDialog::getInt(this, "Delete Person", "Enter ID to delete:", 0, 0, 10000, 1, &ok);
    if (!ok) return;

    bool found = false;
    for (int i = 0; i < persons.getLength(); ++i) {
        if (persons[i].getID() == id) {
            persons.remove(i);
            found = true;
            break;
        }
    }

    if (found) {
        personCache.clear();
        for (int i = 0; i < persons.getLength(); ++i) {
            personCache.put(persons[i].getID(), persons[i]);
        }
        refreshTable();
    } else {
        QMessageBox::warning(this, "Error", "Person not found!");
    }
}

void PersonManagementApp::searchPerson() {
    QString searchText = searchInput->text();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a name or ID to search.");
        return;
    }

    bool ok;
    int id = searchText.toInt(&ok);
    std::optional<Person> result;

    if (ok) {
        result = personCache.get(id);
    } else {
        for (int i = 0; i < persons.getLength(); ++i) {
            const Person& person = persons[i];
            if (QString::fromStdString(person.getFirstName()).contains(searchText, Qt::CaseInsensitive) ||
                QString::fromStdString(person.getLastName()).contains(searchText, Qt::CaseInsensitive)) {
                result = person;
                break;
            }
        }
    }

    if (result.has_value()) {
        const auto& person = result.value();
        QMessageBox::information(this, "Person Found",
            QString("ID: %1\nName: %2 %3\nBirth Date: %4/%5/%6")
                .arg(person.getID())
                .arg(QString::fromStdString(person.getFirstName()))
                .arg(QString::fromStdString(person.getLastName()))
                .arg(person.getBirthDate()[0])
                .arg(person.getBirthDate()[1])
                .arg(person.getBirthDate()[2]));
    } else {
        QMessageBox::warning(this, "Not Found", "Person not found!");
    }
}

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>

void PersonManagementApp::showHistograms() {
    using Range = std::pair<int, int>;

    Range intervalArray[] = {{1950, 1980}, {1980, 2000}, {2000, 2020}};
    int intervalCount = sizeof(intervalArray) / sizeof(intervalArray[0]);

    MutableArraySequence<Range> intervals(intervalArray, intervalCount);

    auto birthYearExtractor = [](const Person& person) { return person.getBirthDate()[2]; };
    auto nameClassifier = [](const Person& person) { return person.getFirstName(); };

    Histogram<int, std::string, Person> histogram(persons, intervals, birthYearExtractor, nameClassifier);

    std::vector<int> counts(intervalCount, 0);
    for (int j = 0; j < persons.getLength(); ++j) { // Проходим по каждому элементу в persons
        const Person& person = persons[j];
        int birthYear = birthYearExtractor(person);
        for (int i = 0; i < intervalCount; ++i) {
            if (birthYear >= intervalArray[i].first && birthYear < intervalArray[i].second) {
                counts[i]++;
                break;
            }
        }
    }


    QBarSet* barSet = new QBarSet("Number of Persons");
    for (int count : counts) {
        *barSet << count;
    }

    QBarSeries* series = new QBarSeries();
    series->append(barSet);


    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Histogram of Birth Years");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (int i = 0; i < intervalCount; ++i) {
        categories << QString("%1-%2").arg(intervalArray[i].first).arg(intervalArray[i].second);
    }
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Count");
    axisY->setRange(0, *std::max_element(counts.begin(), counts.end()) + 1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Histogram");
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    layout->addWidget(chartView);
    dialog->resize(800, 600);
    dialog->exec();
}



void PersonManagementApp::applyStyle() {
    // Устанавливаем стили для приложения
    QString styleSheet = R"(
        QWidget {
            background-color: #f5faff;
            color: #2c3e50;
        }

        QLineEdit {
            border: 2px solid #3498db;
            border-radius: 8px;
            padding: 4px;
            background-color: #ffffff;
        }

        QPushButton {
            background-color: #3498db;
            color: white;
            border: 2px solid #2980b9;
            border-radius: 10px;
            padding: 6px;
            font-size: 14px;
        }

        QPushButton:hover {
            background-color: #5dade2;
            border: 2px solid #3498db;
        }

        QPushButton:pressed {
            background-color: #2980b9;
        }

        QTableWidget {
            border: 1px solid #3498db;
            gridline-color: #3498db;
            background-color: #ffffff;
            selection-background-color: #aed6f1;
            selection-color: #2c3e50;
        }

        QHeaderView::section {
            background-color: #5dade2;
            color: white;
            padding: 4px;
            border: 1px solid #3498db;
        }

        QDialog {
            background-color: #f5faff;
            border: 2px solid #3498db;
            border-radius: 10px;
        }
    )";

    this->setStyleSheet(styleSheet);
}

int runApplication(int argc, char* argv[]) {
    QApplication app(argc, argv);

    PersonManagementApp window;
    window.setWindowTitle("Person Management");
    window.resize(800, 600);
    window.show();

    return app.exec();
}
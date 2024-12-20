#ifndef PERSONMANAGEMENTAPP_H
#define PERSONMANAGEMENTAPP_H

#include <QWidget>
#include <QTableWidget>
#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include "../LAB3.3/Tasks/Cache.h"
#include "../LAB3.3/Tasks/Histogram.h"
#include "Person.h"

class PersonManagementApp : public QWidget {
    Q_OBJECT

private:
    Cache<int, Person> personCache;
    MutableArraySequence<Person> persons;

    QTableWidget* personTable{};
    QLineEdit* searchInput{};
    QPushButton* searchButton{};
    QPushButton* addPersonButton{};
    QPushButton* deletePersonButton{};
    QPushButton* showHistogramButton{};

    void refreshTable();

public:
    PersonManagementApp(QWidget* parent = nullptr);

    private slots:
        void addPerson();
    void deletePerson();
    void searchPerson();
    void showHistograms();
    void applyStyle();
};

int runApplication(int argc, char* argv[]);


#endif // PERSONMANAGEMENTAPP_H


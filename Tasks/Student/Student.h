#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <array>
#include <ostream>
#include <stdexcept>

class Date {
public:
    int date[3]; // date[0] - день, date[1] - месяц, date[2] - год

    explicit Date(int d = 1, int m = 1, int y = 2000) {
        date[0] = d;
        date[1] = m;
        date[2] = y;
    }

    explicit Date(const std::array<int, 3>& dateArray) {
        for (int i = 0; i < 3; i++) {
            date[i] = dateArray[i];
        }
    }

    const int operator[](int index) const {
        if (index < 0 || index >= 3) throw std::out_of_range("index is out of range");
        return date[index];
    }

    int& operator[](int index) {
        if (index < 0 || index >= 3) throw std::out_of_range("index is out of range");
        return date[index];
    }

    bool operator<(const Date& other) const {
        if (date[2] != other.date[2]) {
            return date[2] < other.date[2];
        } else if (date[1] != other.date[1]) {
            return date[1] < other.date[1];
        } else {
            return date[0] < other.date[0];
        }
    }

    bool operator>(const Date& other) const {
        if (date[2] != other.date[2]) {
            return date[2] > other.date[2];
        } else if (date[1] != other.date[1]) {
            return date[1] > other.date[1];
        } else {
            return date[0] > other.date[0];
        }
    }

    friend std::istream& operator>>(std::istream& is, Date& date);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    static bool isValidDate(int day, int month, int year);
};

class Person {
private:
    std::string first_name;
    std::string last_name;
    Date birth_date;
    int ID;

public:
    Person();
    Person(const std::string& firstName, const std::string& lastName, int id, const std::array<int, 3>& dateArray);
    Person(const Person& other);

    virtual ~Person();

    const std::string getFirstName() const { return first_name; }
    const std::string getLastName() const { return last_name; }
    int getID() const { return ID; }
    const Date getBirthDate() const { return birth_date; }

    Person& operator=(const Person& other);
    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

class Student : public Person {
private:
    int enrollment_year;
    std::string group;

public:
    Student();
    Student(const std::string& firstName, const std::string& lastName, int id, const std::array<int, 3>& dateArray, int year, const std::string& group);
    Student(const Student& other);
    Student& operator=(const Student& other);

    int getEnrollmentYear() const { return enrollment_year; }
    const std::string getGroup() const { return group; }

    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

// Экстракторы для использования с гистограммами
int enrollmentYearExtractor(const Student& s); // Экстрактор для года поступления
std::string groupExtractor(const Student& s);  // Экстрактор для группы
int ageExtractor(const Student& s);            // Экстрактор для возраста
std::string lastNameExtractor(const Student& s); // Экстрактор для фамилии

#endif // STUDENT_H

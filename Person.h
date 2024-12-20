#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <array>
#include <iostream>

class Person {
private:
    std::string firstName;
    std::string lastName;
    int id;
    std::array<int, 3> birthDate; // День, месяц, год рождения

public:
    // Конструкторы
    Person() : id(0), birthDate({1, 1, 1970}) {}
    Person(const std::string& firstName, const std::string& lastName, int id, const std::array<int, 3>& birthDate)
        : firstName(firstName), lastName(lastName), id(id), birthDate(birthDate) {}

    // Геттеры
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    int getID() const { return id; }
    std::array<int, 3> getBirthDate() const { return birthDate; }

    // Сеттеры
    void setFirstName(const std::string& firstName) { this->firstName = firstName; }
    void setLastName(const std::string& lastName) { this->lastName = lastName; }
    void setID(int id) { this->id = id; }
    void setBirthDate(const std::array<int, 3>& birthDate) { this->birthDate = birthDate; }

    // Перегрузка операторов
    bool operator==(const Person& other) const { return id == other.id; }
    bool operator!=(const Person& other) const { return !(*this == other); }

    // Вывод информации о человеке
    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "ID: " << person.id
           << ", Name: " << person.firstName << " " << person.lastName
           << ", Birth Date: " << person.birthDate[0] << "/" << person.birthDate[1] << "/" << person.birthDate[2];
        return os;
    }
};

#endif // PERSON_H

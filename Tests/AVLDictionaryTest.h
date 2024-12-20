#pragma once

#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../Basic_Structures/AVLDictionary.h"
#include <stdexcept>
#include <vector>


// Класс для подготовки данных для тестов
class AVLDictionaryTest : public ::testing::Test {
protected:
    AVLDictionary<int, std::string> dict;

    // Метод, который выполняется перед каждым тестом
    void SetUp() override {
        dict.add(1, "One");
        dict.add(2, "Two");
        dict.add(3, "Three");
    }
};

#pragma once

#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../Basic_Structures/AVLDictionary.h"
#include <stdexcept>
#include <vector>


// Класс для подготовки данных для тестов
class AVLDictionaryTest : public ::testing::Test {
protected:
    AVLDictionary<int, std::string> dict;

    void SetUp() override {
        dict.insert(1, "One");
        dict.insert(2, "Two");
        dict.insert(3, "Three");
    }
};

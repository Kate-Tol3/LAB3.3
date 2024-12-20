#pragma once

#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../Tasks/Histogram.h"
#include "../Sequence/MutableArraySequence.h"
#include "../Tasks/Student/Student.h"

// Тестовые структуры
struct SampleClass {
    int value;
    char category;
    SampleClass() : value(0), category('c') {};

    SampleClass(int v, char c) : value(v), category(c) {}
    // Перегрузка оператора << для SampleClass
    friend std::ostream& operator<<(std::ostream& os, const SampleClass& obj) {
        os << "(" << obj.value << ", " << obj.category << ")";
        return os;
    }
};

using HistogramType = Histogram<int, char, SampleClass>;

class HistogramTest : public ::testing::Test {
protected:
    // Это будет выполнено перед каждым тестом
    void SetUp() override {}

    // Это будет выполнено после каждого теста
    void TearDown() override {}
};


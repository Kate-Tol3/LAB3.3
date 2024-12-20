#pragma once

#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../Tasks/Histogram.h"
#include "../Sequence/MutableArraySequence.h"


struct SampleClass {
    int value;
    char category;
    SampleClass() : value(0), category('c') {};

    SampleClass(int v, char c) : value(v), category(c) {}

    friend std::ostream& operator<<(std::ostream& os, const SampleClass& obj) {
        os << "(" << obj.value << ", " << obj.category << ")";
        return os;
    }
};

using HistogramType = Histogram<int, char, SampleClass>;

class HistogramTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};


#ifndef CACHE_TEST_H
#define CACHE_TEST_H

#include "gtest/gtest.h"
#include "../Tasks/Cache.h" // Путь к вашему файлу Cache.h

// Тесты для кеша
class CacheTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Код для инициализации перед каждым тестом
    }

    void TearDown() override {
        // Код для очистки после каждого теста
    }
};

#endif // CACHE_TEST_H

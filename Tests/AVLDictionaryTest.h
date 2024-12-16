//
// Created by Kate on 07.12.2024.
//

#ifndef AVLDICTIONARYTEST_H
#define AVLDICTIONARYTEST_H



// #include <gtest/gtest.h>
#include "../Basic Stuctures/AVLDictionary.h"

// // Тестовые ключи и значения
// using KeyType = int;
// using ValueType = std::string;
//
// // Тестирование конструктора по умолчанию
// TEST(AVLDictionaryTest, DefaultConstructor) {
//     AVLDictionary<KeyType, ValueType> dict;
//     EXPECT_EQ(dict.getCount(), 0); // Проверка начального количества элементов
//     EXPECT_EQ(dict.getCapacity(), 0); // Ёмкость равна количеству элементов в AVL-дереве
// }
//
// // Тестирование добавления элементов
// TEST(AVLDictionaryTest, AddElements) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//     dict.add(2, "Two");
//     dict.add(3, "Three");
//
//     EXPECT_EQ(dict.getCount(), 3); // Проверка количества элементов
//     EXPECT_TRUE(dict.containsKey(1));
//     EXPECT_TRUE(dict.containsKey(2));
//     EXPECT_TRUE(dict.containsKey(3));
// }
//
// // Тестирование получения значений по ключу
// TEST(AVLDictionaryTest, GetElements) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(10, "Ten");
//     dict.add(20, "Twenty");
//
//     EXPECT_EQ(dict.get(10), "Ten");
//     EXPECT_EQ(dict.get(20), "Twenty");
//
//     // Проверка на выбрасывание исключения при отсутствии ключа
//     EXPECT_THROW(dict.get(30), std::runtime_error);
// }
//
// // Тестирование наличия ключей
// TEST(AVLDictionaryTest, ContainsKey) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(5, "Five");
//
//     EXPECT_TRUE(dict.containsKey(5));
//     EXPECT_FALSE(dict.containsKey(10));
// }
//
// // Тестирование удаления элементов
// TEST(AVLDictionaryTest, RemoveElements) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//     dict.add(2, "Two");
//     dict.add(3, "Three");
//
//     EXPECT_TRUE(dict.containsKey(2));
//
//     dict.remove(2);
//
//     EXPECT_FALSE(dict.containsKey(2));
//     EXPECT_EQ(dict.getCount(), 2); // Проверка количества элементов после удаления
// }
//
// // Тестирование итератора
// TEST(AVLDictionaryTest, IteratorTest) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//     dict.add(2, "Two");
//     dict.add(3, "Three");
//
//     int count = 0;
//     for (auto it = dict.begin(); it != dict.end(); ++it) {
//         count++;
//     }
//
//     EXPECT_EQ(count, 3); // Проверка, что итератор обошёл все элементы
// }
//
// // Тестирование на дублирующиеся ключи
// TEST(AVLDictionaryTest, DuplicateKeys) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//     EXPECT_THROW(dict.add(1, "Duplicate"), std::runtime_error); // Предполагаемое исключение на дубликат
// }
//
// // Тестирование удаления несуществующего элемента
// TEST(AVLDictionaryTest, RemoveNonExistingKey) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//
//     EXPECT_THROW(dict.remove(2), std::runtime_error); // Удаление несуществующего ключа
// }
//
// // Тестирование на пустой словарь
// TEST(AVLDictionaryTest, EmptyDictionary) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     EXPECT_EQ(dict.getCount(), 0);
//     EXPECT_FALSE(dict.containsKey(1));
//
//     EXPECT_THROW(dict.get(1), std::runtime_error);
//     EXPECT_THROW(dict.remove(1), std::runtime_error);
// }
//
// // Тестирование большого количества элементов
// TEST(AVLDictionaryTest, LargeNumberOfElements) {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     const int numElements = 1000;
//     for (int i = 0; i < numElements; ++i) {
//         dict.add(i, "Value" + std::to_string(i));
//     }
//
//     EXPECT_EQ(dict.getCount(), numElements);
//
//     for (int i = 0; i < numElements; ++i) {
//         EXPECT_TRUE(dict.containsKey(i));
//         EXPECT_EQ(dict.get(i), "Value" + std::to_string(i));
//     }
// }
//



#include <cassert>
#include <iostream>

using KeyType = int;
using ValueType = std::string;

void testDefaultConstructor() {
    AVLDictionary<KeyType, ValueType> dict;

    assert(dict.getCount() == 0);
    assert(dict.getCapacity() == 0);
    std::cout << "testDefaultConstructor passed.\n";
}

void testAddElements() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(1, "One");
    dict.add(2, "Two");
    dict.add(3, "Three");

    assert(dict.getCount() == 3);
    assert(dict.containsKey(1));
    assert(dict.containsKey(2));
    assert(dict.containsKey(3));

    std::cout << "testAddElements passed.\n";
}

void testGetElements() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(10, "Ten");
    dict.add(20, "Twenty");

    assert(dict.get(10) == "Ten");
    assert(dict.get(20) == "Twenty");

    try {
        dict.get(30);
        assert(false); // Не должно достигаться
    } catch (const std::runtime_error&) {
        // Ожидаем исключение
    }

    std::cout << "testGetElements passed.\n";
}

void testContainsKey() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(5, "Five");

    assert(dict.containsKey(5));
    assert(!dict.containsKey(10));

    std::cout << "testContainsKey passed.\n";
}

void testRemoveElements() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(1, "One");
    dict.add(2, "Two");
    dict.add(3, "Three");

    assert(dict.containsKey(2));
    dict.remove(2);
    assert(!dict.containsKey(2));
    assert(dict.getCount() == 2);

    std::cout << "testRemoveElements passed.\n";
}

// void testIterator() {
//     AVLDictionary<KeyType, ValueType> dict;
//
//     dict.add(1, "One");
//     dict.add(2, "Two");
//     dict.add(3, "Three");
//
//     int count = 0;
//     for (auto it = dict.begin(); it != dict.end(); ++it) {
//         count++;
//     }
//
//     assert(count == 3);
//     std::cout << "testIterator passed.\n";
// }

void testDuplicateKeys() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(1, "One");
    try {
        dict.add(1, "Duplicate");
        assert(false); // Должно выбросить исключение
    } catch (const std::runtime_error&) {
        // Ожидаем исключение
    }

    std::cout << "testDuplicateKeys passed.\n";
}

void testRemoveNonExistingKey() {
    AVLDictionary<KeyType, ValueType> dict;

    dict.add(1, "One");

    try {
        dict.remove(2);
        assert(false); // Должно выбросить исключение
    } catch (const std::runtime_error&) {
        // Ожидаем исключение
    }

    std::cout << "testRemoveNonExistingKey passed.\n";
}

void testEmptyDictionary() {
    AVLDictionary<KeyType, ValueType> dict;

    assert(dict.getCount() == 0);
    assert(!dict.containsKey(1));

    try {
        dict.get(1);
        assert(false);
    } catch (const std::runtime_error&) {
    }

    try {
        dict.remove(1);
        assert(false);
    } catch (const std::runtime_error&) {
    }

    std::cout << "testEmptyDictionary passed.\n";
}

void testLargeNumberOfElements() {
    AVLDictionary<KeyType, ValueType> dict;

    const int numElements = 1000;
    for (int i = 0; i < numElements; ++i) {
        dict.add(i, "Value" + std::to_string(i));
    }

    assert(dict.getCount() == numElements);

    for (int i = 0; i < numElements; ++i) {
        assert(dict.containsKey(i));
        assert(dict.get(i) == "Value" + std::to_string(i));
    }

    std::cout << "testLargeNumberOfElements passed.\n";
}

int test() {
    std::cout << "Running AVLDictionary tests...\n";

    testDefaultConstructor();
    testAddElements();
    testGetElements();
    testContainsKey();
    testRemoveElements();
   // testIterator();
    testDuplicateKeys();
    testRemoveNonExistingKey();
    testEmptyDictionary();
    testLargeNumberOfElements();

    std::cout << "All tests passed successfully!\n";

}


#endif //AVLDICTIONARYTEST_H



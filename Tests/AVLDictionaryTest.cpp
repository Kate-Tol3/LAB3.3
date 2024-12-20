#include "AVLDictionaryTest.h"

TEST_F(AVLDictionaryTest, TestAddAndGet) {

    // Проверяем, что элементы были добавлены и их можно получить
    EXPECT_EQ(dict.get(1), "One");
    EXPECT_EQ(dict.get(2), "Two");
    EXPECT_EQ(dict.get(3), "Three");

    // Проверяем, что исключение выбрасывается при отсутствии ключа
    EXPECT_THROW(dict.get(4), std::runtime_error);  // Ключ 4 отсутствует
}


TEST_F(AVLDictionaryTest, TestGetKeyNotFound) {
    // Проверяем, что выбрасывается исключение, если ключа нет в словаре
    EXPECT_THROW(dict.get(4), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestContainsKey) {
    // Проверяем, что метод containsKey работает правильно
    EXPECT_TRUE(dict.containsKey(1));
    EXPECT_TRUE(dict.containsKey(2));
    EXPECT_TRUE(dict.containsKey(3));
    EXPECT_FALSE(dict.containsKey(4));  // Ключа 4 нет
}

TEST_F(AVLDictionaryTest, TestAddExistingKey) {
    // Проверяем, что не получится добавить элемент с уже существующим ключом
    EXPECT_THROW(dict.insert(1, "OneAgain"), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestRemove) {
    // Проверяем, что удаление работает корректно
    dict.remove(2);
    EXPECT_FALSE(dict.containsKey(2));  // Ключ 2 должен быть удален

    // Убедимся, что другие элементы не затронуты
    EXPECT_TRUE(dict.containsKey(1));
    EXPECT_TRUE(dict.containsKey(3));
}

TEST_F(AVLDictionaryTest, TestRemoveKeyNotFound) {
    // Проверяем, что удаление несуществующего ключа вызывает исключение
    EXPECT_THROW(dict.remove(4), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestGetKeys) {
    // Проверяем метод получения всех ключей
    MutableArraySequence<int> keys = dict.getKeys();
    EXPECT_EQ(keys.getLength(), 3);  // Должно быть 3 ключа
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}

TEST_F(AVLDictionaryTest, TestGetValues) {
    // Проверяем метод получения всех значений
    MutableArraySequence<std::string> values = dict.getValues();
    EXPECT_EQ(values.getLength(), 3);  // Должно быть 3 значения
    EXPECT_EQ(values[0], "One");
    EXPECT_EQ(values[1], "Two");
    EXPECT_EQ(values[2], "Three");
}

TEST_F(AVLDictionaryTest, TestIterator) {
    // Проверяем итератор
    std::vector<std::string> expectedValues = {"One", "Two", "Three"};
    int index = 0;
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        EXPECT_EQ(it->element, expectedValues[index]);
        ++index;
    }
}

TEST_F(AVLDictionaryTest, TestIteratorEquality) {
    // Проверяем операторы сравнения итераторов
    auto it1 = dict.begin();
    auto it2 = dict.begin();
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AVLDictionaryTest, TestIteratorIncrement) {
    // Проверяем инкремент итераторов
    auto it = dict.begin();
    EXPECT_EQ(it->element, "One");
    ++it;
    EXPECT_EQ(it->element, "Two");
    ++it;
    EXPECT_EQ(it->element, "Three");
}

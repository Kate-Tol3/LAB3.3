#include "AVLDictionaryTest.h"

TEST_F(AVLDictionaryTest, TestAddAndGet) {

    EXPECT_EQ(dict.get(1), "One");
    EXPECT_EQ(dict.get(2), "Two");
    EXPECT_EQ(dict.get(3), "Three");

    EXPECT_THROW(dict.get(4), std::runtime_error);
}


TEST_F(AVLDictionaryTest, TestGetKeyNotFound) {
    EXPECT_THROW(dict.get(4), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestContainsKey) {
    EXPECT_TRUE(dict.containsKey(1));
    EXPECT_TRUE(dict.containsKey(2));
    EXPECT_TRUE(dict.containsKey(3));
    EXPECT_FALSE(dict.containsKey(4));
}

TEST_F(AVLDictionaryTest, TestAddExistingKey) {
    EXPECT_THROW(dict.insert(1, "OneAgain"), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestRemove) {
    dict.remove(2);
    EXPECT_FALSE(dict.containsKey(2));
    EXPECT_TRUE(dict.containsKey(1));
    EXPECT_TRUE(dict.containsKey(3));
}

TEST_F(AVLDictionaryTest, TestRemoveKeyNotFound) {
    EXPECT_THROW(dict.remove(4), std::runtime_error);
}

TEST_F(AVLDictionaryTest, TestGetKeys) {
    MutableArraySequence<int> keys = dict.getKeys();
    EXPECT_EQ(keys.getLength(), 3);  // Должно быть 3 ключа
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}

TEST_F(AVLDictionaryTest, TestGetValues) {
    MutableArraySequence<std::string> values = dict.getValues();
    EXPECT_EQ(values.getLength(), 3);  // Должно быть 3 значения
    EXPECT_EQ(values[0], "One");
    EXPECT_EQ(values[1], "Two");
    EXPECT_EQ(values[2], "Three");
}

TEST_F(AVLDictionaryTest, TestIterator) {
    std::vector<std::string> expectedValues = {"One", "Two", "Three"};
    int index = 0;
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        EXPECT_EQ(it->element, expectedValues[index]);
        ++index;
    }
}

TEST_F(AVLDictionaryTest, TestIteratorEquality) {
    auto it1 = dict.begin();
    auto it2 = dict.begin();
    EXPECT_TRUE(it1 == it2);

    ++it2;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);
}

TEST_F(AVLDictionaryTest, TestIteratorIncrement) {
    auto it = dict.begin();
    EXPECT_EQ(it->element, "One");
    ++it;
    EXPECT_EQ(it->element, "Two");
    ++it;
    EXPECT_EQ(it->element, "Three");
}

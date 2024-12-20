#include "CacheTest.h"


TEST_F(CacheTest, AddAndRetrieveElements) {
    Cache<int, std::string> cache(5, 3, "../Tests/cache_test.txt");

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    ASSERT_EQ(cache.get(1).value_or("not found"), "one");
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");
    ASSERT_EQ(cache.get(3).value_or("not found"), "three");

    // Проверка отсутствующих элементов
    ASSERT_EQ(cache.get(4).has_value(), false);
}

TEST_F(CacheTest, EvictFromSet) {
    Cache<int, std::string> cache(3, 2, "../Tests/cache_test.txt");

    // Добавление элементов больше, чем `maxSetSize`
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    cache.put(4, "four"); // Превышает размер

    ASSERT_EQ(cache.get(1).has_value(), false);
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");
    ASSERT_EQ(cache.get(4).value_or("not found"), "four");
}

TEST_F(CacheTest, PromoteToCache) {
    Cache<int, std::string> cache(3, 2, "../Tests/cache_test.txt");

    cache.put(1, "one");
    cache.put(2, "two");

    // Перемещение элемента в `cache`
    ASSERT_EQ(cache.get(1).value_or("not found"), "one");
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");
    cache.put(3, "three");
    ASSERT_EQ(cache.get(3).value_or("not found"), "three");

    // Проверка, что первый элемент был удален из `cache`
    ASSERT_EQ(cache.get(1).has_value(),false);
}


TEST_F(CacheTest, SaveAndLoadFromDisk) {
    Cache<int, std::string> cache(5, 3, "../Tests/cache_test.txt");

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    cache.saveToDisk();

    Cache<int, std::string> loadedCache(5, 3, "../Tests/cache_test.txt");

    loadedCache.loadFromDisk();

    ASSERT_EQ(loadedCache.get(1).value_or("not found"), "one");
    ASSERT_EQ(loadedCache.get(2).value_or("not found"), "two");
    ASSERT_EQ(loadedCache.get(3).value_or("not found"), "three");
}

TEST_F(CacheTest, ClearCache) {
    Cache<int, std::string> cache(5, 3, "cache_test.txt");

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    cache.clear();

    ASSERT_EQ(cache.get(1).has_value(), false);
    ASSERT_EQ(cache.get(2).has_value(), false);
    ASSERT_EQ(cache.get(3).has_value(), false);
}
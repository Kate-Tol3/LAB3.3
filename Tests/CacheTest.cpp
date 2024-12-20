#include "CacheTest.h"

// Тест 1: Проверка добавления и получения элементов
TEST_F(CacheTest, AddAndRetrieveElements) {
    Cache<int, std::string> cache(5, 3, "../Tests/cache_test.txt");

    // Добавление элементов
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    // Проверка получения
    ASSERT_EQ(cache.get(1).value_or("not found"), "one");
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");
    ASSERT_EQ(cache.get(3).value_or("not found"), "three");

    // Проверка отсутствующих элементов
    ASSERT_EQ(cache.get(4).has_value(), false);
}

// Тест 2: Проверка удаления старых элементов из `dataSet`
TEST_F(CacheTest, EvictFromSet) {
    Cache<int, std::string> cache(3, 2, "../Tests/cache_test.txt");

    // Добавление элементов больше, чем `maxSetSize`
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    cache.put(4, "four"); // Превышает размер

    // Элемент с ключом 1 должен быть удален
    ASSERT_EQ(cache.get(1).has_value(), false);
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");
    ASSERT_EQ(cache.get(4).value_or("not found"), "four");
}

// Тест 3: Перемещение элемента в `cache`
TEST_F(CacheTest, PromoteToCache) {
    Cache<int, std::string> cache(3, 2, "../Tests/cache_test.txt");

    // Добавление элементов
    cache.put(1, "one");
    cache.put(2, "two");

    // Перемещение элемента в `cache`
    ASSERT_EQ(cache.get(1).value_or("not found"), "one");
    ASSERT_EQ(cache.get(2).value_or("not found"), "two");

    // Проверяем, что элемент находится в `cache` и очередь работает
    cache.put(3, "three");
    ASSERT_EQ(cache.get(3).value_or("not found"), "three");

    // Проверка, что первый элемент был удален из `cache`
    cache.put(4, "four");
    ASSERT_EQ(cache.get(1).has_value(), false);
}

// Тест 4: Сохранение и загрузка с диска
TEST_F(CacheTest, SaveAndLoadFromDisk) {
    Cache<int, std::string> cache(5, 3, "../Tests/cache_test.txt");

    // Добавление элементов
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    // Сохранение на диск
    cache.saveToDisk();

    // Создание нового кеша и загрузка данных с диска
    Cache<int, std::string> loadedCache(5, 3, "../Tests/cache_test.txt");
    loadedCache.loadFromDisk();

    // Проверка значений после загрузки
    ASSERT_EQ(loadedCache.get(1).value_or("not found"), "one");
    ASSERT_EQ(loadedCache.get(2).value_or("not found"), "two");
    ASSERT_EQ(loadedCache.get(3).value_or("not found"), "three");
}

// Тест 5: Очистка кеша
TEST_F(CacheTest, ClearCache) {
    Cache<int, std::string> cache(5, 3, "cache_test.txt");

    // Добавление элементов
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    // Очистка кеша
    cache.clear();

    // Проверка, что все данные удалены
    ASSERT_EQ(cache.get(1).has_value(), false);
    ASSERT_EQ(cache.get(2).has_value(), false);
    ASSERT_EQ(cache.get(3).has_value(), false);
}

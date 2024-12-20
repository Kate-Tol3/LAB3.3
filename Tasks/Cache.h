#ifndef CACHE_H
#define CACHE_H

#include <fstream>
#include <optional>
#include <string>
#include <iostream>
#include "../Basic_Structures/AVLDictionary.h"
#include "../Basic_Structures/AVLSet.h"
#include "../Basic_Structures/Queue.h"

template <typename TKey, typename TValue>
class Cache {
private:
    AVLSet<Pair<TKey, TValue>> dataSet;    // Основное хранилище кеша (парами)
    AVLDictionary<TKey, TValue> cache;      // Часто запрашиваемые данные
    Queue<TKey> queue;                      // Очередь для управления порядком
    int maxSetSize;                         // Максимальный размер для AVLSet
    int maxCacheSize;                       // Максимальный размер для AVLDictionary
    std::string diskFilePath;               // Путь к файлу для хранения кеша на диске

    // Метод для удаления самого старого элемента из dataSet
    void evictFromSet() {
        if (dataSet.size() == 0) return;

        auto oldest = *dataSet.begin();
        dataSet.erase(oldest);
    }

    // Метод для перемещения элемента из dataSet в cache
    void promoteToCache(const TKey& key) {
        // Ищем элемент в dataSet

        for (const auto& pair : dataSet) {
            if (pair.key == key) {
                TValue value = pair.element;

                dataSet.erase(pair);

                // Если кеш переполнен, удаляем старый элемент из cache и очереди
                if (cache.getCount() >= maxCacheSize) {
                    auto removedKey = queue.front();
                    cache.remove(removedKey);
                    queue.dequeue();
                }

                // Добавляем элемент в кеш и в очередь
                cache.insert(key, value);
                queue.enqueue(key);
                return;
            }
        }

        std::cout << "Key not found in dataSet: " << key << std::endl;
    }

public:
    explicit Cache(int maxSetSize = 100, int maxCacheSize = 100, const std::string& filePath = "../cache.txt")
        : maxSetSize(maxSetSize), maxCacheSize(maxCacheSize), diskFilePath(filePath), queue(maxCacheSize) {}


    void put(const TKey& key, const TValue& value) {
        // Если ключ уже существует в cache, обновляем его значение
        if (cache.containsKey(key)) {
            cache.set(key, value);
            return;
        }
        // Проверяем, существует ли ключ в dataSet
        for (auto it = dataSet.begin(); it != dataSet.end(); ++it) {
            if (it->key == key) {
                dataSet.erase(*it); // Удаляем старую запись из dataSet
                break;
            }
        }

        // Если dataSet переполнен, удаляем самый старый элемент
        if (dataSet.size() >= maxSetSize) {
            evictFromSet();
        }

        dataSet.insert(Pair<TKey, TValue>(key, value));
    }

    // Метод для получения элемента из кеша
    std::optional<TValue> get(const TKey& key) {
        // Если ключ в cache, возвращаем его
        if (cache.containsKey(key)) {
            return cache.get(key);;
        }

        // Если ключ в dataSet, перемещаем его в cache
        for (const auto& pair : dataSet) {
            if (pair.key == key) {
                promoteToCache(key);
                return cache.get(key);
            }
        }

        // Если элемент не найден, возвращаем пустой optional
        return std::nullopt;
    }

    // Метод для сохранения кеша на диск
    void saveToDisk() {
        std::ofstream file(diskFilePath, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи кеша");
        }

        // Сохраняем элементы из dataSet
        for (const auto& pair : dataSet) {
            file << pair.key << " " << pair.element << "\n";
        }

        // Сохраняем элементы из cache
        for (auto it = cache.begin(); it != cache.end(); ++it) {
            file << it->key << " " << it->element << "\n";
        }

        file.close();
    }

    // Метод для загрузки кеша с диска
    void loadFromDisk() {
        std::ifstream file(diskFilePath, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения кеша");
        }

        TKey key;
        TValue value;
        while (file >> key >> value) {
            put(key, value);
        }

        file.close();
    }

    // Метод для очистки кеша
    void clear() {
        dataSet.clear();
        cache.clear();
        queue.clear();
    }
};

#endif // CACHE_H

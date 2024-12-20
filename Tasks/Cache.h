#ifndef CACHE_H
#define CACHE_H

#include <fstream>
#include <optional>
#include <sstream>
#include <string>
#include "../Basic_Structures/AVLDictionary.h"
#include "../Basic_Structures/AVLSet.h"
#include "../Basic_Structures/Queue.h"

template <typename Key, typename Value>
class Cache {
private:
    AVLSet<Pair<Key, Value>> dataSet; // Основное хранилище кеша (парами)
    AVLDictionary<Key, Value> cache; // Часто запрашиваемые данные
    Queue<Key> queue;                // Очередь для управления порядком
    int maxSetSize;                  // Максимальный размер для AVLSet
    int maxCacheSize;                // Максимальный размер для AVLDictionary
    std::string diskFilePath;        // Путь к файлу для хранения кеша на диске

    // Удаление самого старого элемента из dataSet
    void evictFromSet() {
        if (dataSet.size() == 0) return;

        auto oldest = *dataSet.begin();
        dataSet.erase(oldest);
    }

    // Перемещение элемента из dataSet в cache
    void promoteToCache(const Key& key) {
        auto it = std::find_if(dataSet.begin(), dataSet.end(), [&](const auto& pair) {
            return pair.key == key;
        });

        if (it != dataSet.end()) {
            Value value = it->element;

            dataSet.erase(*it);
            if (cache.getCount() >= maxCacheSize) {
                cache.remove(queue.front()); // удалили старый элемент из кеша
                queue.dequeue();
            }
            cache.insert(key, value);
            queue.enqueue(key);
        }
    }

public:
    explicit Cache(int maxSetSize = 100, int maxCacheSize = 100, const std::string& filePath = "../cache.txt")
        : maxSetSize(maxSetSize), maxCacheSize(maxCacheSize), diskFilePath(filePath), queue(maxCacheSize) {}


    void put(const Key& key, const Value& value) {
        // Если ключ уже есть в cache
        if (cache.containsKey(key)) {
            cache.set(key, value);
            return;
        }

        // Если ключ уже есть в cache dataSet
        auto it = std::find_if(dataSet.begin(), dataSet.end(), [&](const auto& pair) {
            return pair.key == key;
        });

        if (it != dataSet.end()) {
            dataSet.erase(*it);
        }

        // если превысили размер удаляем самый старый элемент
        if (dataSet.size() >= maxSetSize) {
            evictFromSet();
        }

        dataSet.insert(Pair<Key, Value>(key, value));
    }


    std::optional<Value> get(const Key& key) {
        // Если ключ в cache
        if (cache.containsKey(key)) {
            return cache.get(key);
        }

        // Если ключ в dataSet перемещаем его в cache
        auto it = std::find_if(dataSet.begin(), dataSet.end(), [&](const auto& pair) {
            return pair.key == key;
        });

        if (it != dataSet.end()) {
            promoteToCache(key);
            return it->element;
        }

        return std::nullopt; // Элемент не найден
    }

    void saveToDisk() {
        std::ofstream file(diskFilePath, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для записи кеша");
        }

        for (const auto& pair : dataSet) {
            file << pair.key << " " << pair.element << "\n";
        }

        for (auto it = cache.begin(); it != cache.end(); ++it) {
            file << it->key << " " << it->element << "\n";
        }

        file.close();
    }

    void loadFromDisk() {
        std::ifstream file(diskFilePath, std::ios::in);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл для чтения кеша");
        }

        Key key;
        Value value;
        while (file >> key >> value) {
            put(key, value);
        }

        file.close();
    }

    void clear() {
        dataSet.clear();
        cache.clear();
        queue.clear();
    }
};

#endif // CACHE_H

#pragma once
#include "../Basic Stuctures/AVLDictionary.h"


template <typename TData, typename TKey = int, typename TElement = int>
class Histogram {
private:
    std::function<TKey(const TData&)> keyExtractor;  // Функция для извлечения ключа
    MutableArraySequence<std::pair<TKey, TKey>> intervals;    // Интервалы для гистограммы
    AVLDictionary<TKey, TElement> dictionary;        // Словарь для хранения гистограммы

public:
    Histogram(const MutableArraySequence<std::pair<TKey, TKey>>& intervals,
              std::function<TKey(const TData&)> keyExtractor)
        : intervals(intervals), keyExtractor(keyExtractor) {}

    void addData(const TData& data) {
        TKey key = keyExtractor(data);
        for (int i = 0; i < intervals.getLength(); i++) {
            if (key >= intervals[i].first && key < intervals[i].second) {
                if (dictionary.containsKey(intervals[i].first)) {
                    dictionary.add(intervals[i].first, dictionary.get(intervals[i].first) + 1);
                } else {
                    dictionary.add(intervals[i].first, 1);
                }
                return;
            }
        }
        throw std::out_of_range("Data does not fit into any defined interval.");
    }

    void removeData(const TData& data) {
        TKey key = keyExtractor(data);
        for (const auto& interval : intervals) {
            if (key >= interval.first && key < interval.second) {
                if (dictionary.containsKey(interval.first)) {
                    TElement currentCount = dictionary.get(interval.first);
                    if (currentCount > 1) {
                        dictionary.add(interval.first, currentCount - 1);
                    } else {
                        dictionary.remove(interval.first);
                    }
                }
                return;
            }
        }
        throw std::out_of_range("Data does not fit into any interval.");
    }

    void printHistogram() const {
        for (int i =0 ; i < intervals.getLength(); i++) {
            if (dictionary.containsKey(intervals[i].first)) {
                std::cout << "[" << intervals[i].first << ", " << intervals[i].second << "): "
                          << dictionary.get(intervals[i].first) << std::endl;
            } else {
                std::cout << "[" << intervals[i].first << ", " << intervals[i].second << "): 0" << std::endl;
            }
        }
    }

};

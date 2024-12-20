#pragma once
#include <functional>
#include <optional>
#include <iostream>
#include "../Basic_Structures/AVLDictionary.h"
#include "../Sequence/MutableArraySequence.h"  // Для работы с последовательностями

template <typename TInfo, typename ClassType, typename Class>
class Histogram {

public:
    struct Info {
        int count = 0;  // количество элементов в классе
        TInfo sum = TInfo();  // сумма значений для этого класса
        std::optional<TInfo> min;
        std::optional<TInfo> max;
        MutableArraySequence<TInfo> elements;  // последовательность значений для этого класса

        // Обновление информации о классе
        void update(const TInfo& value) {
            count++;
            sum += value;
            if (!min || value < *min) min = value;
            if (!max || value > *max) max = value;
            elements.append(value);
        }
    };

private:
    using Range = std::pair<TInfo, TInfo>;
    using Criteria = std::function<TInfo(const Class&)>;  // Функция для извлечения значения для статистики
    using Classifier = std::function<ClassType(const Class&)>;  // Функция для классификации

    AVLDictionary<Range, AVLDictionary<ClassType, Info>> histogram;  // Гистограмма: ключ - диапазон значений, значение - словарь с элементами и информацией о них
    Criteria criteria;  // Функция для извлечения значения для разбиения по диапазону
    Classifier classifier;  // Функция для классификации внутри диапазона

    // Построение гистограммы
    void buildHistogram(const MutableArraySequence<Class>& sequence) {
        int sequenceLength = sequence.getLength();

        // Проходим по каждому элементу последовательности
        for (int i = 0; i < sequenceLength; ++i) {
            const Class& item = sequence[i];
            TInfo value = criteria(item);
            ClassType className = classifier(item);

            bool found = false;
            // Проходим по диапазонам и ищем подходящий
            int rangeCount = histogram.getKeys().getLength();
            for (int j = 0; j < rangeCount; ++j) {
                const auto& range = histogram.getKeys().get(j);
                if (value >= range.first && value < range.second) {  // Если значение в диапазоне
                    auto& classInfo = histogram.getReference(range);
                    if (!classInfo.containsKey(className)) {
                        classInfo.add(className, Info{});
                    }
                    classInfo.getReference(className).update(value);
                    found = true;
                    break;
                }
            }

            // Если значение не попало в какой-либо диапазон, выводим предупреждение
            if (!found) {
                std::cerr << "Warning: Value " << value << " does not fit into any defined range!" << std::endl;
            }
        }
    }

public:

    Histogram(const MutableArraySequence<Class>& sequence, const MutableArraySequence<Range>& intervals, Criteria criteria, Classifier classifier)
        : criteria(criteria), classifier(classifier) {

        int intervalsLength = intervals.getLength();

        // Добавляем диапазоны в гистограмму
        for (int i = 0; i < intervalsLength; ++i) {
            histogram.add(intervals[i], AVLDictionary<ClassType, Info>());
        }

        // Строим гистограмму
        buildHistogram(sequence);
    }

    // Получить гистограмму
    const AVLDictionary<Range, AVLDictionary<ClassType, Info>>& getHistogram() const {
        return histogram;
    }

    // Печать гистограммы
    void printHistogram() const {
        int rangeCount = histogram.getKeys().getLength();

        // Проходим по каждому диапазону
        for (int i = 0; i < rangeCount; ++i) {
            const auto& range = histogram.getKeys().get(i);
            const auto& classInfo = histogram.getReference(range);

            // Получаем количество групп (class keys)
            int classCount = classInfo.getKeys().getLength();

            // Проходим по каждой группе
            for (int j = 0; j < classCount; ++j) {
                const auto& classStat = classInfo.getKeys().get(j);
                const auto& info = classInfo.getReference(classStat);

                // Печатаем информацию о диапазоне и классе
                std::cout << "Range: [" << range.first << ", " << range.second << "), Class: "
                          << classStat << ", Count: " << info.count << ", Sum: " << info.sum;

                // Печать Min и Max, если они существуют
                if (info.min.has_value()) {
                    std::cout << ", Min: " << *info.min;
                } else {
                    std::cout << ", Min: N/A";  // Если Min не существует
                }

                if (info.max.has_value()) {
                    std::cout << ", Max: " << *info.max;
                } else {
                    std::cout << ", Max: N/A";  // Если Max не существует
                }

                std::cout << std::endl;
            }
        }
    }


};

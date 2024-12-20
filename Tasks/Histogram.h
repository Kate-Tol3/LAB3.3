#pragma once
#include <functional>
#include <optional>
#include <iostream>
#include "../Basic_Structures/AVLDictionary.h"
#include "../Sequence/MutableArraySequence.h"  // Для работы с последовательностями
#include <utility>

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    os << "[" << p.first << ", " << p.second << ")";
    return os;
}

template <typename TInfo>
std::istream& operator>>(std::istream& is, std::pair<TInfo, TInfo>& p) {
    char delimiter;
    is >> delimiter;
    if (delimiter != '[') {
        is.setstate(std::ios::failbit);
        return is;
    }

    is >> p.first;

    is >> delimiter;
    if (delimiter != ',') {
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> p.second;

    is >> delimiter;
    if (delimiter != ']') {
        is.setstate(std::ios::failbit);
    }

    return is;
}


template <typename TInfo, typename ClassType, typename Class>
class Histogram {

public:
    struct Info {
        int count = 0;  // количество элементов
        TInfo sum = TInfo();  // сумма значений
        std::optional<TInfo> min;
        std::optional<TInfo> max;
        MutableArraySequence<TInfo> elements;

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
    using Criteria = std::function<TInfo(const Class&)>;
    using Classifier = std::function<ClassType(const Class&)>;

    AVLDictionary<Range, AVLDictionary<ClassType, Info>> histogram;  // Гистограмма: ключ - диапазон значений, значение - словарь с элементами и информацией о них
    Criteria criteria;  // Функция для извлечения значения для разбиения по диапазону
    Classifier classifier;  // Функция для классификации внутри диапазона


    void buildHistogram(const MutableArraySequence<Class>& sequence) {
        int sequenceLength = sequence.getLength();

        for (int i = 0; i < sequenceLength; ++i) {
            const Class& item = sequence[i];
            TInfo value = criteria(item);
            ClassType className = classifier(item);

            bool found = false;
            int rangeCount = histogram.getKeys().getLength();
            for (int j = 0; j < rangeCount; ++j) {
                const auto& range = histogram.getKeys().get(j);
                if (value >= range.first && value < range.second) {  // если значение в диапазоне
                    auto& classInfo = histogram.getReference(range);
                    if (!classInfo.containsKey(className)) {
                        classInfo.insert(className, Info{});
                    }
                    classInfo.getReference(className).update(value);
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cerr << "Warning: Value " << value << " does not fit into any defined range!" << std::endl;
            }
        }
    }

public:

    Histogram(const MutableArraySequence<Class>& sequence, const MutableArraySequence<Range>& intervals, Criteria criteria, Classifier classifier)
        : criteria(criteria), classifier(classifier) {

        int intervalsLength = intervals.getLength();

        for (int i = 0; i < intervalsLength; ++i) {
            histogram.insert(intervals[i], AVLDictionary<ClassType, Info>());
        }

        buildHistogram(sequence);
    }

    const AVLDictionary<Range, AVLDictionary<ClassType, Info>>& getHistogram() const {
        return histogram;
    }

    void printHistogram() const {
        int rangeCount = histogram.getKeys().getLength();

        for (int i = 0; i < rangeCount; ++i) {
            const auto& range = histogram.getKeys().get(i);
            const auto& classInfo = histogram.getReference(range);

            // Получаем количество групп (class keys)
            int classCount = classInfo.getKeys().getLength();

            for (int j = 0; j < classCount; ++j) {
                const auto& classStat = classInfo.getKeys().get(j);
                const auto& info = classInfo.getReference(classStat);

                // Печатаем информацию о диапазоне и классе
                std::cout << "Range: " << range << ", Class: "
                          << classStat << ", Count: " << info.count << ", Sum: " << info.sum;

                // Печать Min и Max
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

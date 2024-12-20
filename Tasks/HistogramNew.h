// #pragma once
// #include <functional>
// #include <optional>
// #include <iostream>
// #include "../Basic Structures/AVLDictionary.h"
// #include "../Sequence/MutableArraySequence.h"  // Для работы с последовательностями
//
// template <typename TInfo, typename ClassType, typename Class>
// class Histogram {
//
// public:
//     struct Info {
//         int count = 0; // количество элементов в классе.
//         TInfo sum = TInfo(); //сумма значений для этого класса.
//         std::optional<TInfo> min;
//         std::optional<TInfo> max;
//         MutableArraySequence<TInfo> elements; //последовательность значений для этого класса.
//
//         void update(const TInfo& value) {
//             count++;
//             sum += value;
//             if (!min || value < *min) min = value;
//             if (!max || value > *max) max = value;
//             elements.append(value);
//         }
//     };
//
// private:
//     using Range = std::pair<TInfo, TInfo>;
//     using Criteria = std::function<TInfo(const Class&)>;  // Функция для извлечения значения для статистики
//     using Classifier = std::function<ClassType(const Class&)>;  // Функция для классификации
//
//     AVLDictionary<Range, AVLDictionary<ClassType, Info>> histogram;  // Гистограмма: ключ - диапазон значений, значение - словарь с элементами и информацией о них
//     Criteria criteria;  // Функция для извлечения значения для разбиения по диапазону
//     Classifier classifier;  // Функция для классификации внутри диапазона
//
//     // Построение гистограммы
//     void buildHistogram(const MutableArraySequence<Class>& sequence) {
//         for (int i = 0; i < sequence.getLength(); ++i) {
//             const Class& item = sequence[i];
//             TInfo value = criteria(item);
//             ClassType className = classifier(item);
//
//             for (const auto& range : histogram.getKeys()) {
//                 if (value >= range.first && value < range.second) { // в интервале
//                     auto& classInfo = histogram.getReference(range);
//                     if (!classInfo.containsKey(className)) {
//                         classInfo.add(className, Info{});
//                     }
//                     classInfo.getReference(className).update(value);
//                     break;
//                 }
//             }
//         }
//     }
//
// public:
//
//     Histogram(const MutableArraySequence<Class>& sequence, const MutableArraySequence<Range>& intervals, Criteria criteria, Classifier classifier)
//         : criteria(criteria), classifier(classifier) {
//
//         for (int i = 0; i < intervals.getLength(); ++i) {
//             histogram.add(intervals[i], AVLDictionary<ClassType, Info>());
//         }
//
//         buildHistogram(sequence);
//     }
//
//     // Получить гистограмму
//     const AVLDictionary<Range, AVLDictionary<ClassType, Info>>& getHistogram() const {
//         return histogram;
//     }
//
//     // Добавить данные в гистограмму
//     void addData(const Class& item) {
//         TInfo value = criteria(item);
//         ClassType className = classifier(item);
//
//         for (const auto& range : histogram.getKeys()) {
//             if (value >= range.first && value < range.second) {
//                 auto& classInfo = histogram.getReference(range);
//                 if (!classInfo.containsKey(className)) {
//                     classInfo.add(className, Info{});
//                 }
//                 classInfo.getReference(className).update(value);
//                 return;
//             }
//         }
//         throw std::out_of_range("Data does not fit into any defined range.");
//     }
//
//     // Удалить данные из гистограммы
//     void removeData(const Class& item) {
//         TInfo value = criteria(item);
//         ClassType className = classifier(item);
//
//         for (const auto& range : histogram.getKeys()) {
//             if (value >= range.first && value < range.second) {
//                 auto& classInfo = histogram.getReference(range);
//                 if (classInfo.containsKey(className)) {
//                     auto& Info = classInfo.getReference(className);
//                     Info.count--;
//                     Info.sum -= value;
//                     Info.elements.remove(value);
//                     if (Info.count == 0) { // Если после удаления статистика для класса становится равной нулю, то класс удаляется из гистограммы.
//                         classInfo.remove(className);
//                     }
//                 }
//                 return;
//             }
//         }
//         throw std::out_of_range("Data does not fit into any defined range.");
//     }
//
//     // Печать гистограммы
//     void printHistogram() const {
//         for (const auto& range : histogram.getKeys()) {
//             const auto& classInfo = histogram.getReference(range);
//             for (const auto& classStat : classInfo.getKeys()) {
//                 const auto& Info = classInfo.getReference(classStat);
//                 std::cout << "Range: [" << range.first << ", " << range.second << "), Class: "
//                           << classStat << ", Count: " << Info.count << ", Sum: " << Info.sum
//                           << ", Min: " << (Info.min ? *Info.min : TInfo())  // Проверка на наличие значения
//                           << ", Max: " << (Info.max ? *Info.max : TInfo())  // Проверка на наличие значения
//                           << std::endl;
//             }
//         }
//     }
// };
//








// #pragma once
// #include <functional>
// #include <optional>
// #include <iostream>
// #include "../Basic Structures/AVLDictionary.h"
// #include "../Sequence/MutableArraySequence.h"  // Для работы с последовательностями
//
//
//
//
// template <typename TInfo, typename ClassType, typename Class>
// class Histogram {
//
// public:
//     struct Info {
//         int count = 0; // количество элементов в классе.
//         TInfo sum = TInfo(); //сумма значений для этого класса.
//         std::optional<TInfo> min;
//         std::optional<TInfo> max;
//         MutableArraySequence<TInfo> elements; //последовательность значений для этого класса.
//
//         void update(const TInfo& value) {
//             count++;
//             sum += value;
//             if (!min || value < *min) min = value;
//             if (!max || value > *max) max = value;
//             elements.append(value);
//         }
//     };
//
// private:
//     using Range = std::pair<TInfo, TInfo>;
//     using Criteria = std::function<T(const Class&)>;  // Функция для извлечения значения для статистики
//     using Classifier = std::function<ClassType(const Class&)>;  // Функция для классификации
//
//
//     AVLDictionary<Range, AVLDictionary<ClassType, Info>> histogram;  // Гистограмма: ключ - диапазон значений, значение - словарь с элементами и информацией о них
//     Criteria criteria;  // Функция для извлечения значения для разбиения по диапазону
//     Classifier classifier;  // Функция для классификации внутри диапазона
//
//
//     // Построение гистограммы
//     void buildHistogram(const MutableArraySequence<Class>& sequence) {
//         for (int i = 0; i < sequence.getLength(); ++i) {
//             const Class& item = sequence[i];
//             TInfo value = criteria(item);
//             ClassType className = classifier(item);
//
//             for (const auto& range : histogram.getKeys()) {
//                 if (value >= range.first && value < range.second) { // в инетрвале
//                     auto& classInfo = histogram.get(range);
//                     if (!classInfo.containsKey(className)) {
//                         classInfo.add(className, Info{});
//                     }
//                     classInfo.get(className).update(value);
//                     break;
//                 }
//             }
//         }
//     }
//
//
// public:
//
//     Histogram(const MutableArraySequence<Class>& sequence, const MutableArraySequence<Range>& intervals, Criteria criteria, Classifier classifier)
//         : criteria(criteria), classifier(classifier) {
//
//         for (int i = 0; i < intervals.getLength(); ++i) {
//             histogram.add(intervals[i], AVLDictionary<ClassType, Info>());
//         }
//
//         buildHistogram(sequence);
//     }
//
//     // Получить гистограмму
//     const AVLDictionary<Range, AVLDictionary<ClassType, Info>>& getHistogram() const {
//         return histogram;
//     }
//
//     // Добавить данные в гистограмму
//     void addData(const Class& item) {
//         TInfo value = criteria(item);
//         ClassType className = classifier(item);
//
//         for (const auto& range : histogram.getKeys()) {
//             if (value >= range.first && value < range.second) {
//                 auto& classInfo = histogram.get(range);
//                 if (!classInfo.containsKey(className)) {
//                     classInfo.add(className, Info{});
//                 }
//                 classInfo.get(className).update(value);
//                 return;
//             }
//         }
//         throw std::out_of_range("Data does not fit into any defined range.");
//     }
//
//     // Удалить данные из гистограммы
//     void removeData(const Class& item) {
//         TInfo value = criteria(item);
//         ClassType className = classifier(item);
//
//         for (const auto& range : histogram.getKeys()) {
//             if (value >= range.first && value < range.second) {
//                 auto& classInfo = histogram.get(range);
//                 if (classInfo.containsKey(className)) {
//                     auto& Info = classInfo.get(className);
//                     Info.count--;
//                     Info.sum -= value;
//                     Info.elements.remove(value);
//                     if (Info.count == 0) { // Если после удаления статистика для класса становится равной нулю, то класс удаляется из гистограммы.
//                         classInfo.remove(className);
//                     }
//                 }
//                 return;
//             }
//         }
//         throw std::out_of_range("Data does not fit into any defined range.");
//     }
//
//
//     // Печать гистограммы
//     void printHistogram() const {
//         for (const auto& range : histogram.getKeys()) {
//             const auto& classInfo = histogram.get(range);
//             for (const auto& classStat : classInfo.getKeys()) {
//                 const auto& Info = classInfo.get(classStat);
//                 std::cout << "Range: [" << range.first << ", " << range.second << "), Class: "
//                           << classStat << ", Count: " << Info.count << ", Sum: " << Info.sum
//                           << ", Min: " << *Info.min << ", Max: " << *Info.max << std::endl;
//             }
//         }
//     }
//
//
//
// };




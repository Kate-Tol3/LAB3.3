#include "HistogramTest.h"
#include <sstream>

// Тест 1: Проверка, что гистограмма правильно строится по заданным данным
TEST_F(HistogramTest, BuildHistogram) {
    // Массив SampleClass
    SampleClass data[] = {
        SampleClass(10, 'A'),
        SampleClass(20, 'B'),
        SampleClass(30, 'A'),
        SampleClass(15, 'A'),
        SampleClass(25, 'B'),
        SampleClass(35, 'C')
    };

    // Интервалы для гистограммы
    std::pair<int, int> intervals[] = {
        {0, 20},  // Диапазон 1
        {20, 40}  // Диапазон 2
    };

    // Критерии и классификация
    auto criteria = [](const SampleClass& item) { return item.value; };
    auto classifier = [](const SampleClass& item) { return item.category; };

    // Создаём объект гистограммы
    MutableArraySequence<SampleClass> sequence(data, 6);  // Массив из 6 элементов
    MutableArraySequence<std::pair<int, int>> intervalSequence(intervals, 2);  // 2 интервала

    HistogramType histogram(sequence, intervalSequence, criteria, classifier);

    // Проверяем, что гистограмма была построена корректно
    const auto& hist = histogram.getHistogram();

    // Проверяем диапазоны и классы
    ASSERT_EQ(hist.getCount(), 2);  // Два диапазона

    auto range1 = hist.getKeys().get(0);
    auto range2 = hist.getKeys().get(1);

    // Проверяем, что в первом диапазоне есть элементы
    const auto& classInfo1 = hist.getReference(range1);
    ASSERT_EQ(classInfo1.getCount(), 1);

    // Проверяем второй диапазон
    const auto& classInfo2 = hist.getReference(range2);
    ASSERT_EQ(classInfo2.getCount(), 3);
}

// Тест 2: Проверка правильности работы update в структуре Info (сумма, минимум, максимум, количество)
TEST_F(HistogramTest, InfoUpdate) {
    HistogramType::Info info;

    info.update(10);
    ASSERT_EQ(info.count, 1);
    ASSERT_EQ(info.sum, 10);
    ASSERT_EQ(info.min, 10);
    ASSERT_EQ(info.max, 10);

    info.update(20);
    ASSERT_EQ(info.count, 2);
    ASSERT_EQ(info.sum, 30);
    ASSERT_EQ(info.min, 10);
    ASSERT_EQ(info.max, 20);

    info.update(5);
    ASSERT_EQ(info.count, 3);
    ASSERT_EQ(info.sum, 35);
    ASSERT_EQ(info.min, 5);
    ASSERT_EQ(info.max, 20);
}

// Тест 3: Проверка правильности печати гистограммы
TEST_F(HistogramTest, PrintHistogram) {
    // Массив SampleClass
    SampleClass data[] = {
        SampleClass(10, 'A'),
        SampleClass(20, 'B'),
        SampleClass(30, 'A'),
        SampleClass(15, 'A'),
        SampleClass(25, 'B'),
        SampleClass(35, 'C')
    };

    // Интервалы для гистограммы
    std::pair<int, int> intervals[] = {
        {0, 20},
        {20, 40}
    };

    // Критерии и классификация
    auto criteria = [](const SampleClass& item) { return item.value; };
    auto classifier = [](const SampleClass& item) { return item.category; };

    // Создаём объект гистограммы
    MutableArraySequence<SampleClass> sequence(data, 6);  // Массив из 6 элементов
    MutableArraySequence<std::pair<int, int>> intervalSequence(intervals, 2);  // 2 интервала

    HistogramType histogram(sequence, intervalSequence, criteria, classifier);

    // Перенаправляем вывод в строку
    std::stringstream ss;
    std::streambuf* oldBuf = std::cout.rdbuf(ss.rdbuf());

    histogram.printHistogram();

    std::cout.rdbuf(oldBuf);  // Восстанавливаем вывод

    // Проверяем, что гистограмма напечатана корректно
    std::string output = ss.str();
    std::cout << "Generated Output:\n" << output << std::endl;  // Отладочный вывод

    ASSERT_NE(output.find("Range: [0, 20)"), std::string::npos);  // Проверка наличия диапазона
    ASSERT_NE(output.find("Class: A"), std::string::npos);  // Проверка наличия класса
    ASSERT_NE(output.find("Count: 2"), std::string::npos);  // Проверка правильного подсчёта
    ASSERT_NE(output.find("Sum: 45"), std::string::npos);  // Проверка правильной суммы
}


// Тест 4: Проверка пустой гистограммы
TEST_F(HistogramTest, EmptyHistogram) {
    // Пустой массив SampleClass
    SampleClass emptyData[] = {};

    // Интервалы для гистограммы
    std::pair<int, int> intervals[] = {
        {0, 10},
        {10, 20}
    };

    // Критерии и классификация
    auto criteria = [](const SampleClass& item) { return item.value; };
    auto classifier = [](const SampleClass& item) { return item.category; };

    // Создаём объект гистограммы
    MutableArraySequence<SampleClass> emptySequence(emptyData, 0);  // Пустой массив
    MutableArraySequence<std::pair<int, int>> intervalSequence(intervals, 2);  // 2 интервала

    HistogramType histogram(emptySequence, intervalSequence, criteria, classifier);

    const auto& hist = histogram.getHistogram();
    ASSERT_EQ(hist.getCount(), 2);  // Должны быть два диапазона

    for (int i = 0; i < hist.getCount(); ++i) {
        const auto& range = hist.getKeys().get(i);
        const auto& classInfo = hist.getReference(range);
        ASSERT_EQ(classInfo.getCount(), 0);  // В каждом диапазоне должны быть нулевые классы
    }
}

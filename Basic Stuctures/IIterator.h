//
// Created by Kate on 07.12.2024.
//

#ifndef IITERATOR_H
#define IITERATOR_H


// Интерфейс для итераторов
template <typename TElement>
class IIterator {
public:
    virtual ~IIterator() = default;

    // Получение текущего элемента
    virtual TElement getCurrentItem() const = 0;

    // Проверка, есть ли следующий элемент
    virtual bool hasNext() const = 0;

    // Переход к следующему элементу
    virtual bool next() = 0;

    // Попытка получения текущего элемента
    virtual bool tryGetCurrentItem(TElement& element) const = 0;
};


#endif //IITERATOR_H

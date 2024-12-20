#ifndef QUEUE_H
#define QUEUE_H

#include "../Sequence/DynamicArray.h"

template <typename T>
class Queue {
private:
    DynamicArray<T> array; // Динамический массив для хранения данных
    int frontIndex; // Индекс начала очереди
    int backIndex; // Индекс конца очереди
    int currentSize;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        DynamicArray<T> newArray(newCapacity);

        for (int i = 0; i < currentSize; ++i) {
            newArray[i] = array[(frontIndex + i) % capacity];
        }

        array = newArray;
        frontIndex = 0;
        backIndex = currentSize - 1;
        capacity = newCapacity;
    }

public:
    explicit Queue(int initialCapacity = 10)
        : array(initialCapacity), frontIndex(0), backIndex(-1), currentSize(0), capacity(initialCapacity) {}

    // Добавление элемента в конец очереди
    void enqueue(const T& value) {
        if (currentSize == capacity) {
            resize();
        }
        backIndex = (backIndex + 1) % capacity;
        array[backIndex] = value;
        currentSize++;
    }

    // Удаление элемента из начала очереди
    void dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста. Невозможно удалить элемент.");
        }
        frontIndex = (frontIndex + 1) % capacity;
        currentSize--;
    }

    // Получение элемента из начала очереди
    T& front() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста. Невозможно получить элемент.");
        }
        return array[frontIndex];
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пуста. Невозможно получить элемент.");
        }
        return array[frontIndex];
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    void clear() {
        frontIndex = 0;
        backIndex = -1;
        currentSize = 0;
    }

    int size() const {
        return currentSize;
    }

    void print() const {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << array[(frontIndex + i) % capacity] << (i != currentSize - 1 ? " " : "");
        }
        std::cout << std::endl;
    }
};

#endif // QUEUE_H

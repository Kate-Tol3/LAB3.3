#pragma once

#include <iostream>
#include "Exception.h"
#include "Sequence.h"
#include "LinkedList.h"
#include "../Pointers/UnqPtr.h"

template <typename T>
class DynamicArray {
protected:
    int size;
    UnqPtr<T[]> array;

public:

    DynamicArray(const T* other_array, int size): size(size){
        if (size < 0) throw IndexOutOfRange();
        array = UnqPtr<T[]> (new T[size]);
        for (int i = 0; i < size; ++i) {
            array[i] = other_array[i];
        }
    }

    DynamicArray(): size(0), array(nullptr) {}

    DynamicArray(int size): size(size) {
        if (size < 0) throw IndexOutOfRange();
        array = UnqPtr<T[]> (new T[size]);
    }

    DynamicArray(const DynamicArray<T>& other): size(other.getSize()), array(new T[other.getSize()]) {
        for (int i = 0; i < size; ++i) {
            array[i] = other.get(i);
        }
    }

    DynamicArray(const LinkedList<T>& other): size(other.getLength()), array(new T[other.getLength()]) {
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    DynamicArray(const Sequence<T>& other): size(other.getLength()), array(new T[other.getLength()]) {
        for (int i = 0; i < size; ++i) {
            set(i, other.get(i));
        }
    }

    ~DynamicArray() = default;


    T& operator[](int index) {
        if (index >= size || index < 0) throw IndexOutOfRange();
        return array[index];
    }

    const T& operator[](int index) const {
        if (index >= size || index < 0) throw IndexOutOfRange();
        return array[index];
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this == &other) return *this;
        array.reset(new T[other.getSize()]);
        size = other.size;
        for (int i = 0; i < size; ++i) {
            array[i] = other.get(i);
        }
        return *this;
    }

    T get(int index) const {
        if (index >= size || index < 0) throw IndexOutOfRange();
        return array[index];
    }

    int getSize() const {
        return size;
    }

    void set(int index, const T& value) {
        if (index >= size || index < 0) throw IndexOutOfRange();
        array[index] = value;
    }

    void resize(int newSize) {
        if (newSize < 0) throw IndexOutOfRange();
        UnqPtr<T[]> newArray(new T[newSize]);
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            newArray[i] = array[i];
        }
        array.swap(newArray); // Замена массива
        size = newSize;
    }

    void append(const T& item) {
        resize(size + 1);
        array[size - 1] = item;
    }

    void prepend(const T& item) {
        UnqPtr<T[]> newArray(new T[size + 1]);
        newArray[0] = item;
        for (int i = 0; i < size; ++i) {
            newArray[i + 1] = array[i];
        }
        array.swap(newArray);
        size += 1;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > size) throw IndexOutOfRange();
        UnqPtr<T[]> newArray(new T[size + 1]);
        for (int i = 0; i < index; ++i) {
            newArray[i] = array[i];
        }
        newArray[index] = item;
        for (int i = index; i < size; ++i) {
            newArray[i + 1] = array[i];
        }
        array.swap(newArray);
        size += 1;
    }

    void print() const {
        for (int i = 0; i < size; i++){
            std::cout << array[i].first << " " << array[i].second << (i != size - 1 ? " " : "");
        }
    }
};

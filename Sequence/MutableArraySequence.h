#pragma once

#include <stdexcept>
#include "MutableSequence.h"
#include "Sequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "../Pointers/UnqPtr.h"


template <typename T>
class MutableArraySequence: public MutableSequence<T> {
private:
    UnqPtr<DynamicArray<T>> array;
public:

    MutableArraySequence(const T* array, int size): array(new DynamicArray<T>(array, size)) {}
    MutableArraySequence(int size): array(new DynamicArray<T>(size)) {}
    MutableArraySequence(): array(new DynamicArray<T>(0)) {}
    MutableArraySequence(const LinkedList<T>& other): array(new DynamicArray<T>(other)) {}
    MutableArraySequence(const DynamicArray<T>& other): array(new DynamicArray<T>(other)) {}
    MutableArraySequence(const Sequence<T>& other): array(new DynamicArray<T>(other)) {}
    MutableArraySequence(const MutableArraySequence<T>& other): array(new DynamicArray<T>(*(other.array))) {}

    ~MutableArraySequence() override {}

    T& operator[](int index) override{
        return (*array)[index];
    }

    const T& operator [] (int index) const override {
        return (*array)[index];
    }

    MutableArraySequence<T>& operator=(const MutableArraySequence<T>& other) {
       *array = *other.array;
       return *this;
    }

    const T& getFirst() const override {
        return (*array)[0];
    }

    T& getFirst() {
        return (*array)[0];
    }

    const T& getLast() const override {
        return (*array)[getLength() - 1];
    }

    T& getLast() {
        return (*array)[getLength() - 1];
    }

    const T& get(int index) const override {
        return (*array)[index];
    }

    T& get(int index) {
        return (*array)[index];
    }

    void set(int index, const T& value) override {
        (*array)[index] = value;
    }

    int getLength() const override {
        return array->getSize();
    }

    void append(const T& item) override {
        array->append(item);
    }

    void prepend(const T& item) override {
        array->prepend(item);
    }

    void insertAt(const T& item, int index) override {
        array->insertAt(item, index);
    }

    MutableArraySequence<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength()) throw IndexOutOfRange();
        MutableArraySequence<T>* result = new MutableArraySequence<T>(endIndex - startIndex + 1);
        for (int i = 0; i < result->getLength(); ++i) {
            (*result)[i] = get(i + startIndex);
        }
        return result;
    }

    MutableArraySequence<T>* concat(const Sequence<T>& other) const override {
        MutableArraySequence<T>* result = new MutableArraySequence<T>(other.getLength() + getLength());
        int i = 0;
        int length = getLength();
        for (; i < length; ++i) {
            (*result)[i] = get(i);
        }
        for (; i < length + other.getLength(); ++i) {
            (*result)[i] = other.get(i - length);
        }
        return result;
    }


    void print() const override{
        this->array->print();
    }

};
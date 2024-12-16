#pragma once

#include "Sequence.h"
#include "../Pointers/SharedPtr.h"
#include <iostream>
#include "Exception.h"


template <typename T>
class Node {
public:
    SharedPtr<Node<T>> next;
    T value;
    Node(): next(nullptr) {}
    explicit Node(T value): next(nullptr), value(value) {}
};

template <typename T>
class LinkedList {
private:
    int length = 0;
    SharedPtr<Node<T>> head;
    SharedPtr<Node<T>> tail;


    Node<T>& getNode(int index) const {
        if (index < 0 || index >= length) throw IndexOutOfRange();
        if (head.get() == nullptr) throw IndexOutOfRange();
        SharedPtr<Node<T>> bufNode (head);
        for (int i = 0; i < index; ++i) {
            bufNode = bufNode->next;
        }
        return *bufNode;
    }

public:
    LinkedList(const T* items, int length) {
        if (length < 0) throw IndexOutOfRange();
        for (int i = 0; i < length; ++i){
            append(items[i]);
        }
    }

    LinkedList(const Sequence<T>& other) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    LinkedList() {}

    LinkedList(const LinkedList<T>& other) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other[i]);
        }
    }

    LinkedList(int length) {
        if (length < 0) throw IndexOutOfRange();
        if (length > 0) {
            head = SharedPtr<Node<T>>(new Node<T>());
            tail = head;
        }
        for (int i = 1; i < length; ++i) {
            tail->next = SharedPtr<Node<T>>(new Node<T>());
            tail = tail->next;
        }
        this->length = length;
    }

    ~LinkedList() = default;

    int getLength() const {
        return length;
    }

    T& operator[](int index) {
        return getNode(index).value;
    }

    const T& operator[](int index) const {
        return getNode(index).value;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        head = nullptr;
        tail = nullptr;
        length = 0;

        for (int i = 0; i < other.getLength(); ++i) {
            append(other.getNode(i).value);
        }
        return *this;
    }

     bool operator==(const LinkedList<T>& other) const {
        if (this == &other) return true;
        if (length == other.getLength()) {
            for (int i = 0; i < length; ++i) {
                if ((*this).get(i) != other.get(i)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    const T& getFirst() const {
        if (!head.get()) throw EmptyListException();
        return head->value;
    }

    const T& getLast() const {
        if (!head.get()) throw EmptyListException();
        return tail->value;
    }

    const T& get(int index) const {
        return (*this)[index];
    }

     T& getFirst() {
        if (!head.get()) throw EmptyListException();
        return head->value;
    }

     T& getLast() {
        if (!head.get()) throw EmptyListException();
        return tail->value;
    }

     T& get(int index) {
        return (*this)[index];
    }

    void set(int index, const T& value) {
        (*this)[index] = value;
    }

    void append(const T& item) {
        if (length == 0) {
            head = SharedPtr<Node<T>>(new Node<T>(item));
            tail = head;
        } else {
            tail->next = SharedPtr<Node<T>>(new Node<T>(item));
            tail = tail->next;
        }
        ++length;
    }

    void prepend(const T& item) {
        SharedPtr<Node<T>> newNode(new Node<T>(item));
        newNode->next = std::move(head);
        head = std::move(newNode);
        if (length == 0) {
            tail = head;
        }
        ++length;
    }

    void insertAt(const T& item, int index) {
        if (index < 0 || index > length) throw IndexOutOfRange();

        if (index == 0) {
            prepend(item);
        } else if (index == length) {
            append(item);
        } else {
            Node<T>* prevNode = &getNode(index - 1);
            SharedPtr<Node<T>> newNode(new Node<T>(item));
            newNode->next = std::move(prevNode->next);
            prevNode->next = std::move(newNode);
            ++length;
        }
    }

    LinkedList<T>* concat(const LinkedList<T>* other) const {
        LinkedList<T>* result = new LinkedList<T>;

        for (int i = 0; i < getLength(); ++i) {
            result->append(getNode(i).value);
        }
        for (int j = 0; j < other->getLength(); ++j) {
            result->append(other->getNode(j).value);
        }

        return result;
    }

    LinkedList<T>* getSubsequence(int startIndex, int endIndex) const {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= this->getLength())
            throw IndexOutOfRange();

        LinkedList<T>* result = new LinkedList<T>;
        for (int i = startIndex; i <= endIndex; ++i) {
            result->append(getNode(i).value);
        }
        return result;
    }

     void print() const {
        SharedPtr<Node<T>> temp = head;
        while (temp.get()) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

};
#ifndef AVLSET_H
#define AVLSET_H

#include <set>
#include "ISet.h"
#include "AVLTree.h"
#include "../Sequence/MutableArraySequence.h"

template <typename T>
class AVLSet : public ISet<T> {
private:
    AVLTree<T> tree;

public:
    AVLSet() = default;
    ~AVLSet() = default;


    explicit AVLSet(const MutableArraySequence<T>& sequence) {
        for (int i = 0; i < sequence.getLength(); i++)
            AVLSet<T>::insert(sequence.get(i));
    }

    AVLSet(const AVLSet<T>& set) : tree(set.tree) {}
    explicit AVLSet(std::set<T> set) : tree(set) {}

    void insert(const T& element) override {
        if (tree.find(element)) return;
        tree.insert(element);
    }

    void erase(const T& element) override {
        tree.remove(element);
    }

    bool contains(const T& element) const override {
        return tree.find(element);
    }

    int size() const override {
        return tree.getSize();
    }

    bool isEmpty() const override {
        return tree.getSize() == 0;
    }

    // Объединение двух множеств
    ISet<T>* setUnion(ISet<T>& s) override {
        AVLSet<T>* result = new AVLSet<T>();
        for (const T& value : tree) {
            result->insert(value);
        }
        for (const T& value : dynamic_cast<AVLSet<T>&>(s).tree) {
            result->insert(value);
        }
        return result;
    }

    // Пересечение двух множеств
    ISet<T>* intersect(ISet<T>& s) override {
        AVLSet<T>* result = new AVLSet<T>();
        for (const T& value : tree) {
            if (s.contains(value)) {
                result->insert(value);
            }
        }
        return result;
    }

    // Разность двух множеств
    ISet<T>* subtract(ISet<T>& s) override {
        AVLSet<T>* result = new AVLSet<T>();
        for (const T& value : tree) {
            if (!s.contains(value)) {
                result->insert(value);
            }
        }
        return result;
    }

    void clear() override {
        tree.clear();
    }


    // Проверка, является ли текущее множество подмножеством другого множества
    bool isSubset(const ISet<T>& set) const override {
        if (this->size() > set.size()) return false;
        for (const T& value : tree) {
            if (!set.contains(value)) {
                return false;
            }
        }
        return true;
    }

    // Проверка на равенство двух множеств
    bool isEqual(const ISet<T>& set) const override {
        if (size() != set.size()) {
            return false;
        }
        for (const T& value : tree) {
            if (!set.contains(value)) {
                return false;
            }
        }
        return true;
    }


    bool operator==(const ISet<T>& set) const override {
        return isEqual(set);
    }

    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        typename AVLTree<T>::Iterator iterator;

        explicit Iterator(typename AVLTree<T>::Iterator it) : iterator(it) {}

        reference operator*() {
            return *iterator;
        }
        const T& operator*() const { return *iterator; }

        pointer operator->() {
            return &(*iterator);
        }

        Iterator& operator++() {
            ++iterator;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) {
            return a.iterator == b.iterator;
        }

        friend bool operator!=(const Iterator& a, const Iterator& b) {
            return a.iterator != b.iterator;
        }
    };

    Iterator begin() {
        return Iterator(tree.begin());
    }

    Iterator end() {
        return Iterator(tree.end());
    }

};

#endif



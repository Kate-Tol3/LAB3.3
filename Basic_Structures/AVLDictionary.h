#ifndef AVLDICTIONARY_H
#define AVLDICTIONARY_H

#include "AVLTree.h"
#include "IDictionary.h"
#include "../Sequence/MutableArraySequence.h"
#include <stdexcept>


// Структура Pair для хранения ключа и значения
template <typename TKey, typename TElement>
class Pair {
public:
    TKey key;
    TElement element;

    Pair() = default;

    Pair(const TKey& key, const TElement& element)
        : key(key), element(element) {}

    bool operator<(const Pair& other) const { return key < other.key; }
    bool operator>(const Pair& other) const { return key > other.key; }
    bool operator==(const Pair& other) const { return key == other.key; }
    bool operator!=(const Pair& other) const { return key != other.key; }
    bool operator<=(const Pair& other) const { return key <= other.key; }
    bool operator>=(const Pair& other) const { return key >= other.key; }
};


template <typename TKey, typename TElement>
class AVLDictionary : public IDictionary<TKey, TElement> {
private:
    AVLTree<Pair<TKey, TElement>> tree;


    class Iterator {
    private:
        typename AVLTree<Pair<TKey, TElement>>::Iterator treeIterator; // Итератор для обхода дерева

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = Pair<TKey, TElement>;
        using pointer = Pair<TKey, TElement>*;
        using reference = Pair<TKey, TElement>&;


        explicit Iterator(typename AVLTree<Pair<TKey, TElement>>::Iterator it)
            : treeIterator(it) {}


        reference operator*() const {
            return *treeIterator;
        }

        pointer operator->() {
            return &(*treeIterator);
        }

        Iterator& operator++() {
            ++treeIterator;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.treeIterator == b.treeIterator;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.treeIterator != b.treeIterator;
        }

    };


public:
    AVLDictionary() = default;

    int getCount() const override {
        return tree.getCount();
    }

    int getCapacity() const override {
        return tree.getSize();
    }

    // Получить элемент по ключу
     TElement get(const TKey& key) const override {
        Pair<TKey, TElement> pairToFind(key, TElement());
        auto node = tree.getNode(tree.root, pairToFind);
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return node->value.element;
    }

    // Получить ссылку на элемент по ключу
    const TElement& getReference(const TKey& key) const {
        Pair<TKey, TElement> pairToFind(key, TElement());
        auto node = tree.getNode(tree.root, pairToFind);
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return node->value.element;
    }

    TElement& getReference(const TKey& key){
        Pair<TKey, TElement> pairToFind(key, TElement());
        auto node = tree.getNode(tree.root, pairToFind);
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return node->value.element;
    }

    bool containsKey(const TKey& key) const override {
        Pair<TKey, TElement> pairToFind(key, TElement());
        return tree.find(pairToFind);
    }

    void insert(const TKey& key, const TElement& element) override {
        if (containsKey(key)) {
            throw std::runtime_error("Key already exists");
        }
        Pair<TKey, TElement> pairToAdd(key, element);
        tree.insert(pairToAdd);
    }

    void remove(const TKey& key) override {

        if (!containsKey(key)) {
            throw std::runtime_error("Key not found");
        }
        Pair<TKey, TElement> pairToRemove(key, TElement());
        tree.remove(pairToRemove);
    }

    // Добавить или обновить пару ключ-значение
    void set(const TKey& key, const TElement& element) override {
        Pair<TKey, TElement> pairToSet(key, element);
        auto node = tree.getNode(tree.root, pairToSet);
        if (node == nullptr) {
            tree.insert(pairToSet);
        } else {
            node->value.element = element;
        }
    }

    // возвращает все ключи
    MutableArraySequence<TKey> getKeys() const {
        MutableArraySequence<TKey> keys;
        for (const auto &pair : tree) {
            keys.append(pair.key);
        }
        return keys;
    }
    //возвращает все значения
    MutableArraySequence<TElement> getValues() const {
        MutableArraySequence<TElement> values;
        for (const auto &pair : tree) {
            values.append(pair.element);
        }
        return values;
    }

    // Очищает словарь
    void clear() override {
        tree.clear(); // Очистка дерева
    }

    Iterator begin() const {
        return Iterator(tree.begin());
    }

    Iterator end() const {
        return Iterator(tree.end());
    }

    Iterator getIterator() const {
        return begin();
    }
};

#endif // AVLDICTIONARY_H







#ifndef AVLDICTIONARY_H
#define AVLDICTIONARY_H

#include "AVLTree.h"
#include "IDictionary.h"
#include "IIterator.h"
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

    int findIndex(const TKey& key) const {
        Pair<TKey, TElement> pairToFind(key, TElement()); // Пара с нужным ключом
        auto node = tree.find(pairToFind);
        if (node == nullptr) {
            return -1; // Не найдено
        }
        return 0; // Если нашли, просто возвращаем индекс (можно улучшить)
    }

    // Итератор для словаря
    class Iterator : public IIterator<Pair<TKey, TElement>> {
    private:
        typename AVLTree<Pair<TKey, TElement>>::Iterator treeIterator; // Итератор для обхода дерева

    public:
        Iterator(typename AVLTree<Pair<TKey, TElement>>::Iterator treeIter)
            : treeIterator(treeIter) {}

        bool hasNext() const override {
            return treeIterator.hasNext();
        }

        bool next() override {
            return treeIterator.next();
        }

        const Pair<TKey, TElement>& getCurrentItem() const override {
            return treeIterator.getCurrentItem();
        }

        bool tryGetCurrentItem(Pair<TKey, TElement>& currentItem) const override {
            return treeIterator.tryGetCurrentItem(currentItem);
        }
    };

public:
    AVLDictionary() = default;

    int getCount() const override {
        return tree.getCount();
    }

    // в данном случае количество элементов, так как AVL-дерево не имеет фиксированной емкости
    int getCapacity() const override {
        return tree.getCount();
    }

    // Получить элемент по ключу
    TElement get(const TKey& key) const override {
        Pair<TKey, TElement> pairToFind(key, TElement());
        auto node = tree.find(pairToFind);
        if (node == nullptr) {
            throw std::runtime_error("Key not found");
        }
        return node->element;
    }

    // Get value by key
    TValue Get(const TKey &key) const override {
        auto node = tree.findRef(KeyValuePair(key, TValue()));
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->value.value;
    }

    // Проверить наличие ключа
    bool containsKey(const TKey& key) const override {
        Pair<TKey, TElement> pairToFind(key, TElement());
        return tree.contains(pairToFind);
    }

    // Добавить пару ключ-значение
    void add(const TKey& key, const TElement& element) override {
        Pair<TKey, TElement> pairToAdd(key, element);
        if (tree.contains(pairToAdd)) {
            throw std::runtime_error("Key already exists");
        }
        tree.insert(pairToAdd);
    }

    // Удалить пару по ключу
    void remove(const TKey& key) override {
        Pair<TKey, TElement> pairToRemove(key, TElement());
        if (!tree.contains(pairToRemove)) {
            throw std::runtime_error("Key not found");
        }
        tree.remove(pairToRemove);
    }

    // Итератор
    Iterator begin() const {
        return Iterator(tree.begin());
    }

    Iterator end() const {
        return Iterator(tree.end());
    }

    Iterator getIterator() const {
        return begin();  // getIterator эквивалентен begin
    }
};

#endif // AVLDICTIONARY_H


#ifndef LAB3_SEM3_IDICTIONARYBINARYTREE_H
#define LAB3_SEM3_IDICTIONARYBINARYTREE_H

#include <stdexcept>
#include "BinaryTree.h"
#include "IDictionary.h"

template <typename TKey, typename TValue>
class IDictionaryBinaryTree : public IDictionary<TKey, TValue> {



public:




    // Get value by key (pointer)
    TValue& GetReference(const TKey &key) {
        auto node = tree.findRef(KeyValuePair(key, TValue()));
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->value.value;
    }

    const TValue& GetReference(const TKey &key) const {
        auto node = tree.findRef(KeyValuePair(key, TValue()));
        if (!node) {
            throw std::out_of_range("Key not found");
        }
        return node->value.value;
    }
    // Check if key exists
    bool ContainsKey(const TKey &key) const override {
        return tree.find(KeyValuePair(key, TValue()));
    }

    // Add key-value pair
    void Add(const TKey &key, const TValue &value) override {
        if (ContainsKey(key)) {
            throw std::invalid_argument("Key already exists");
        }
        tree.insert(KeyValuePair(key, value));
    }

    // Remove key-value pair
    void Remove(const TKey &key) override {
        if (!ContainsKey(key)) {
            throw std::out_of_range("Key not found");
        }
        tree.remove(KeyValuePair(key, TValue()));
    }

    // Get count of elements
    size_t GetCount() const override {
        return tree.getSize();
    }

    // Get all keys
    ArraySequence<TKey> GetKeys() const override {
        ArraySequence<TKey> keys;
        for (const auto &pair : tree) {
            keys.append(pair.key);
        }
        return keys;
    }

    // Get all values
    ArraySequence<TValue> GetValues() const override {
        ArraySequence<TValue> values;
        for (const auto &pair : tree) {
            values.append(pair.value);
        }
        return values;
    }

    class Iterator {
        typename BinaryTree<KeyValuePair>::Iterator iterator;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = KeyValuePair;
        using pointer = KeyValuePair*;
        using reference = KeyValuePair&;

        explicit Iterator(typename BinaryTree<KeyValuePair>::Iterator it) : iterator(it) {}

        reference operator*() const {
            return *iterator;
        }

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

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.iterator == b.iterator;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.iterator != b.iterator;
        }
    };

    Iterator begin() const {
        return Iterator(tree.begin());
    }

    Iterator end() const {
        return Iterator(tree.end());
    }
};

#endif //LAB3_SEM3_IDICTIONARYBINARYTREE_H

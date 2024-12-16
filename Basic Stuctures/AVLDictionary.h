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
    bool operator==(const Pair& other) const { return key == other.key; }
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

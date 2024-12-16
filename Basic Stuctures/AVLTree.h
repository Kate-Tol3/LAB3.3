#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <stdexcept>
#include "IIterator.h"
#include "Stack.h"
#include "../Pointers/UnqPtr.h"

// Узел дерева
template <typename T>
struct TreeNode {
    T value;
    UnqPtr<TreeNode<T>> left;
    UnqPtr<TreeNode<T>> right;
    int height;

    explicit TreeNode(const T& value)
        : value(value), left(nullptr), right(nullptr), height(1) {}

    explicit TreeNode(const T& value, UnqPtr<TreeNode<T>> left = nullptr, UnqPtr<TreeNode<T>> right = nullptr)
                : value(value), left(left), right(right), height(1) {}
};

// АВЛ-дерево
template <typename T>
class AVLTree {
private:
    UnqPtr<TreeNode<T>> root;

    // Получение высоты узла
    int getHeight(const UnqPtr<TreeNode<T>>& node) const {
        return !node.isNull() ? node->height : 0;
    }

    // Обновление высоты узла
    void updateHeight(UnqPtr<TreeNode<T>>& node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    // Получение баланса узла
    int getBalanceFactor(const UnqPtr<TreeNode<T>>& node) const {
        return node.get() ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Левый поворот
    void rotateLeft(UnqPtr<TreeNode<T>>& node) {
        auto newRoot = std::move(node->right);
        node->right = std::move(newRoot->left);
        newRoot->left = std::move(node);
        updateHeight(newRoot->left);
        updateHeight(newRoot);
        node = std::move(newRoot);
    }

    // Правый поворот
    void rotateRight(UnqPtr<TreeNode<T>>& node) {
        auto newRoot = std::move(node->left);
        node->left = std::move(newRoot->right);
        newRoot->right = std::move(node);
        updateHeight(newRoot->right);
        updateHeight(newRoot);
        node = std::move(newRoot);
    }

    // Балансировка узла
    void balance(UnqPtr<TreeNode<T>>& node) {
        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) { // Левый тяжелый
            if (getBalanceFactor(node->left) < 0) { // Левый-правый случай
                rotateLeft(node->left);
            }
            rotateRight(node);
        } else if (balanceFactor < -1) { // Правый тяжелый
            if (getBalanceFactor(node->right) > 0) { // Правый-левый случай
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
    }

    // Вставка узла
    void insert(UnqPtr<TreeNode<T>>& node, const T& value) {
        if (!node.get()) {
            node = UnqPtr<TreeNode<T>>(new TreeNode(value));
            return;
        }
        if (value < node->value) {
            insert(node->left, value);
        } else if (value > node->value) {
            insert(node->right, value);
        } else {
            return; // Дубликаты игнорируются
        }
        updateHeight(node);
        balance(node);
    }

    // Удаление минимального узла
    UnqPtr<TreeNode<T>> removeMin(UnqPtr<TreeNode<T>>& node) {
        if (!node->left.get()) {
            return std::move(node->right);
        }
        node->left = removeMin(node->left);
        updateHeight(node);
        return std::move(node);
    }

    // Удаление узла
    void remove(UnqPtr<TreeNode<T>>& node, const T& value) {
        if (!node.get()) return;

        if (value < node->value) {
            remove(node->left, value);
        } else if (value > node->value) {
            remove(node->right, value);
        } else {
            if (!node->left.get()) {
                node = std::move(node->right);
            } else if (!node->right.get()) {
                node = std::move(node->left);
            } else {
                auto minNode = findMin(node->right);
                node->value = minNode->value;
                node->right = removeMin(node->right);
            }
        }
        if (node.get()) {
            updateHeight(node);
            balance(node);
        }
    }

    // Поиск минимального узла
    const TreeNode<T>* findMin(const UnqPtr<TreeNode<T>>& node) const {
        return node->left.get() ? findMin(node->left) : node.get();
    }

    // Проверка наличия узла
    bool contains(const UnqPtr<TreeNode<T>>& node, const T& value) const {
        if (node.isNull()) return false;
        if (value < node->value) return contains(node->left, value);
        if (value > node->value) return contains(node->right, value);
        return true;
    }

    // Подсчет количества узлов
    int getCount(const UnqPtr<TreeNode<T>>& node) const {
        return node.get() ? 1 + getCount(node->left) + getCount(node->right) : 0;
    }

    // Приватный метод поиска узла
    const T& find(const UnqPtr<TreeNode<T>>& node, const T& value) const {
        if (!node.get()) throw std::runtime_error("Element not found");
        if (value < node->value) {
            return find(node->left, value);
        } else if (value > node->value) {
            return find(node->right, value);
        } else {
            return node->value; // Найден элемент
        }
    }

public:
    // Вставка ключа
    void insert(const T& value) {
        insert(root, value);
    }

    // Удаление ключа
    void remove(const T& value) {
        remove(root, value);
    }

    // Проверка наличия ключа
    bool contains(const T& value) const {
        return contains(root, value);
    }

    // Получить количество элементов в дереве
    int getCount() const {
        return getCount(root);
    }

    // Итератор для обхода
    class Iterator : public IIterator<T> {
    private:
        Stack<const TreeNode<T>*> nodesStack;

        void pushAll(const TreeNode<T>* node) {
            while (node) {
                nodesStack.push(node);
                node = node->left.get();
            }
        }

    public:
        explicit Iterator(const TreeNode<T>* root) { // Изменяем конструктор для const
            pushAll(root);
        }

        Iterator& operator++() {
            if (!hasNext()) throw std::out_of_range("No more elements");
            const TreeNode<T>* current = nodesStack.peek();
            nodesStack.pop();
            pushAll(current->right.get());
            return *this;
        }

        T operator*() const {
            if (nodesStack.isEmpty()) throw std::out_of_range("No more elements");
            return nodesStack.peek()->value;
        }

        bool hasNext() const override {
            return !nodesStack.isEmpty();
        }

        bool next() override {
            if (!hasNext()) return false;
            const TreeNode<T>* current = nodesStack.peek();
            nodesStack.pop();
            pushAll(current->right.get());
            return true;
        }

        T getCurrentItem() const override {
            if (nodesStack.isEmpty()) throw std::out_of_range("No more elements");
            return nodesStack.peek()->value; // возвращаем значение по значению
        }


        bool tryGetCurrentItem(T& element) const override {
            if (nodesStack.isEmpty()) {
                return false;
            }
            element = getCurrentItem();
            return true;
        }
    };


    Iterator begin() const {
        return Iterator(root.get());
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    // Получить итератор
    Iterator getIterator() const {
        return begin();
    }

    // Поиск ключа
    const T& find(const T& value) const {
        return find(root, value);
    }
};

#endif // AVLTREE_H

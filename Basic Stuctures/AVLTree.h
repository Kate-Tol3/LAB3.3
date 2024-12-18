#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <stdexcept>
#include <algorithm>
#include "IIterator.h"
#include "Stack.h"
#include "../Pointers/UnqPtr.h"

// Узел дерева
template <typename T>
struct TreeNode {
    T value;
    UnqPtr<TreeNode<T>> left;
    UnqPtr<TreeNode<T>> right;
    TreeNode* next = nullptr;
    int height = 1; // Высота для баланса

    explicit TreeNode(T value) : value(value), left(nullptr), right(nullptr), height(1) {}

    void updateHeight() {
        int leftHeight = left.get() ? left->height : 0;
        int rightHeight = right.get() ? right->height : 0;
        height = std::max(leftHeight, rightHeight) + 1;
    }

    int balanceFactor() const {
        int leftHeight = left.get() ? left->height : 0;
        int rightHeight = right.get() ? right->height : 0;
        return leftHeight - rightHeight;
    }
};

// AVL Дерево
template <typename T>
class AVLTree {
private:
    UnqPtr<TreeNode<T>> root;
    int size = 0;

    // Приватные методы для балансировки
    void rotateLeft(UnqPtr<TreeNode<T>>& node) {
        // Поворот влево: левый дочерний узел будет новым корнем
        UnqPtr<TreeNode<T>> rightChild = std::move(node->right); // правый дочерний узел
        node->right = std::move(rightChild->left);  // левый дочерний узел правого узла становится правым для текущего
        rightChild->left = std::move(node);  // текущий узел становится левым дочерним для правого дочернего узла

        // Обновляем высоты
        rightChild->left->updateHeight();
        rightChild->updateHeight();

        // Обновляем ссылку на новый корень
        node = std::move(rightChild);
    }

    void rotateRight(UnqPtr<TreeNode<T>>& node) {
        // Поворот вправо: правый дочерний узел будет новым корнем
        UnqPtr<TreeNode<T>> leftChild = std::move(node->left); // левый дочерний узел
        node->left = std::move(leftChild->right);  // правый дочерний узел левого узла становится левым для текущего
        leftChild->right = std::move(node);  // текущий узел становится правым дочерним для левого дочернего узла

        // Обновляем высоты
        leftChild->right->updateHeight();
        leftChild->updateHeight();

        // Обновляем ссылку на новый корень
        node = std::move(leftChild);
    }


    void balance(UnqPtr<TreeNode<T>>& node) {
        node->updateHeight();
        if (node->balanceFactor() > 1) {
            if (node->left->balanceFactor() < 0) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
        else if (node->balanceFactor() < -1) {
            if (node->right->balanceFactor() > 0) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
    }

    void insertRec(UnqPtr<TreeNode<T>>& node, const T& value) {
        if (!node.get()) {
            node = UnqPtr<TreeNode<T>>(new TreeNode(value));
            return;
        }
        if (value < node->value) {
            insertRec(node->left, value);
        } else {
            insertRec(node->right, value);
        }
        node->updateHeight();
        balance(node);
    }

    void removeRec(UnqPtr<TreeNode<T>>& node, const T& value) {
        if (!node.get()) return;

        if (value < node->value) {
            removeRec(node->left, value);
        } else if (value > node->value) {
            removeRec(node->right, value);
        } else {
            if (!node->left.get()) {
                node = std::move(node->right);  // Перемещение правого поддерева
            } else if (!node->right.get()) {
                node = std::move(node->left);   // Перемещение левого поддерева
            } else {
                auto minNode = getMinNode(std::move(node->right));  // Перемещение правого поддерева
                minNode->right = removeMinNode(std::move(node->right)); // Перемещение правого поддерева
                minNode->left = std::move(node->left);  // Перемещение левого поддерева
                node = std::move(minNode);  // Присваиваем перемещенный минимальный узел
            }
        }
        if (node.get()) {
            node->updateHeight();
            balance(node);
        }
    }

    UnqPtr<TreeNode<T>> getMinNode(UnqPtr<TreeNode<T>> node) {
        while (node->left.get()) {
            node = std::move(node->left);  // Перемещение влево
        }
        return node;
    }

    UnqPtr<TreeNode<T>> removeMinNode(UnqPtr<TreeNode<T>> node) {
        if (!node->left.get()) return std::move(node->right);  // Перемещение правого поддерева
        node->left = removeMinNode(std::move(node->left));  // Перемещение левого поддерева
        return node;
    }

    int getCountRec(const UnqPtr<TreeNode<T>>& node) const {
        return node.get() ? 1 + getCountRec(node->left) + getCountRec(node->right) : 0;
    }

    // Приватные методы для поиска и получения максимума
    bool findRec(TreeNode<T>* node, const T& value) const {
        if (!node) return false;
        if (value == node->value) return true;
        return value < node->value ? findRec(node->left.get(), value) : findRec(node->right.get(), value);
    }

    T getMaxRec(TreeNode<T>* node) const {
        if (!node->right) return node->value;
        return getMaxRec(node->right.get());
    }

    // Потоки для обхода
    struct ThreadOperation {
        UnqPtr<TreeNode<T>> first;
        UnqPtr<TreeNode<T>> last;

        void apply(UnqPtr<TreeNode<T>> node) {
            if (!first.get()) first = node;
            if (last.get()) last->next = node;
            node->next = nullptr;
            last = node;
        }
    };

    void preOrderTraversal(TreeNode<T>* node, ThreadOperation& op) { //node-left-right traversal
        if (!node) return;
        op.apply(node);
        preOrderTraversal(node->left.get(), op);
        preOrderTraversal(node->right.get(), op);
    }


    void postOrderTraversal(TreeNode<T>* node) const {//left-right-node traversal
        if (!node) return;
        postOrderTraversal(node->left.get());  // Обойти левое поддерево
        postOrderTraversal(node->right.get());  // Обойти правое поддерево
        std::cout << node->value << " ";  // Посетить корень
    }



public:
    AVLTree() = default;
    ~AVLTree() = default;

    int getSize() const { return size; }

    void insert(const T& value) {
        insertRec(root, value);
        size++;
    }

    void remove(const T& value) {
        removeRec(root, value);
        size--;
    }

    bool findRecursive(const T& value) const {
        return findRec(root.get(), value);
    }

    bool find(const T& value) const {
        auto node = root.get();
        while (node) {
            if (value == node->value) return true;
            node = value < node->value ? node->left.get() : node->right.get();
        }
        return false;
    }

    T getMaxRecursive() const {
        if (!root) throw std::range_error("Tree is empty");
        return getMaxRec(root.get());
    }

    T getMax() const {
        if (!root) throw std::range_error("Tree is empty");
        TreeNode<T>* node = root.get();
        while (node->right) {
            node = node->right.get();
        }
        return node->value;
    }

    T getMin() const {
        if (!root) throw std::range_error("Tree is empty");
        return getMinNode(root.get())->value;
    }

    int getCount() const {
        return getCountRec(root);
    }

    void threadpreOrderTraversal() {
        ThreadOperation op;
        preOrderTraversal(root, op);
    }

    void printThreaded() const {
        UnqPtr<TreeNode<T>> current = root.get();
        while (current.get()) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Итератор для дерева
    // Итератор для дерева
    class Iterator {

    private:
        UnqPtr<TreeNode<T>> current;
        UnqPtr<TreeNode<T>> root;

    public:

        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        explicit Iterator(UnqPtr<TreeNode<T>> node) : current(node), root(node) {
            goToStart();
        }

        T& operator*() { return current->value; }
        T* operator->() { return &current->value; }

        bool operator!=(const Iterator& other) const { return current != other.current; }

        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.current == b.current;
        }

        Iterator& operator++() {
            advance(); // идет к следующему узлу
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        void goToStart() {
            // Переходим к самому левому узлу (для обхода в порядке in-order)
            while (current.get() && current->left.get()) {
                current = current->left.get();
            }
        }

        void advance() {
            if (!current.get()) return;

            // Если у текущего узла есть правый ребенок
            if (current->right.get()) {
                current = current->right.get();
                goToStart();  // Переходим к самому левому узлу правого поддерева
            } else {
                // Ищем следующего элемента, который находится в родительской цепочке
                UnqPtr<TreeNode<T>> successor = nullptr;
                UnqPtr<TreeNode<T>> ancestor = root;

                while (ancestor.get() != current.get()) {
                    if (current->value < ancestor->value) {
                        successor = ancestor;  // Найден возможный преемник
                        ancestor = ancestor->left.get();  // Идем в левое поддерево
                    } else {
                        ancestor = ancestor->right.get();  // Идем в правое поддерево
                    }
                }
                current = successor;  // Обновляем текущий элемент
            }

        }
    };

    Iterator begin() {
        return Iterator (root);
    }

    Iterator end() {
        return Iterator(nullptr);  // Возвращаем итератор на пустой узел
    }

};

#endif // AVLTREE_H

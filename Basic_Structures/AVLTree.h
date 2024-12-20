#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// Узел дерева
template <typename T>
class TreeNode {
public:
    T value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next = nullptr;
    int height = 1; // Высота для баланса

    explicit TreeNode(T value) : value(value), left(nullptr), right(nullptr), height(1) {}

    void updateHeight() {
        int leftHeight = left ? left->height : 0;
        int rightHeight = right ? right->height : 0;
        height = std::max(leftHeight, rightHeight) + 1;
    }

    int balanceFactor() const {
        int leftHeight = left ? left->height : 0;
        int rightHeight = right ? right->height : 0;
        return leftHeight - rightHeight;
    }
};

// AVL Дерево
template <typename T>
class AVLTree {
    template <typename TKey, typename TElement>
    friend class AVLDictionary;
private:
    TreeNode<T>* root = nullptr;
    int size = 0;

    // Приватные методы для балансировки
    void rotateLeft(TreeNode<T>*& node) {
        TreeNode<T>* rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;

        node->updateHeight();
        rightChild->updateHeight();

        node = rightChild;
    }

    void rotateRight(TreeNode<T>*& node) {
        TreeNode<T>* leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;

        node->updateHeight();
        leftChild->updateHeight();

        node = leftChild;
    }

    void balance(TreeNode<T>*& node) {
        node->updateHeight();
        if (node->balanceFactor() > 1) {
            if (node->left->balanceFactor() < 0) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        } else if (node->balanceFactor() < -1) {
            if (node->right->balanceFactor() > 0) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        }
    }

    void insertRec(TreeNode<T>*& node, const T& value) {
        if (!node) {
            node = new TreeNode<T>(value);
            return;
        }
        if (value < node->value) {
            insertRec(node->left, value);
        } else {
            insertRec(node->right, value);
        }
        balance(node);
    }

    void removeRec(TreeNode<T>*& node, const T& value) {
        if (!node) return;

        if (value < node->value) {
            removeRec(node->left, value);
        } else if (value > node->value) {
            removeRec(node->right, value);
        } else {
            if (!node->left) {
                TreeNode<T>* temp = node->right;
                delete node;
                node = temp;
            } else if (!node->right) {
                TreeNode<T>* temp = node->left;
                delete node;
                node = temp;
            } else {
                TreeNode<T>* minNode = getMinNode(node->right);
                node->value = minNode->value;
                removeRec(node->right, minNode->value);
            }
        }

        if (node) {
            balance(node);
        }
    }

    TreeNode<T>* getMinNode(TreeNode<T>* node) const {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T>* removeMinNode(TreeNode<T>* node) {
        if (!node->left) return node->right;
        node->left = removeMinNode(node->left);
        return node;
    }

    int getCountRec(const TreeNode<T>* node) const {
        return node ? 1 + getCountRec(node->left) + getCountRec(node->right) : 0;
    }

    bool findRec(const TreeNode<T>* node, const T& value) const {
        if (!node) return false;
        if (value == node->value) return true;
        return value < node->value ? findRec(node->left, value) : findRec(node->right, value);
    }

    TreeNode<T>* getNode(TreeNode<T>* node, const T& value) const {
        if (node == nullptr || node->value == value) {
            return node; // Возвращаем найденный узел или nullptr, если не найден
        }
        return value < node->value ? getNode(node->left, value) : getNode(node->right, value);
    }

    T getMaxRec(const TreeNode<T>* node) const {
        if (!node->right) return node->value;
        return getMaxRec(node->right);
    }

    struct ThreadOperation {
        TreeNode<T>* first = nullptr;
        TreeNode<T>* last = nullptr;

        void apply(TreeNode<T>* node) {
            if (!first) first = node;
            if (last) last->next = node;
            node->next = nullptr;
            last = node;
        }
    };

    void preOrderTraversal(TreeNode<T>* node, ThreadOperation& op) {
        if (!node) return;
        op.apply(node);
        preOrderTraversal(node->left, op);
        preOrderTraversal(node->right, op);
    }

public:
    AVLTree() = default;

    ~AVLTree() {
        clear(root);
    }

    void clear(TreeNode<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    int getSize() const { return size; }

    void insert(const T& value) {
        insertRec(root, value);
        size++;
    }

    void remove(const T& value) {
        removeRec(root, value);
        size--;
    }

    bool find(const T& value) const {
        return findRec(root, value);
    }

    T getMax() const {
        if (!root) throw std::range_error("Tree is empty");
        TreeNode<T>* node = root;
        while (node->right) {
            node = node->right;
        }
        return node->value;
    }

    T getMin() const {
        if (!root) throw std::range_error("Tree is empty");
        return getMinNode(root)->value;
    }

    int getCount() const {
        return getCountRec(root);
    }

    void threadPreOrderTraversal() {
        ThreadOperation op;
        preOrderTraversal(root, op);
    }

    void printThreaded() const {
        TreeNode<T>* current = root;
        while (current) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    class Iterator {
    private:
        TreeNode<T>* current;
        TreeNode<T>* root;

    public:
        explicit Iterator(TreeNode<T>* node) : current(nullptr), root(node) {
            goToStart();
        }

        T& operator*() { return current->value; }
        T* operator->() { return &current->value; }

        // bool operator==(const Iterator& other) const {
        //     return current == other.current;
        // }
        //
        // bool operator!=(const Iterator& other) const {
        //     return current != other.current;
        // }


        friend bool operator==(const Iterator &a, const Iterator &b) {
            return a.current == b.current;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b) {
            return a.current != b.current;
        }



        Iterator& operator++() {
            advance();
            return *this;
        }

    private:
        void goToStart() {
            current = root;
            while (current && current->left) {
                current = current->left;
            }
        }

        void advance() {
            if (!current) return;

            if (current->right) {
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                TreeNode<T>* successor = nullptr;
                TreeNode<T>* ancestor = root;
                while (ancestor != current) {
                    if (current->value < ancestor->value) {
                        successor = ancestor;
                        ancestor = ancestor->left;
                    } else {
                        ancestor = ancestor->right;
                    }
                }
                current = successor;
            }
        }
    };

    Iterator begin() const {
        return Iterator(root);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }
};

#endif // AVLTREE_H


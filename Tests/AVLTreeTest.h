//
// Created by Kate on 16.12.2024.
//

#ifndef AVLTREETEST_H
#define AVLTREETEST_H


#include <gtest/gtest.h>
#include "AVLTree.h"  // Подключаем ваш заголовочный файл с классом AVLTree

// Тестирование базовых операций с деревом
TEST(AVLTreeTest, InsertTest) {
    AVLTree<int> tree;

    // Вставляем элементы в дерево
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);

    // Проверка размера дерева
    EXPECT_EQ(tree.getSize(), 5);

    // Проверка поиска элементов
    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_FALSE(tree.find(100));
}

TEST(AVLTreeTest, RemoveTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Удаляем элементы
    tree.remove(20);
    tree.remove(5);

    // Проверка размера дерева
    EXPECT_EQ(tree.getSize(), 1);

    // Проверка наличия элементов
    EXPECT_TRUE(tree.find(10));
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(20));
}

TEST(AVLTreeTest, MinMaxTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    // Проверка минимального и максимального элементов
    EXPECT_EQ(tree.getMin(), 5);
    EXPECT_EQ(tree.getMax(), 20);
}

TEST(AVLTreeTest, IteratorTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(30);

    // Проверка обхода дерева с использованием итератора
    std::vector<int> values;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        values.push_back(*it);
    }

    std::vector<int> expected_values = {5, 10, 15, 20, 30};
    EXPECT_EQ(values, expected_values);
}

TEST(AVLTreeTest, ThreadedTraversalTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    tree.threadpreOrderTraversal();

    // Печать деревьев после threaded-обхода
    tree.printThreaded();
}

TEST(AVLTreeTest, PreOrderTraversalTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    std::vector<int> preOrderValues;
    tree.threadPreOrderTraversal();

    // Проверка обхода в порядке PreOrder
    tree.printThreaded();
}

TEST(AVLTreeTest, PostOrderTraversalTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    std::vector<int> postOrderValues;
    tree.threadPreOrderTraversal();

    // Проверка обхода в порядке PostOrder
    tree.printThreaded();
}

// Тестирование итератора через обход Морриса
TEST(AVLTreeTest, MorrisIteratorTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);
    tree.insert(25);

    std::vector<int> values;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        values.push_back(*it);
    }

    std::vector<int> expected_values = {5, 10, 15, 20, 25};
    EXPECT_EQ(values, expected_values);
}

// Тест на удаление минимальных и максимальных элементов
TEST(AVLTreeTest, RemoveMinMaxTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    tree.remove(5); // Удаляем минимальный элемент
    tree.remove(20); // Удаляем максимальный элемент

    EXPECT_EQ(tree.getSize(), 2); // После удаления должно остаться 2 элемента
    EXPECT_FALSE(tree.find(5)); // 5 должно быть удалено
    EXPECT_FALSE(tree.find(20)); // 20 должно быть удалено
}




#endif //AVLTREETEST_H

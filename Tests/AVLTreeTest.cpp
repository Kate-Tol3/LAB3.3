#include "AVLTreeTest.h"


TEST(AVLTreeTest, InsertTest) {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);

    EXPECT_EQ(tree.getSize(), 5);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(20));
    EXPECT_FALSE(tree.find(100));
}

TEST(AVLTreeTest, RemoveTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    tree.remove(20);
    tree.remove(5);

    EXPECT_EQ(tree.getSize(), 1);

    EXPECT_TRUE(tree.find(10));
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(20));
}

TEST(AVLTreeTest, MinMaxTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

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

    tree.threadPreOrderTraversal();

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

    tree.printThreaded();
}


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


TEST(AVLTreeTest, RemoveMinMaxTest) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    tree.remove(5);
    tree.remove(20);

    EXPECT_EQ(tree.getSize(), 2);
    EXPECT_FALSE(tree.find(5));
    EXPECT_FALSE(tree.find(20));
}

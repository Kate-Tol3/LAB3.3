#include <iostream>
#include "Basic Stuctures/AVLTree.h"

int main() {
    AVLTree<int> tree;
    system("chcp 65001");

    // Тест на вставку элементов
    std::cout << "== Тест на вставку элементов ==" << std::endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);

    std::cout << "Элементы вставлены: 10, 20, 30, 5, 15" << std::endl;
    std::cout << "Количество элементов в дереве: " << tree.getCount() << std::endl;

    // Тест на поиск элементов
    std::cout << "\n== Тест на поиск элементов ==" << std::endl;
    try {
        std::cout << "Поиск 15: " << tree.find(15) << " - Найден" << std::endl;
        std::cout << "Поиск 30: " << tree.find(30) << " - Найден" << std::endl;
        std::cout << "Поиск 25: ";
        std::cout << tree.find(25) << " - Найден" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Элемент 25 не найден" << std::endl;
    }

    // Тест на проверку наличия элементов
    std::cout << "\n== Тест на contains ==" << std::endl;
    std::cout << "Содержит 10? " << (tree.contains(10) ? "Да" : "Нет") << std::endl;
    std::cout << "Содержит 25? " << (tree.contains(25) ? "Да" : "Нет") << std::endl;

    // Тест на удаление элементов
    std::cout << "\n== Тест на удаление элементов ==" << std::endl;
    tree.remove(10);
    std::cout << "Удалён элемент 10" << std::endl;
    std::cout << "Содержит 10? " << (tree.contains(10) ? "Да" : "Нет") << std::endl;
    std::cout << "Количество элементов в дереве: " << tree.getCount() << std::endl;

    // Тест итератора
    std::cout << "\n== Тест на итератор ==" << std::endl;
    auto it = tree.getIterator();
    std::cout << "Обход элементов в порядке возрастания: ";
    while (it.hasNext()) {
        std::cout << it.getCurrentItem() << " ";
        it.next();
    }
    std::cout << std::endl;

    // Повторный тест вставки после удаления
    std::cout << "\n== Тест на повторную вставку ==" << std::endl;
    tree.insert(25);
    std::cout << "Вставлен элемент 25" << std::endl;
    std::cout << "Содержит 25? " << (tree.contains(25) ? "Да" : "Нет") << std::endl;
    std::cout << "Количество элементов в дереве: " << tree.getCount() << std::endl;

    // Финальный обход
    std::cout << "\n== Финальный обход элементов ==" << std::endl;
    auto finalIt = tree.getIterator();
    std::cout << "Элементы: ";
    while (finalIt.hasNext()) {
        std::cout << finalIt.getCurrentItem() << " ";
        finalIt.next();
    }
    std::cout << std::endl;

    return 0;
}

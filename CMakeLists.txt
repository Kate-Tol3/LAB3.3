cmake_minimum_required(VERSION 3.29)
project(LAB3_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(LAB3_3 main.cpp
        "Basic Stuctures/IDictionary.h"
        Tasks/Histogram.cpp
        Tasks/Histogram.h
        Sequence/DynamicArray.h
        Sequence/MutableArraySequence.h
        Sequence/MutableListSequence.h
        "Pointers/UnqPtr.h"
        "Pointers/SharedPtr.h"
        "Pointers/WeakPtr.h"
        "Basic Stuctures/Range.h"
        "Basic Stuctures/HashTable.h"
        "Basic Stuctures/AVLDictionary.h"
        "Basic Stuctures/AVLTree.h"
        "Basic Stuctures/IIterator.h"
        "Basic Stuctures/Stack.h"
        Tests/AVLDictionaryTest.h
        "Basic Stuctures/tempClass.cpp"
        "Basic Stuctures/tempClass.h"
)


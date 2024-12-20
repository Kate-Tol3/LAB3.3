cmake_minimum_required(VERSION 3.29)
project(LAB3_3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/googletest)

add_executable(LAB3_3 main.cpp
        "Basic_Structures/IDictionary.h"
        Tasks/Histogram.h
        Sequence/DynamicArray.h
        Sequence/MutableArraySequence.h
        Sequence/MutableListSequence.h
        "Pointers/UnqPtr.h"
        "Pointers/SharedPtr.h"
        "Pointers/WeakPtr.h"
        "Basic_Structures/Range.h"
        "Basic_Structures/AVLDictionary.h"
        "Basic_Structures/AVLTree.h"
        Tasks/Student/Student.h
        Basic_Structures/ISet.h
        Basic_Structures/AVLSet.h
        Tasks/Cache.h
        Basic_Structures/Queue.h
        #        Tests/AVLTreeTest.h
#        Tests/AVLDictionaryTest.h
#        Tests/AVLTreeTest.cpp
#        Tests/AVLDictionaryTest.cpp

)

#link_directories(${PROJECT_SOURCE_DIR}/third_party/googletest/lib)
include_directories(${PROJECT_SOURCE_DIR}/third_party/googletest/include)

# Добавляем тесты
enable_testing()
add_executable(MyTests
        Tests/AVLTreeTest.h
        Tests/AVLDictionaryTest.h
        Tests/AVLDictionaryTest.cpp
        Tests/AVLTreeTest.cpp
        Tests/HistogramTest.cpp
        Tests/HistogramTest.h
        Tests/CacheTest.cpp
        Tests/CacheTest.h
)

target_link_libraries(MyTests gtest gtest_main)
target_compile_options(MyTests PRIVATE -O2 -Wall -Wextra)

# Регистрируем тесты
add_test(NAME MyTests COMMAND MyTests)



##cmake_minimum_required(VERSION 3.29)
##project(LAB3_3)
##
##set(CMAKE_CXX_STANDARD 20)
##
##add_subdirectory(third_party/googletest)
##
###set(CMAKE_AUTOMOC ON)
###set(CMAKE_AUTORCC ON)
###set(CMAKE_AUTOUIC ON)
##
##find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)
##
##add_executable(LAB3_3 main.cpp
##        "Basic_Structures/IDictionary.h"
##        Tasks/Histogram.h
##        Sequence/DynamicArray.h
##        Sequence/MutableArraySequence.h
##        Sequence/MutableListSequence.h
##        "Pointers/UnqPtr.h"
##        "Pointers/SharedPtr.h"
##        "Pointers/WeakPtr.h"
##        "Basic_Structures/Range.h"
##        "Basic_Structures/AVLDictionary.h"
##        "Basic_Structures/AVLTree.h"
##        Tasks/Student/Student.h
##        Basic_Structures/ISet.h
##        Basic_Structures/AVLSet.h
##        Tasks/Cache.h
##        Basic_Structures/Queue.h
##        GUI.cpp
##        GUI.h
##        Person.h
##
##)
##
##target_link_libraries(LAB3_3
##        Qt6::Core
##        Qt6::Gui
##        Qt6::Widgets
##        Qt6::Charts
##)
##
##
##include_directories(${PROJECT_SOURCE_DIR}/third_party/googletest/include)
##
##enable_testing()
##add_executable(MyTests
##        Tests/AVLTreeTest.h
##        Tests/AVLDictionaryTest.h
##        Tests/AVLDictionaryTest.cpp
##        Tests/AVLTreeTest.cpp
##        Tests/HistogramTest.cpp
##        Tests/HistogramTest.h
##        Tests/CacheTest.cpp
##        Tests/CacheTest.h
##)
##
##target_link_libraries(MyTests gtest gtest_main)
##
##target_compile_options(MyTests PRIVATE -O2 -Wall -Wextra)
##
##add_test(NAME MyTests COMMAND MyTests)
##
##
#cmake_minimum_required(VERSION 3.29)
#project(LAB3_3)
#
#set(CMAKE_CXX_STANDARD 20)
#
## Включение поддержки Qt для moc, uic и rcc
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#
## Добавление сторонних библиотек
#add_subdirectory(third_party/googletest)
#
## Поиск библиотек Qt6
#find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)
#
## Главный исполняемый файл
#add_executable(LAB3_3
#        main.cpp
#        Basic_Structures/IDictionary.h
#        Tasks/Histogram.h
#        Sequence/DynamicArray.h
#        Sequence/MutableArraySequence.h
#        Sequence/MutableListSequence.h
#        Pointers/UnqPtr.h
#        Pointers/SharedPtr.h
#        Pointers/WeakPtr.h
#        Basic_Structures/Range.h
#        Basic_Structures/AVLDictionary.h
#        Basic_Structures/AVLTree.h
#        Tasks/Cache.h
#        Basic_Structures/ISet.h
#        Basic_Structures/AVLSet.h
#        Basic_Structures/Queue.h
#        GUI.cpp
#        GUI.h
#        Person.h
#)
#
## Линковка с библиотеками Qt
#target_link_libraries(LAB3_3
#        Qt6::Core
#        Qt6::Gui
#        Qt6::Widgets
#        Qt6::Charts
#)
#
## Установить директорию для дополнительных заголовков
#target_include_directories(LAB3_3 PRIVATE ${PROJECT_SOURCE_DIR}/third_party/googletest/include)
#
## Тесты
#enable_testing()
#add_executable(MyTests
#        Tests/AVLTreeTest.h
#        Tests/AVLDictionaryTest.h
#        Tests/AVLDictionaryTest.cpp
#        Tests/AVLTreeTest.cpp
#        Tests/HistogramTest.cpp
#        Tests/HistogramTest.h
#        Tests/CacheTest.cpp
#        Tests/CacheTest.h
#)
#
## Линковка тестов с GTest
#target_link_libraries(MyTests PRIVATE gtest gtest_main)
#
## Опции компиляции
#target_compile_options(MyTests PRIVATE -O2 -Wall -Wextra)
#
## Регистрация тестов
#add_test(NAME MyTests COMMAND MyTests)

cmake_minimum_required(VERSION 3.29)
project(LAB3_3)

set(CMAKE_CXX_STANDARD 20)

# Включение поддержки Qt для moc, uic и rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Добавление сторонних библиотек
add_subdirectory(third_party/googletest)

# Поиск библиотек Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts)

# Главный исполняемый файл
add_executable(LAB3_3
        main.cpp
        Basic_Structures/IDictionary.h
        Tasks/Histogram.h
        Sequence/DynamicArray.h
        Sequence/MutableArraySequence.h
        Sequence/MutableListSequence.h
        Pointers/UnqPtr.h
        Pointers/SharedPtr.h
        Pointers/WeakPtr.h
        Basic_Structures/Range.h
        Basic_Structures/AVLDictionary.h
        Basic_Structures/AVLTree.h
        Tasks/Cache.h
        Basic_Structures/ISet.h
        Basic_Structures/AVLSet.h
        Basic_Structures/Queue.h
        GUI.cpp
        GUI.h
        Person.h
)

# Линковка с библиотеками Qt
target_link_libraries(LAB3_3
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Charts
)

# Установить директорию для дополнительных заголовков
target_include_directories(LAB3_3 PRIVATE ${PROJECT_SOURCE_DIR}/third_party/googletest/include)

# Тесты
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

# Линковка тестов с GTest
target_link_libraries(MyTests PRIVATE gtest gtest_main)

# Опции компиляции
target_compile_options(MyTests PRIVATE -O2 -Wall -Wextra)

# Отключение AUTOMOC для тестов
set_property(TARGET MyTests PROPERTY AUTOMOC OFF)

# Регистрация тестов
add_test(NAME MyTests COMMAND MyTests)

cmake_minimum_required(VERSION 3.29)
project(Modeling)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(third_party/googletest)

# Основной исполняемый файл
add_executable(Modeling
        main.cpp
        game.cpp
        game.h
        board.cpp
        board.h
        players.cpp
        players.h)

# Исполняемый файл для тестов
add_executable(tests
        tests/test.cpp
        game.cpp
        game.h
        board.cpp
        board.h
        players.cpp
        players.h)

# Подключаем Google Test к тестам
target_link_libraries(tests
        PRIVATE
        gtest_main
        gmock_main)

# Добавляем include директории
target_include_directories(tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include
        ${CMAKE_SOURCE_DIR}/third_party/googletest/googlemock/include
        ${CMAKE_SOURCE_DIR})
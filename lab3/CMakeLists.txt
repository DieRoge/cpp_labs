cmake_minimum_required(VERSION 3.10)
project(Lab3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установка выходных каталогов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Для MSVC
if(MSVC)
    add_compile_options("$<$<CONFIG:Debug>:/MDd>")
    add_compile_options("$<$<CONFIG:Release>:/MD>")
endif()

# GoogleTest
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Основные исходные файлы
set(LIB_SOURCES
    src/point.cpp
    src/vector-points.cpp
    src/vector-figure.cpp
    src/figure.cpp
    src/triangle.cpp
    src/hexagon.cpp
    src/octagon.cpp
)

# Главное приложение
add_executable(Lab3 src/main.cpp ${LIB_SOURCES})
target_include_directories(Lab3 PRIVATE include)

# Тесты
add_executable(run_tests tests/main_test.cpp ${LIB_SOURCES})
target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests PRIVATE gtest_main)

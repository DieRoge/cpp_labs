cmake_minimum_required(VERSION 3.20)
project(Lab4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

add_executable(lab4 src/main.cpp)

target_include_directories(lab4 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/inline
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(MSVC)
    target_compile_options(lab4 PRIVATE /W4)
else()
    target_compile_options(lab4 PRIVATE -Wall -Wextra -Wpedantic)
endif()

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    
    FetchContent_GetProperties(googletest)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif()

    add_executable(tests
        tests/test_main.cpp
        tests/test_array.cpp
        tests/test_point.cpp
        tests/test_figures.cpp
    )

    target_include_directories(tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/inline
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_link_libraries(tests PRIVATE
        gtest_main
        gmock
    )

    include(GoogleTest)
    gtest_discover_tests(tests)

    if(MSVC)
        target_compile_options(tests PRIVATE /W4)
    else()
        target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()
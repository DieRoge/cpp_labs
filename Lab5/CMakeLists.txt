cmake_minimum_required(VERSION 3.10)
project(list)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Windows console fix
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")
endif()

add_executable(list src/main.cpp src/memory_resource.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE include)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra )

enable_testing()

add_executable(tests tests/test.cpp src/memory_resource.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE gtest_main)
target_compile_options(tests PRIVATE -Wall -Wextra )

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)
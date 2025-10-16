cmake_minimum_required(VERSION 3.16)
project(Lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(solver src/decimal.cpp)
target_include_directories(solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(lab2 programm.cpp)
target_link_libraries(lab2 PRIVATE solver)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(solver_tests tests/test.cpp)
target_link_libraries(solver_tests PRIVATE solver GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(solver_tests)

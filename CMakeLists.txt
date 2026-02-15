cmake_minimum_required(VERSION 3.20)

project(semp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(semp_lib
  src/lexer.cpp
)

# Main
add_executable(semp
  src/main.cpp
)

target_link_libraries(semp
  semp_lib
)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Tests
add_executable(
  lexer_test
  tests/lexer_test.cpp
)

target_link_libraries(
  lexer_test
  GTest::gtest_main
  semp_lib
)

include(GoogleTest)
gtest_discover_tests(lexer_test)

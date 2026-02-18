cmake_minimum_required(VERSION 3.20)

project(semp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# C-lang

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")

    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
    )

    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_EXE} -i ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Formatting all source files"
    )

else()
    message(WARNING "clang-format NOT found! Formatting disabled.")
endif()

# Linter
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" 
      "-checks=bugprone-*,cert-*,performance-*,portability-*,modernize-use-auto,modernize-use-nullptr"
      "-warnings-as-errors=*"
    )
else()
    message(WARNING "clang-tidy NOT found! Linting disabled.")
endif()

add_library(semp_lib
  src/lexer.cpp
)

target_include_directories(semp_lib PUBLIC include)

# Main
add_executable(semp
  src/main.cpp
)

target_link_libraries(semp
  semp_lib
)

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

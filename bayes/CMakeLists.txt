# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define project name
project(BlackjackBayes CXX)

set(CMAKE_CXX_STANDARD 20)

# Add a library target
add_library(blackjack_bayes src/bayes.cpp)

target_include_directories(blackjack_bayes PUBLIC include)

# Add an executable target
# add_executable(main src/main.c)

option(BUILD_TESTS "Enable building tests" ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()


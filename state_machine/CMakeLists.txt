# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define project name
project(BlackjackStateMachine CXX)

set(CMAKE_CXX_STANDARD 20)

# Header-only library target
add_library(blackjack_state_machine INTERFACE)

target_include_directories(blackjack_state_machine INTERFACE include)

option(BUILD_TESTS "Enable building tests" ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

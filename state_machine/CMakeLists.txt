# Set minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Define project name
project(BlackjackStateMachine CXX)

set(CMAKE_CXX_STANDARD 20)

# Add a library target
add_library(blackjack_state_machine src/state_machine.cpp)

target_include_directories(blackjack_state_machine PUBLIC include)

option(BUILD_TESTS "Enable building tests" ON)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

cmake_minimum_required(VERSION 3.15)

project(BlackjackStateMachineTests LANGUAGES CXX)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
               state_machine.cpp)

target_link_libraries(unit_tests blackjack_state_machine gtest_main)

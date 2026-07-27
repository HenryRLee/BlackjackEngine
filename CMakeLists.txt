# Set minimum required CMake version
cmake_minimum_required(VERSION 3.15)

# Define project name
project(BlackjackEngine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Enable building tests" ON)

if(BUILD_TESTS)
  enable_testing()

  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
  )

  FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(state_machine)
add_subdirectory(bayes)

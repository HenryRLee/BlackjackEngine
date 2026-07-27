# The state machine library.
add_library(blackjack_state_machine src/state_machine.cpp)

target_include_directories(blackjack_state_machine PUBLIC include)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

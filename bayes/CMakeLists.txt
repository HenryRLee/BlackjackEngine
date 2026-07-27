# The Bayes expected-value library, built on top of the state machine.
add_library(blackjack_bayes src/bayes.cpp)

target_include_directories(blackjack_bayes PUBLIC include)

target_link_libraries(blackjack_bayes PUBLIC blackjack_state_machine)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()

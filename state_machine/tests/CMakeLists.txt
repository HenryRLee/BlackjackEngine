add_executable(state_machine_tests
               state_machine_tests.cpp
               hand_tests.cpp)

target_link_libraries(state_machine_tests blackjack_state_machine gtest_main)

add_test(NAME state_machine_tests COMMAND state_machine_tests)

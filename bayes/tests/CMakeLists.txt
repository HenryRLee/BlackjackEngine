add_executable(bayes_tests
               bayes_macau_tests.cpp)

target_link_libraries(bayes_tests blackjack_bayes gtest_main)

add_test(NAME bayes_tests COMMAND bayes_tests)

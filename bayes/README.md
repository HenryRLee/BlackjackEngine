# Blackjack Bayes

This project is a library that uses Bayes' theorem to calculate the expected value of an action
based on a Blackjack state.

# Build

The following command builds the library and the unit test binary:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

It will generate the library:

```bash
$ ls build/libblackjack_bayes.a
build/libblackjack_bayes.a
```

And the unit test binary:
```bash
$ ls build/tests/unit_tests
build/tests/unit_tests
```

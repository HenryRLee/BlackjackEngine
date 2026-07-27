# Blackjack Engine

This project models Blackjack as a state machine and, on top of it, uses Bayes'
theorem to calculate the expected value of an action for a given Blackjack state.

## Layout

- `state_machine/` — the `BlackjackEngine::StateMachine` library: hands, rules,
  states, and the transitions between them.
- `bayes/` — the `BlackjackEngine::Bayes` library: an expected-value calculator
  built on top of the state machine.

## Build

The following commands build the libraries and the unit test binaries from the
repository root:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

This produces the two libraries:

```bash
$ ls build/state_machine/libblackjack_state_machine.a build/bayes/libblackjack_bayes.a
build/bayes/libblackjack_bayes.a  build/state_machine/libblackjack_state_machine.a
```

## Test

Run the whole test suite with CTest from the build directory:

```bash
ctest --test-dir build
```

The individual test binaries are `build/state_machine/tests/state_machine_tests`
and `build/bayes/tests/bayes_tests`.

#ifndef ACTION_H
#define ACTION_H

namespace BlackjackEngine::StateMachine {

// The set of actions available to whoever is acting, stored as a bit mask.
// For the player this is a subset of {Hit, Stand, Double}; for the dealer it is
// the single action the ruleset forces (Hit or Stand); for a finished round it
// is None.
enum class Action : unsigned char {
  None = 0,
  Hit = 1u << 0,
  Stand = 1u << 1,
  Double = 1u << 2,
  Split = 1u << 3,
};

constexpr Action operator|(Action a, Action b) {
  return static_cast<Action>(static_cast<unsigned char>(a) |
                             static_cast<unsigned char>(b));
}

constexpr Action operator&(Action a, Action b) {
  return static_cast<Action>(static_cast<unsigned char>(a) &
                             static_cast<unsigned char>(b));
}

constexpr Action operator~(Action a) {
  return static_cast<Action>(~static_cast<unsigned char>(a));
}

constexpr Action& operator|=(Action& a, Action b) {
  a = a | b;
  return a;
}

constexpr Action& operator&=(Action& a, Action b) {
  a = a & b;
  return a;
}

// True when the given single action is present in the set.
constexpr bool IsAllowed(Action set, Action action) {
  return (set & action) == action;
}

}  // namespace BlackjackEngine::StateMachine

#endif  // ACTION_H

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "card.h"
#include "ruleset.h"
#include "state.h"

namespace BlackjackEngine::StateMachine {

// The result of a finished round, from the player's perspective.
enum class Outcome : signed char {
  PlayerLoses = -1,
  Push = 0,
  PlayerWins = 1,
};

// ---------------------------------------------------------------------------
// Helper functions: inspect a state without changing it.
// ---------------------------------------------------------------------------

// True once the round has finished and only an Outcome remains.
bool IsTerminal(const State& state);

// Outcome of a terminal state, comparing the two hands.
Outcome Result(const State& state);

// ---------------------------------------------------------------------------
// Transition functions: produce the next state from the current one.
// ---------------------------------------------------------------------------

// Build a starting state. Double is stripped from the allowed actions unless
// the double requirement is met (it is the player's turn holding exactly two
// cards). A dealer-turn state is advanced straight to the dealer's forced
// state.
State InitiateState(const RuleSet& ruleset, Turn turn, PlayerHand playerHand,
                    DealerHand dealerHand,
                    Action allowedActions = Action::Hit | Action::Stand |
                                            Action::Double);

// Stand: the acting party takes no more cards. On the player's turn play passes
// to the dealer, who is advanced to their next forced state; on the dealer's
// turn the round ends with no further actions.
State Stand(const RuleSet& ruleset, const State& state);

// A card is drawn for whoever is acting. On the player's turn it is added to
// the player hand; the hand may no longer double, and a bust ends the round. On
// the dealer's turn it is added to the dealer hand and the dealer is advanced
// to their next forced state.
State Hit(const RuleSet& ruleset, const State& state, Card card);

// Double: a single card is drawn, after which the acting party may only stand;
// the following Stand passes play to the dealer. Currently only the player is
// allowed to double.
State Double(const State& state, Card card);

}  // namespace BlackjackEngine::StateMachine

#endif  // STATE_MACHINE_H

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "card.h"
#include "ruleset.h"
#include "state.h"

namespace BlackjackEngine {

// A decision the player may take on their turn.
enum class Action : unsigned char {
  Hit,
  Stand,
  Double,
};

// The result of a finished round, from the player's perspective.
enum class Outcome : signed char {
  PlayerLoses = -1,
  Push = 0,
  PlayerWins = 1,
};

// True once the round has finished and only an Outcome remains.
bool IsTerminal(const State& state);

// True when the player is allowed to double, i.e. it is their turn and they
// still hold exactly their two initial cards.
bool CanDouble(const State& state);

// Player decisions. Hit and Double consume a drawn card.
State Stand(const State& state);
State Hit(const State& state, Card card);
State Double(const State& state, Card card);

// Dealer play is forced by the ruleset. DealerShouldHit answers whether the
// dealer must draw again; DealerDraw applies a drawn card and moves the round
// to End once the dealer is done.
bool DealerShouldHit(const RuleSet& ruleset, const State& state);
State DealerDraw(const RuleSet& ruleset, const State& state, Card card);

// Outcome of a terminal state, comparing the two hands.
Outcome Result(const State& state);

} // namespace BlackjackEngine

#endif // STATE_MACHINE_H

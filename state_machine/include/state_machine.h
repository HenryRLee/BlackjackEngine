#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "card.h"
#include "ruleset.h"
#include "state.h"

#include <cassert>

namespace BlackjackEngine {

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
constexpr bool IsTerminal(const State& state) {
  return state.turn == Turn::End;
}

// Whether the dealer is forced to draw again under the ruleset.
constexpr bool DealerShouldHit(const RuleSet& ruleset, const State& state) {
  const DealerHand& hand = state.dealerHand;

  if (hand.score < 17)
    return true;

  if (hand.score > 17)
    return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

// Outcome of a terminal state, comparing the two hands.
constexpr Outcome Result(const State& state) {
  const PlayerHand& player = state.playerHand;
  const DealerHand& dealer = state.dealerHand;

  if (player.score > 21)
    return Outcome::PlayerLoses;

  if (dealer.score > 21)
    return Outcome::PlayerWins;

  // Blackjacks (a two-card 21) are settled before comparing totals: two
  // blackjacks push, otherwise the side holding the blackjack wins.
  const bool playerBlackjack = player.numCards == 2 && player.score == 21;
  const bool dealerBlackjack = dealer.numCards == 2 && dealer.score == 21;

  if (playerBlackjack || dealerBlackjack) {
    if (playerBlackjack && dealerBlackjack)
      return Outcome::Push;

    return playerBlackjack ? Outcome::PlayerWins : Outcome::PlayerLoses;
  }

  if (dealer.score > player.score)
    return Outcome::PlayerLoses;

  if (dealer.score < player.score)
    return Outcome::PlayerWins;

  return Outcome::Push;
}

// ---------------------------------------------------------------------------
// Transition functions: produce the next state from the current one.
// ---------------------------------------------------------------------------

// Advance a state into the dealer's turn: the dealer keeps hitting while the
// ruleset requires it, so a dealer-turn state always has Hit as its only
// allowed action. Once the dealer must stand, the round is finished. Used
// internally by Stand and Hit.
constexpr State EnterDealer(const RuleSet& ruleset, State state) {
  if (DealerShouldHit(ruleset, state)) {
    state.turn = Turn::Dealer;
    state.allowedActions = Action::Hit;
  } else {
    state.turn = Turn::End;
    state.allowedActions = Action::None;
  }

  return state;
}

// Build a starting state. Double is stripped from the allowed actions unless the
// double requirement is met (it is the player's turn holding exactly two cards).
// A dealer-turn state is advanced straight to the dealer's forced state.
constexpr State InitiateState(const RuleSet& ruleset, Turn turn,
                              PlayerHand playerHand, DealerHand dealerHand,
                              Action allowedActions = Action::Hit | Action::Stand | Action::Double) {
  if (turn != Turn::Player || playerHand.numCards != 2)
    allowedActions &= ~Action::Double;

  State state(turn, playerHand, dealerHand, allowedActions);

  if (turn == Turn::Dealer)
    return EnterDealer(ruleset, state);

  return state;
}

// Stand: the acting party takes no more cards. On the player's turn play passes
// to the dealer, who is advanced to their next forced state; on the dealer's
// turn the round ends with no further actions.
constexpr State Stand(const RuleSet& ruleset, const State& state) {
  State next = state;

  if (state.turn == Turn::Player)
    return EnterDealer(ruleset, next);

  next.turn = Turn::End;
  next.allowedActions = Action::None;
  return next;
}

// A card is drawn for whoever is acting. On the player's turn it is added to the
// player hand; the hand may no longer double, and a bust ends the round. On the
// dealer's turn it is added to the dealer hand and the dealer is advanced to
// their next forced state.
constexpr State Hit(const RuleSet& ruleset, const State& state, Card card) {
  assert(IsAllowed(state.allowedActions, Action::Hit));

  State next = state;

  if (state.turn != Turn::Player) {
    next.dealerHand = next.dealerHand + card;
    return EnterDealer(ruleset, next);
  }

  next.playerHand = next.playerHand + card;
  next.allowedActions &= ~Action::Double;

  if (next.playerHand.score > 21) {
    next.turn = Turn::End;
    next.allowedActions = Action::None;
  }

  return next;
}

// Double: a single card is drawn, after which the acting party may only stand;
// the following Stand passes play to the dealer. Currently only the player is
// allowed to double.
constexpr State Double(const State& state, Card card) {
  assert(state.turn == Turn::Player);
  assert(IsAllowed(state.allowedActions, Action::Double));

  State next = state;
  next.playerHand = next.playerHand + card;
  next.allowedActions &= ~(Action::Hit | Action::Double);
  return next;
}

} // namespace BlackjackEngine

#endif // STATE_MACHINE_H

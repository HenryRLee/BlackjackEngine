#include "state_machine.h"

#include <cassert>

namespace BlackjackEngine::StateMachine {

namespace {

// Whether the dealer is forced to draw again under the ruleset.
bool DealerShouldHit(const RuleSet& ruleset, const State& state) {
  const DealerHand& hand = state.dealerHand;

  if (hand.score < 17) return true;

  if (hand.score > 17) return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

// Advance a state into the dealer's turn: the dealer keeps hitting while the
// ruleset requires it, so a dealer-turn state always has Hit as its only
// allowed action. Once the dealer must stand, the round is finished. Used
// internally by Stand, Hit, and InitiateState.
State EnterDealer(const RuleSet& ruleset, State state) {
  if (DealerShouldHit(ruleset, state)) {
    state.turn = Turn::Dealer;
    state.allowedActions = Action::Hit;
  } else {
    state.turn = Turn::End;
    state.allowedActions = Action::None;
  }

  return state;
}

}  // namespace

bool IsTerminal(const State& state) { return state.turn == Turn::End; }

Outcome Result(const State& state) {
  const PlayerHand& player = state.playerHand;
  const DealerHand& dealer = state.dealerHand;

  if (player.score > 21) return Outcome::PlayerLoses;

  if (dealer.score > 21) return Outcome::PlayerWins;

  // Blackjacks (a two-card 21) are settled before comparing totals: two
  // blackjacks push, otherwise the side holding the blackjack wins.
  const bool playerBlackjack = player.numCards == 2 && player.score == 21;
  const bool dealerBlackjack = dealer.numCards == 2 && dealer.score == 21;

  if (playerBlackjack || dealerBlackjack) {
    if (playerBlackjack && dealerBlackjack) return Outcome::Push;

    return playerBlackjack ? Outcome::PlayerWins : Outcome::PlayerLoses;
  }

  if (dealer.score > player.score) return Outcome::PlayerLoses;

  if (dealer.score < player.score) return Outcome::PlayerWins;

  return Outcome::Push;
}

State InitiateState(const RuleSet& ruleset, Turn turn, PlayerHand playerHand,
                    DealerHand dealerHand, Action allowedActions) {
  if (turn != Turn::Player || playerHand.numCards != 2)
    allowedActions &= ~Action::Double;

  State state(turn, playerHand, dealerHand, allowedActions);

  if (turn == Turn::Dealer) return EnterDealer(ruleset, state);

  return state;
}

State Stand(const RuleSet& ruleset, const State& state) {
  State next = state;

  if (state.turn == Turn::Player) return EnterDealer(ruleset, next);

  next.turn = Turn::End;
  next.allowedActions = Action::None;
  return next;
}

State Hit(const RuleSet& ruleset, const State& state, Card card) {
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

State Double(const State& state, Card card) {
  assert(state.turn == Turn::Player);
  assert(IsAllowed(state.allowedActions, Action::Double));

  State next = state;
  next.playerHand = next.playerHand + card;
  next.allowedActions &= ~(Action::Hit | Action::Double);
  return next;
}

}  // namespace BlackjackEngine::StateMachine

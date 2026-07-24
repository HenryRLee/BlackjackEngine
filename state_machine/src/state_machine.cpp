#include "state_machine.h"

namespace BlackjackEngine {

bool IsTerminal(const State& state) {
  return state.turn == Turn::End;
}

bool CanDouble(const State& state) {
  return state.turn == Turn::Player && state.playerHand.numCards == 2;
}

State Stand(const State& state) {
  State next = state;
  next.turn = Turn::Dealer;
  return next;
}

State Hit(const State& state, Card card) {
  State next = state;
  next.playerHand = next.playerHand + card;

  // A bust ends the round immediately; the dealer need not play.
  if (next.playerHand.score > 21)
    next.turn = Turn::End;

  return next;
}

State Double(const State& state, Card card) {
  State next = state;
  next.playerHand = next.playerHand + card;
  next.turn = Turn::Dealer;
  return next;
}

bool DealerShouldHit(const RuleSet& ruleset, const State& state) {
  const DealerHand& hand = state.dealerHand;

  if (hand.score < 17)
    return true;

  if (hand.score > 17)
    return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

State DealerDraw(const RuleSet& ruleset, const State& state, Card card) {
  State next = state;
  next.dealerHand = next.dealerHand + card;

  if (!DealerShouldHit(ruleset, next))
    next.turn = Turn::End;

  return next;
}

Outcome Result(const State& state) {
  const PlayerHand& player = state.playerHand;
  const DealerHand& dealer = state.dealerHand;

  if (player.score > 21)
    return Outcome::PlayerLoses;

  if (dealer.score > 21)
    return Outcome::PlayerWins;

  // A dealer natural (21 on the first two cards) beats any player hand that is
  // not itself a blackjack; matching the Bayes model, we assume the player has
  // already been resolved for a blackjack before this point.
  if (dealer.numCards == 2 && dealer.score == 21)
    return Outcome::PlayerLoses;

  if (dealer.score > player.score)
    return Outcome::PlayerLoses;

  if (dealer.score < player.score)
    return Outcome::PlayerWins;

  return Outcome::Push;
}

} // namespace BlackjackEngine

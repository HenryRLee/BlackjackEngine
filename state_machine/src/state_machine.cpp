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

// Advance a state by recalculate the allowed actions for player.
// Used internally by Hit and Split. Double doesn't need to come here
// since Stand is the only allowed action after doubling.
State EnterPlayer(const RuleSet& ruleset, const State& state) {
  assert(state.turn == Turn::Player);

  Action actions = state.allowedActions;

  if (state.playerHand.numCards < 2) {
    actions &= ~Action::Stand;
    actions |= Action::Hit;

  } else {
    actions |= Action::Stand;
  }

  if (state.playerHand.numCards != 2) {
    actions &= ~(Action::Double | Action::Split);
  } else {
    // Stand on split aces
    if (state.splitCardScore == 11 && ruleset.standOnSplitAces) {
      actions &= ~(Action::Hit | Action::Double | Action::Split);

      // Still allow re-split if aces are drawn and resplitAces is enabled.
      if (ruleset.resplitAces && state.splitDepth < ruleset.maxSplittedHands &&
          state.playerHand.score == 12 && state.playerHand.isSoft) {
        actions |= Action::Split;
      }
    } else {
      // Re-enable Double for split hands that just received their second card.
      if (state.splitDepth > 0 && ruleset.doubleOnSplits) {
        actions |= Action::Double;
      }

      // Re-enable Split only when the drawn card matches the original split card.
      // For non-aces: hand score == splitCardScore * 2.
      // For aces (splitCardScore == 11): hand is soft 12 (11 + 11 wraps).
      bool drawnCardMatchesSplit =
          state.splitCardScore > 0 &&
          (state.playerHand.score == state.splitCardScore * 2 ||
           (state.splitCardScore == 11 && ruleset.resplitAces &&
            state.playerHand.score == 12 && state.playerHand.isSoft));
      if (state.splitDepth > 0 && state.splitDepth < ruleset.maxSplittedHands &&
          drawnCardMatchesSplit) {
        actions |= Action::Split;
      }

      if (state.playerHand.score % 2 != 0) {
        actions &= ~Action::Split;
      } else if (state.playerHand.isSoft && state.playerHand.score != 12) {
        actions &= ~Action::Split;
      }
    }
  }

  State next = state;
  next.allowedActions = actions;

  return next;
}

// Advance a state into the dealer's turn: the dealer keeps hitting while the
// ruleset requires it, so a dealer-turn state always has Hit as its only
// allowed action. Once the dealer must stand, the round is finished. Used
// internally by Stand, Hit, and InitializeState.
State EnterDealer(const RuleSet& ruleset, State state) {
  assert(state.turn <= Turn::Dealer);

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
  const bool playerBlackjack = player.numCards == 2 && player.score == 21 && state.splitDepth == 0;
  const bool dealerBlackjack = dealer.numCards == 2 && dealer.score == 21;

  if (playerBlackjack || dealerBlackjack) {
    if (playerBlackjack && dealerBlackjack) return Outcome::Push;

    return playerBlackjack ? Outcome::PlayerWins : Outcome::PlayerLoses;
  }

  if (dealer.score > player.score) return Outcome::PlayerLoses;

  if (dealer.score < player.score) return Outcome::PlayerWins;

  return Outcome::Push;
}

State InitializeState(const RuleSet& ruleset, Turn turn, PlayerHand playerHand,
                    DealerHand dealerHand, Action allowedActions) {
  const State state(turn, playerHand, dealerHand, allowedActions);

  if (turn == Turn::Player)
    return EnterPlayer(ruleset, state);
  else
    return EnterDealer(ruleset, state);
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

  if (next.playerHand.score > 21) {
    next.turn = Turn::End;
    next.allowedActions = Action::None;

    return next;
  } else {
    return EnterPlayer(ruleset, next);
  }
}

State Double(const State& state, Card card) {
  assert(state.turn == Turn::Player);
  assert(IsAllowed(state.allowedActions, Action::Double));

  State next = state;
  next.playerHand = next.playerHand + card;
  next.allowedActions &= ~(Action::Hit | Action::Double | Action::Split);
  return next;
}

std::pair<State, State> Split(const RuleSet& ruleset, const State& state) {
  assert(state.turn == Turn::Player);
  assert(IsAllowed(state.allowedActions, Action::Split));
  assert(state.playerHand.numCards == 2);
  assert(state.playerHand.score % 2 == 0);
  assert(!state.playerHand.isSoft || state.playerHand.score == 12);

  State first = state;

  if (state.playerHand.score == 12 && state.playerHand.isSoft) {
    // two aces
    first.playerHand.score = 11;

    if (!ruleset.resplitAces) {
      first.allowedActions &= ~Action::Split;
    }
  } else {
    first.playerHand.score = state.playerHand.score / 2;
  }

  first.playerHand.numCards = 1;
  first.splitDepth = state.splitDepth + 1;
  first.splitCardScore = first.playerHand.score;

  State second = first;

  return {EnterPlayer(ruleset, first), EnterPlayer(ruleset, second)};
}

}  // namespace BlackjackEngine::StateMachine

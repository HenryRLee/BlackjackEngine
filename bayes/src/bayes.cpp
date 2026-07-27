#include "bayes.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include <numeric>
#include <ranges>

#include "state_machine.h"

using namespace BlackjackEngine::StateMachine;

namespace BlackjackEngine::Bayes {

constexpr std::array<Card, 10> AllCards() {
  return {
      Card(2), Card(3), Card(4), Card(5),  Card(6),
      Card(7), Card(8), Card(9), Card(10), Card(11),
  };
};

constexpr Probability ProbOfGettingOneCard(Card card) {
  if (card.score == 10)
    return Probability(double(4) / 13);
  else
    return Probability(double(1) / 13);
}

constexpr ExpectedValue OutcomeValue(Outcome outcome) {
  return ExpectedValue(static_cast<double>(static_cast<signed char>(outcome)));
}

// The value of playing a state optimally.
ExpectedValue EvBest(const RuleSet& ruleset, const State& state);

// EV of hitting: draw a card, then play the resulting state optimally.
ExpectedValue EvHits(const RuleSet& ruleset, const State& state) {
  auto allCards = std::views::all(AllCards());
  return std::accumulate(
      allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, state](ExpectedValue current, Card card) {
        return ExpectedValue(
            current.value +
            ProbOfGettingOneCard(card).value *
                EvBest(ruleset, Hit(ruleset, state, card)).value);
      });
}

// EV of standing: hand play over to the next state and play it optimally.
ExpectedValue EvStands(const RuleSet& ruleset, const State& state) {
  return EvBest(ruleset, Stand(ruleset, state));
}

// EV of doubling: draw a single card for twice the stake, then play the
// resulting state optimally (only standing remains).
ExpectedValue EvDoubles(const RuleSet& ruleset, const State& state) {
  auto allCards = std::views::all(AllCards());
  return std::accumulate(
      allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, state](ExpectedValue current, Card card) {
        return ExpectedValue(current.value +
                             2.0 * ProbOfGettingOneCard(card).value *
                                 EvBest(ruleset, Double(state, card)).value);
      });
}

// Value of playing a state optimally: a terminal state is simply scored,
// otherwise it is the greatest expected value over every allowed action. This
// drives both the player's choices and the dealer's forced play, since a
// dealer-turn state only ever allows Hit.
ExpectedValue EvBest(const RuleSet& ruleset, const State& state) {
  if (IsTerminal(state)) return OutcomeValue(Result(state));

  // A non-terminal state must offer at least one action, otherwise the fallback
  // below would return negative infinity.
  assert(state.allowedActions != Action::None);

  ExpectedValue best(-std::numeric_limits<double>::infinity());

  if (IsAllowed(state.allowedActions, Action::Hit))
    best = std::max(best, EvHits(ruleset, state));

  if (IsAllowed(state.allowedActions, Action::Stand))
    best = std::max(best, EvStands(ruleset, state));

  if (IsAllowed(state.allowedActions, Action::Double))
    best = std::max(best, EvDoubles(ruleset, state));

  return best;
}

ExpectedValue EvPlayerBestAction(const RuleSet& ruleset, PlayerHand playerHand,
                                 DealerHand dealerHand) {
  return EvBest(ruleset,
                InitiateState(ruleset, Turn::Player, playerHand, dealerHand));
}

ExpectedValue EvPlayerStands(const RuleSet& ruleset, PlayerHand playerHand,
                             DealerHand dealerHand) {
  return EvStands(ruleset,
                  InitiateState(ruleset, Turn::Player, playerHand, dealerHand));
}

ExpectedValue EvPlayerHits(const RuleSet& ruleset, PlayerHand playerHand,
                           DealerHand dealerHand) {
  return EvHits(ruleset,
                InitiateState(ruleset, Turn::Player, playerHand, dealerHand));
}

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset, PlayerHand playerHand,
                              DealerHand dealerHand) {
  return EvDoubles(
      ruleset, InitiateState(ruleset, Turn::Player, playerHand, dealerHand));
}

}  // namespace BlackjackEngine::Bayes

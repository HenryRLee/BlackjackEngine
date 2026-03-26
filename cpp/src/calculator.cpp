#include "calculator.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>

static constexpr bool HitFromDealer(const RuleSet& ruleset, DealerHandScore hand) {
  if (hand.score < 17)
    return true;

  if (hand.score > 17)
    return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

static constexpr std::array<CardScore, 10> AllCards() {
  return {
    CardScore(2),
    CardScore(3),
    CardScore(4),
    CardScore(5),
    CardScore(6),
    CardScore(7),
    CardScore(8),
    CardScore(9),
    CardScore(10),
    CardScore(11),
  };
};

static constexpr Probability ProbOfGettingOneCard(CardScore card) {
  if (card.score == 10)
    return Probability(double(4) / 13);
  else
    return Probability(double(1) / 13);
}

ExpectedValue EvDealerTurn(const RuleSet& ruleset,
                           PlayerHandScore playerHand, DealerHandScore dealerHand) {
  if (HitFromDealer(ruleset, dealerHand)) {
    auto allCards = std::views::all(AllCards());
    return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
        [&ruleset, playerHand, dealerHand] (ExpectedValue current, CardScore card) {
          const DealerHandScore newDealerHand = dealerHand + card;
          return ExpectedValue(current.value +
              ProbOfGettingOneCard(card).value * EvDealerTurn(ruleset, playerHand, newDealerHand).value);
        });
  } else {
    if (dealerHand.score > 21)
      return ExpectedValue(1.0);

    if (dealerHand.score > playerHand.score)
      return ExpectedValue(-1.0);
    else if (dealerHand.score < playerHand.score)
      return ExpectedValue(1.0);
    else
      return ExpectedValue(0.0);
  }
}

ExpectedValue EvPlayerHitsOrStands(const RuleSet& ruleset,
                                   PlayerHandScore playerHand, DealerHandScore dealerHand) {
  if (playerHand.score > 21)
    return ExpectedValue(-1.0);

  const ExpectedValue evHit = EvPlayerHits(ruleset, playerHand, dealerHand);
  const ExpectedValue evStand = EvPlayerStands(ruleset, playerHand, dealerHand);

  return std::max(evHit, evStand);
}

ExpectedValue EvPlayerStands(const RuleSet& ruleset,
                             PlayerHandScore playerHand, DealerHandScore dealerHand) {
  return EvDealerTurn(ruleset, playerHand, dealerHand);
}

ExpectedValue EvPlayerHits(const RuleSet& ruleset,
                           PlayerHandScore playerHand, DealerHandScore dealerHand) {
  auto allCards = std::views::all(AllCards());
  return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, playerHand, dealerHand] (ExpectedValue current, CardScore card) {
        const DealerHandScore newPlayerHand = playerHand + card;
        return ExpectedValue(current.value +
            ProbOfGettingOneCard(card).value *
            EvPlayerHitsOrStands(ruleset, newPlayerHand, dealerHand).value);
      });
}

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset,
                              PlayerHandScore playerHand, DealerHandScore dealerHand) {
  auto allCards = std::views::all(AllCards());
  return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, playerHand, dealerHand] (ExpectedValue current, CardScore card) {
        const DealerHandScore newPlayerHand = playerHand + card;
        return ExpectedValue(current.value +
            2.0 * ProbOfGettingOneCard(card).value * EvPlayerStands(ruleset, newPlayerHand, dealerHand).value);
      });
}

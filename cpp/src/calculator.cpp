#include "calculator.h"
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


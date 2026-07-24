#include "bayes.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>

namespace BlackjackEngine::Bayes {

constexpr bool HitFromDealer(const RuleSet& ruleset, DealerHand hand) {
  if (hand.score < 17)
    return true;

  if (hand.score > 17)
    return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

constexpr std::array<Card, 10> AllCards() {
  return {
    Card(2),
    Card(3),
    Card(4),
    Card(5),
    Card(6),
    Card(7),
    Card(8),
    Card(9),
    Card(10),
    Card(11),
  };
};

constexpr Probability ProbOfGettingOneCard(Card card) {
  if (card.score == 10)
    return Probability(double(4) / 13);
  else
    return Probability(double(1) / 13);
}

ExpectedValue EvDealerRemainingRounds(const RuleSet& ruleset,
                                      PlayerHand playerHand, DealerHand dealerHand) {
  if (HitFromDealer(ruleset, dealerHand)) {
    auto allCards = std::views::all(AllCards());
    return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
        [&ruleset, playerHand, dealerHand] (ExpectedValue current, Card card) {
          const DealerHand newDealerHand = dealerHand + card;
          return ExpectedValue(current.value +
              ProbOfGettingOneCard(card).value *
              EvDealerRemainingRounds(ruleset, playerHand, newDealerHand).value);
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

ExpectedValue EvDealerFirstRound(const RuleSet& ruleset,
                                 PlayerHand playerHand, DealerHand dealerHand) {
  /*
   * We need to deal with the special case that dealer draws a Blackjack.
   * At this point, we assume the player doesn't have a Blackjack.
   * And the dealer should have only one card in his hand at the moment.
   * If the dealer card is not an Ace or anything value at 10, we can run the normal evaluation
   *   with EvDealerRemainingRounds.
   */
  if (dealerHand.score != 10 && dealerHand.score != 11)
    return EvDealerRemainingRounds(ruleset, playerHand, dealerHand);

  auto allCards = std::views::all(AllCards());
  return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, playerHand, dealerHand] (ExpectedValue current, Card card) {
        const DealerHand newDealerHand = dealerHand + card;
        // Only two cards so far, this must be a Blackjack
        // The dealer wins regardless of the player score
        if (newDealerHand.score == 21) {
          return ExpectedValue(current.value +
              ProbOfGettingOneCard(card).value * -1.0);
        }

        return ExpectedValue(current.value +
            ProbOfGettingOneCard(card).value *
            EvDealerRemainingRounds(ruleset, playerHand, newDealerHand).value);
      });

}

ExpectedValue EvPlayerHitsOrStands(const RuleSet& ruleset,
                                   PlayerHand playerHand, DealerHand dealerHand) {
  if (playerHand.score > 21)
    return ExpectedValue(-1.0);

  const ExpectedValue evHit = EvPlayerHits(ruleset, playerHand, dealerHand);
  const ExpectedValue evStand = EvPlayerStands(ruleset, playerHand, dealerHand);

  return std::max(evHit, evStand);
}

ExpectedValue EvPlayerStands(const RuleSet& ruleset,
                             PlayerHand playerHand, DealerHand dealerHand) {
  return EvDealerFirstRound(ruleset, playerHand, dealerHand);
}

ExpectedValue EvPlayerHits(const RuleSet& ruleset,
                           PlayerHand playerHand, DealerHand dealerHand) {
  auto allCards = std::views::all(AllCards());
  return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, playerHand, dealerHand] (ExpectedValue current, Card card) {
        const PlayerHand newPlayerHand = playerHand + card;
        return ExpectedValue(current.value +
            ProbOfGettingOneCard(card).value *
            EvPlayerHitsOrStands(ruleset, newPlayerHand, dealerHand).value);
      });
}

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset,
                              PlayerHand playerHand, DealerHand dealerHand) {
  auto allCards = std::views::all(AllCards());
  return std::reduce(allCards.begin(), allCards.end(), ExpectedValue(0.0),
      [&ruleset, playerHand, dealerHand] (ExpectedValue current, Card card) {
        const DealerHand newPlayerHand = playerHand + card;
        return ExpectedValue(current.value +
            2.0 * ProbOfGettingOneCard(card).value * EvPlayerStands(ruleset, newPlayerHand, dealerHand).value);
      });
}

} // namespace BlackjackEngine::Bayes

#include "calculator.h"

static bool HitFromDealer(const RuleSet& ruleset, HandScore hand) {
  if (hand.score < 17)
    return true;

  if (hand.score > 17)
    return false;

  return hand.isSoft && ruleset.hitOnSoft17;
}

ExpectedValue EVDealerTurn(const RuleSet& ruleset, HandScore hand) {
  if (HitFromDealer(ruleset, hand)) {
  }
  return ExpectedValue(0.0);
}


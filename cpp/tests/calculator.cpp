#include <gtest/gtest.h>
#include "calculator.h"

constexpr double Epsilon = 0.000001;

TEST(EvTests, TestPlayer21Dealer16Stand) {
  const PlayerHandScore playerHand(21);
  const DealerHandScore dealerHand(16);

  RuleSet ruleset;

  const ExpectedValue ev = EvDealerTurn(ruleset, playerHand, dealerHand);

  EXPECT_NEAR(ev.value, 0.923077, Epsilon);
}

#include <gtest/gtest.h>
#include "calculator.h"

constexpr double Epsilon = 0.000001;

TEST(EvTests, TestPlayer21Dealer16Stand) {
  const ExpectedValue ev = EvDealerTurn(RuleSet(), PlayerHandScore(21), DealerHandScore(16));
  EXPECT_NEAR(ev.value, 0.923077, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHandScore(16), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.509322, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Stand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHandScore(16), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9HitOrStand) {
  const ExpectedValue ev = EvPlayerHitsOrStands(RuleSet(), PlayerHandScore(16), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.509322, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHandScore(13), DealerHandScore(6));
  EXPECT_NEAR(ev.value, -0.235626, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Stand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHandScore(13), DealerHandScore(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6HitOrStand) {
  const ExpectedValue ev = EvPlayerHitsOrStands(RuleSet(), PlayerHandScore(13), DealerHandScore(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer10Dealer6Double) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHandScore(10), DealerHandScore(6));
  EXPECT_NEAR(ev.value, 0.575590, Epsilon);
}

TEST(EvTests, TestPlayer11Dealer7Double) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHandScore(11), DealerHandScore(7));
  EXPECT_NEAR(ev.value, 0.462889, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHandScore(16, true), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.148644, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Stands) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHandScore(16, true), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Doubles) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHandScore(16, true), DealerHandScore(9));
  EXPECT_NEAR(ev.value, -0.456367, Epsilon);
}

TEST(EvTests, TestPlayerSoft19DealerSoft11Stands) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHandScore(19, true), DealerHandScore(11, true));
  EXPECT_NEAR(ev.value, -0.115483, Epsilon);
}

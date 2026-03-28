#include <gtest/gtest.h>
#include "bayes.h"

using namespace BlackjackBayes;

constexpr double Epsilon = 0.000001;

TEST(EvTests, TestPlayer16Dealer9Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.509322, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Stand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9HitOrStand) {
  const ExpectedValue ev = EvPlayerHitsOrStands(RuleSet(), PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.509322, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575224, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10Stand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575782, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10HitOrStand) {
  const ExpectedValue ev = EvPlayerHitsOrStands(RuleSet(), PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575224, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.235626, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Stand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6HitOrStand) {
  const ExpectedValue ev = EvPlayerHitsOrStands(RuleSet(), PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer10Dealer6Double) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHand(10), DealerHand(6));
  EXPECT_NEAR(ev.value, 0.575590, Epsilon);
}

TEST(EvTests, TestPlayer11Dealer7Double) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHand(11), DealerHand(7));
  EXPECT_NEAR(ev.value, 0.462889, Epsilon);
}

TEST(EvTests, TestPlayer9DealerAceHit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(9), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.353164, Epsilon);
}

TEST(EvTests, TestPlayer9DealerAceStand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(9), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.769427, Epsilon);
}

TEST(EvTests, TestPlayer4DealerAceHit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(4), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.482899, Epsilon);
}

TEST(EvTests, TestPlayer4DealerAceStand) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(4), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.769427, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Hit) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.148644, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Stands) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Doubles) {
  const ExpectedValue ev = EvPlayerDoubles(RuleSet(), PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.456367, Epsilon);
}

TEST(EvTests, TestPlayerSoft19DealerAceHits) {
  const ExpectedValue ev = EvPlayerHits(RuleSet(), PlayerHand(19, true), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.311668, Epsilon);
}

TEST(EvTests, TestPlayerSoft19DealerAceStands) {
  const ExpectedValue ev = EvPlayerStands(RuleSet(), PlayerHand(19, true), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.115483, Epsilon);
}

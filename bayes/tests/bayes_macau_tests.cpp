#include <gtest/gtest.h>

#include "bayes.h"

using namespace BlackjackEngine::StateMachine;
using namespace BlackjackEngine::Bayes;

constexpr double Epsilon = 0.000001;

const RuleSet macauRule = {
    .hitOnSoft17 = false,
    .maxSplittedHands = 4,
    .resplitAces = false,
    .splitLosesOriginalToDealerBJ = false,
    .doubleLosesOriginalToDealerBJ = true,
    .doubleOnSplits = true,
};

TEST(EvTests, TestPlayer16Dealer9Hit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(16, false, 2), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.509322, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Stand) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10Hit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575224, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10Stand) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575782, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer10Best) {
  const ExpectedValue ev =
      EvPlayerBestAction(macauRule, PlayerHand(16), DealerHand(10));
  EXPECT_NEAR(ev.value, -0.575224, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Hit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.235626, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Stand) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer13Dealer6Best) {
  const ExpectedValue ev =
      EvPlayerBestAction(macauRule, PlayerHand(13), DealerHand(6));
  EXPECT_NEAR(ev.value, -0.153699, Epsilon);
}

TEST(EvTests, TestPlayer10Dealer6Double) {
  const ExpectedValue ev =
      EvPlayerDoubles(macauRule, PlayerHand(10), DealerHand(6));
  EXPECT_NEAR(ev.value, 0.575590, Epsilon);
}

TEST(EvTests, TestPlayer11Dealer7Double) {
  const ExpectedValue ev =
      EvPlayerDoubles(macauRule, PlayerHand(11), DealerHand(7));
  EXPECT_NEAR(ev.value, 0.462889, Epsilon);
}

TEST(EvTests, TestPlayer9DealerAceHit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(9), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.353164, Epsilon);
}

TEST(EvTests, TestPlayer9DealerAceStand) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(9), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.769427, Epsilon);
}

TEST(EvTests, TestPlayer4DealerAceHit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(4), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.482899, Epsilon);
}

TEST(EvTests, TestPlayer4DealerAceStand) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(4), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.769427, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Hit) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.148644, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Stands) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.543150, Epsilon);
}

TEST(EvTests, TestPlayerSoft16Dealer9Doubles) {
  const ExpectedValue ev =
      EvPlayerDoubles(macauRule, PlayerHand(16, true), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.456367, Epsilon);
}

TEST(EvTests, TestPlayerSoft19DealerAceHits) {
  const ExpectedValue ev =
      EvPlayerHits(macauRule, PlayerHand(19, true), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.311668, Epsilon);
}

TEST(EvTests, TestPlayerSoft19DealerAceStands) {
  const ExpectedValue ev =
      EvPlayerStands(macauRule, PlayerHand(19, true), DealerHand(11, true));
  EXPECT_NEAR(ev.value, -0.115483, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer6Split) {
  const ExpectedValue ev =
      EvPlayerSplits(macauRule, PlayerHand(16), DealerHand(6));
  EXPECT_NEAR(ev.value, 0.412349, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer5Split) {
  const ExpectedValue ev =
      EvPlayerSplits(macauRule, PlayerHand(16), DealerHand(5));
  EXPECT_NEAR(ev.value, 0.299967, Epsilon);
}

TEST(EvTests, TestPlayer20Dealer6Split) {
  const ExpectedValue ev =
      EvPlayerSplits(macauRule, PlayerHand(20), DealerHand(6));
  EXPECT_NEAR(ev.value, 0.575590, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Split) {
  const ExpectedValue ev =
      EvPlayerSplits(macauRule, PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.386573, Epsilon);
}

TEST(EvTests, TestPlayer16Dealer9Best) {
  const ExpectedValue ev =
      EvPlayerBestAction(macauRule, PlayerHand(16), DealerHand(9));
  EXPECT_NEAR(ev.value, -0.386573, Epsilon);
}

/*
 * Commented out because it is too slow at the moment.
 * We will introduce caches to fix this.
TEST(EvTests, TestPlayerSoft12Dealer9Split) {
  const ExpectedValue ev =
      EvPlayerSplits(macauRule, PlayerHand(12, true), DealerHand(9));
  EXPECT_NEAR(ev.value, 0.642847, Epsilon);
}
 */

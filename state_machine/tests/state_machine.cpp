#include <gtest/gtest.h>
#include "state_machine.h"

using namespace BlackjackEngine;

namespace {

State PlayerTurn(PlayerHand player, DealerHand dealer) {
  return State(Turn::Player, player, dealer);
}

State DealerTurn(PlayerHand player, DealerHand dealer) {
  return State(Turn::Dealer, player, dealer);
}

} // namespace

TEST(StateMachineTests, StandMovesToDealer) {
  const State next = Stand(PlayerTurn(PlayerHand(18, false, 2), DealerHand(9, false, 1)));
  EXPECT_EQ(next.turn, Turn::Dealer);
  EXPECT_EQ(next.playerHand.score, 18);
}

TEST(StateMachineTests, HitStaysWithPlayerWhenNoBust) {
  const State next = Hit(PlayerTurn(PlayerHand(12, false, 2), DealerHand(9, false, 1)), Card(5));
  EXPECT_EQ(next.turn, Turn::Player);
  EXPECT_EQ(next.playerHand.score, 17);
  EXPECT_EQ(next.playerHand.numCards, 3);
}

TEST(StateMachineTests, HitBustEndsRound) {
  const State next = Hit(PlayerTurn(PlayerHand(16, false, 2), DealerHand(9, false, 1)), Card(10));
  EXPECT_EQ(next.turn, Turn::End);
  EXPECT_EQ(next.playerHand.score, 26);
  EXPECT_TRUE(IsTerminal(next));
  EXPECT_EQ(Result(next), Outcome::PlayerLoses);
}

TEST(StateMachineTests, DoubleAddsCardThenDealer) {
  const State next = Double(PlayerTurn(PlayerHand(10, false, 2), DealerHand(6, false, 1)), Card(9));
  EXPECT_EQ(next.turn, Turn::Dealer);
  EXPECT_EQ(next.playerHand.score, 19);
  EXPECT_EQ(next.playerHand.numCards, 3);
}

TEST(StateMachineTests, CanDoubleOnlyOnTwoCards) {
  EXPECT_TRUE(CanDouble(PlayerTurn(PlayerHand(10, false, 2), DealerHand(6, false, 1))));
  EXPECT_FALSE(CanDouble(PlayerTurn(PlayerHand(15, false, 3), DealerHand(6, false, 1))));
  EXPECT_FALSE(CanDouble(DealerTurn(PlayerHand(10, false, 2), DealerHand(6, false, 1))));
}

TEST(StateMachineTests, DealerHitsBelow17) {
  EXPECT_TRUE(DealerShouldHit(RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(16, false, 2))));
}

TEST(StateMachineTests, DealerStandsOnHard17) {
  EXPECT_FALSE(DealerShouldHit(RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(17, false, 2))));
}

TEST(StateMachineTests, DealerStandsAbove17) {
  EXPECT_FALSE(DealerShouldHit(RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(19, false, 2))));
}

TEST(StateMachineTests, DealerStandsOnSoft17WhenRuleOff) {
  RuleSet ruleset;
  ruleset.hitOnSoft17 = false;
  EXPECT_FALSE(DealerShouldHit(ruleset, DealerTurn(PlayerHand(18, false, 2), DealerHand(17, true, 2))));
}

TEST(StateMachineTests, DealerHitsOnSoft17WhenRuleOn) {
  RuleSet ruleset;
  ruleset.hitOnSoft17 = true;
  EXPECT_TRUE(DealerShouldHit(ruleset, DealerTurn(PlayerHand(18, false, 2), DealerHand(17, true, 2))));
}

TEST(StateMachineTests, DealerDrawEndsRoundWhenDealerStands) {
  const State next = DealerDraw(RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(12, false, 2)), Card(6));
  EXPECT_EQ(next.dealerHand.score, 18);
  EXPECT_EQ(next.turn, Turn::End);
}

TEST(StateMachineTests, DealerDrawKeepsDealerTurnWhenHitting) {
  const State next = DealerDraw(RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(10, false, 1)), Card(5));
  EXPECT_EQ(next.dealerHand.score, 15);
  EXPECT_EQ(next.turn, Turn::Dealer);
}

TEST(StateMachineTests, ResultDealerBustIsPlayerWin) {
  const State state(Turn::End, PlayerHand(18, false, 2), DealerHand(23, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerWins);
}

TEST(StateMachineTests, ResultDealerNaturalBeatsPlayer) {
  const State state(Turn::End, PlayerHand(20, false, 3), DealerHand(21, false, 2));
  EXPECT_EQ(Result(state), Outcome::PlayerLoses);
}

TEST(StateMachineTests, ResultThreeCard21IsNotNatural) {
  const State state(Turn::End, PlayerHand(21, false, 3), DealerHand(21, false, 3));
  EXPECT_EQ(Result(state), Outcome::Push);
}

TEST(StateMachineTests, ResultHigherPlayerWins) {
  const State state(Turn::End, PlayerHand(20, false, 3), DealerHand(18, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerWins);
}

TEST(StateMachineTests, ResultLowerPlayerLoses) {
  const State state(Turn::End, PlayerHand(17, false, 3), DealerHand(19, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerLoses);
}

TEST(StateMachineTests, ResultEqualIsPush) {
  const State state(Turn::End, PlayerHand(19, false, 3), DealerHand(19, false, 3));
  EXPECT_EQ(Result(state), Outcome::Push);
}

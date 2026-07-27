#include <gtest/gtest.h>

#include "state_machine.h"

using namespace BlackjackEngine::StateMachine;

namespace {

State PlayerTurn(PlayerHand player, DealerHand dealer) {
  return State(Turn::Player, player, dealer);
}

State DealerTurn(PlayerHand player, DealerHand dealer) {
  return State(Turn::Dealer, player, dealer);
}

}  // namespace

TEST(StateMachineTests, InitiateStateKeepsDoubleOnTwoCards) {
  const State state = InitiateState(
      RuleSet(), Turn::Player, PlayerHand(10, false, 2),
      DealerHand(6, false, 1), Action::Hit | Action::Stand | Action::Double);
  EXPECT_EQ(state.turn, Turn::Player);
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Double));
}

TEST(StateMachineTests, InitiateStateRemovesDoubleWhenNotTwoCards) {
  const State state = InitiateState(
      RuleSet(), Turn::Player, PlayerHand(15, false, 3),
      DealerHand(6, false, 1), Action::Hit | Action::Stand | Action::Double);
  EXPECT_FALSE(IsAllowed(state.allowedActions, Action::Double));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Hit));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Stand));
}

TEST(StateMachineTests, InitiateStateDealerEntersForcedHit) {
  const State state = InitiateState(
      RuleSet(), Turn::Dealer, PlayerHand(18, false, 2),
      DealerHand(9, false, 1), Action::Hit | Action::Stand | Action::Double);
  EXPECT_EQ(state.turn, Turn::Dealer);
  EXPECT_EQ(state.allowedActions, Action::Hit);
}

TEST(StateMachineTests, InitiateStateDealerStandBecomesTerminal) {
  const State state = InitiateState(
      RuleSet(), Turn::Dealer, PlayerHand(18, false, 2),
      DealerHand(19, false, 2), Action::Hit | Action::Stand | Action::Double);
  EXPECT_EQ(state.turn, Turn::End);
  EXPECT_EQ(state.allowedActions, Action::None);
}

TEST(StateMachineTests, StandMovesToDealer) {
  const State next = Stand(
      RuleSet(), PlayerTurn(PlayerHand(18, false, 2), DealerHand(9, false, 1)));
  EXPECT_EQ(next.turn, Turn::Dealer);
  EXPECT_EQ(next.playerHand.score, 18);
}

TEST(StateMachineTests, HitStaysWithPlayerWhenNoBust) {
  const State next = Hit(
      RuleSet(), PlayerTurn(PlayerHand(12, false, 2), DealerHand(9, false, 1)),
      Card(5));
  EXPECT_EQ(next.turn, Turn::Player);
  EXPECT_EQ(next.playerHand.score, 17);
  EXPECT_EQ(next.playerHand.numCards, 3);
}

TEST(StateMachineTests, HitBustEndsRound) {
  const State next = Hit(
      RuleSet(), PlayerTurn(PlayerHand(16, false, 2), DealerHand(9, false, 1)),
      Card(10));
  EXPECT_EQ(next.turn, Turn::End);
  EXPECT_EQ(next.playerHand.score, 26);
  EXPECT_TRUE(IsTerminal(next));
  EXPECT_EQ(Result(next), Outcome::PlayerLoses);
}

TEST(StateMachineTests, DoubleAddsCardAndLeavesOnlyStand) {
  const State next = Double(
      PlayerTurn(PlayerHand(10, false, 2), DealerHand(6, false, 1)), Card(9));
  EXPECT_EQ(next.turn, Turn::Player);
  EXPECT_EQ(next.playerHand.score, 19);
  EXPECT_EQ(next.playerHand.numCards, 3);
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Stand));
  EXPECT_FALSE(IsAllowed(next.allowedActions, Action::Hit));
  EXPECT_FALSE(IsAllowed(next.allowedActions, Action::Double));
}

TEST(StateMachineTests, DealerHitsBelow17) {
  const State state =
      InitiateState(RuleSet(), Turn::Dealer, PlayerHand(18, false, 2),
                    DealerHand(16, false, 2));
  EXPECT_FALSE(IsTerminal(state));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Hit));
}

TEST(StateMachineTests, DealerStandsOnHard17) {
  const State state =
      InitiateState(RuleSet(), Turn::Dealer, PlayerHand(18, false, 2),
                    DealerHand(17, false, 2));
  EXPECT_TRUE(IsTerminal(state));
}

TEST(StateMachineTests, DealerStandsAbove17) {
  const State state =
      InitiateState(RuleSet(), Turn::Dealer, PlayerHand(18, false, 2),
                    DealerHand(19, false, 2));
  EXPECT_TRUE(IsTerminal(state));
}

TEST(StateMachineTests, DealerStandsOnSoft17WhenRuleOff) {
  RuleSet ruleset;
  ruleset.hitOnSoft17 = false;
  const State state = InitiateState(
      ruleset, Turn::Dealer, PlayerHand(18, false, 2), DealerHand(17, true, 2));
  EXPECT_TRUE(IsTerminal(state));
}

TEST(StateMachineTests, DealerHitsOnSoft17WhenRuleOn) {
  RuleSet ruleset;
  ruleset.hitOnSoft17 = true;
  const State state = InitiateState(
      ruleset, Turn::Dealer, PlayerHand(18, false, 2), DealerHand(17, true, 2));
  EXPECT_FALSE(IsTerminal(state));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Hit));
}

TEST(StateMachineTests, HitAddsToDealerOnDealerTurn) {
  const State next = Hit(
      RuleSet(), DealerTurn(PlayerHand(18, false, 2), DealerHand(10, false, 1)),
      Card(5));
  EXPECT_EQ(next.dealerHand.score, 15);
  EXPECT_EQ(next.dealerHand.numCards, 2);
  EXPECT_EQ(next.playerHand.score, 18);
  EXPECT_EQ(next.turn, Turn::Dealer);
}

TEST(StateMachineTests, StandEndsRoundOnDealerTurn) {
  const State next = Stand(RuleSet(), DealerTurn(PlayerHand(18, false, 2),
                                                 DealerHand(19, false, 2)));
  EXPECT_EQ(next.turn, Turn::End);
  EXPECT_TRUE(IsTerminal(next));
}

TEST(StateMachineTests, ResultDealerBustIsPlayerWin) {
  const State state(Turn::End, PlayerHand(18, false, 2),
                    DealerHand(23, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerWins);
}

TEST(StateMachineTests, ResultDealerBlackjackBeatsPlayer) {
  const State state(Turn::End, PlayerHand(20, false, 3),
                    DealerHand(21, false, 2));
  EXPECT_EQ(Result(state), Outcome::PlayerLoses);
}

TEST(StateMachineTests, ResultBothBlackjacksPush) {
  const State state(Turn::End, PlayerHand(21, false, 2),
                    DealerHand(21, false, 2));
  EXPECT_EQ(Result(state), Outcome::Push);
}

TEST(StateMachineTests, ResultPlayerBlackjackBeatsNonBlackjack) {
  const State state(Turn::End, PlayerHand(21, false, 2),
                    DealerHand(21, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerWins);
}

TEST(StateMachineTests, ResultThreeCard21IsNotBlackjack) {
  const State state(Turn::End, PlayerHand(21, false, 3),
                    DealerHand(21, false, 3));
  EXPECT_EQ(Result(state), Outcome::Push);
}

TEST(StateMachineTests, ResultHigherPlayerWins) {
  const State state(Turn::End, PlayerHand(20, false, 3),
                    DealerHand(18, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerWins);
}

TEST(StateMachineTests, ResultLowerPlayerLoses) {
  const State state(Turn::End, PlayerHand(17, false, 3),
                    DealerHand(19, false, 3));
  EXPECT_EQ(Result(state), Outcome::PlayerLoses);
}

TEST(StateMachineTests, ResultEqualIsPush) {
  const State state(Turn::End, PlayerHand(19, false, 3),
                    DealerHand(19, false, 3));
  EXPECT_EQ(Result(state), Outcome::Push);
}

TEST(StateMachineTests, InitialPlayerStateAllowsAllActions) {
  const State state =
      PlayerTurn(PlayerHand(10, false, 2), DealerHand(6, false, 1));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Hit));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Stand));
  EXPECT_TRUE(IsAllowed(state.allowedActions, Action::Double));
}

TEST(StateMachineTests, HitRemovesDoubleFromAllowedActions) {
  const State next = Hit(
      RuleSet(), PlayerTurn(PlayerHand(12, false, 2), DealerHand(6, false, 1)),
      Card(3));
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Hit));
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Stand));
  EXPECT_FALSE(IsAllowed(next.allowedActions, Action::Double));
}

TEST(StateMachineTests, BustLeavesNoAllowedActions) {
  const State next = Hit(
      RuleSet(), PlayerTurn(PlayerHand(16, false, 2), DealerHand(6, false, 1)),
      Card(10));
  EXPECT_EQ(next.allowedActions, Action::None);
}

TEST(StateMachineTests, StandSetsDealerForcedHit) {
  const State next = Stand(
      RuleSet(), PlayerTurn(PlayerHand(18, false, 2), DealerHand(9, false, 1)));
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Hit));
  EXPECT_FALSE(IsAllowed(next.allowedActions, Action::Stand));
}

TEST(StateMachineTests, StandEndsRoundWhenDealerMustStand) {
  const State next = Stand(RuleSet(), PlayerTurn(PlayerHand(18, false, 2),
                                                 DealerHand(19, false, 2)));
  EXPECT_EQ(next.turn, Turn::End);
  EXPECT_TRUE(IsTerminal(next));
  EXPECT_EQ(next.allowedActions, Action::None);
}

TEST(StateMachineTests, DealerForcedActionRespectsHitOnSoft17) {
  RuleSet ruleset;
  ruleset.hitOnSoft17 = true;
  const State next = Stand(
      ruleset, PlayerTurn(PlayerHand(18, false, 2), DealerHand(17, true, 2)));
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Hit));
}

TEST(StateMachineTests, StandAfterDoubleMovesToDealer) {
  const State doubled = Double(
      PlayerTurn(PlayerHand(10, false, 2), DealerHand(9, false, 1)), Card(9));
  const State next = Stand(RuleSet(), doubled);
  EXPECT_EQ(next.turn, Turn::Dealer);
  EXPECT_TRUE(IsAllowed(next.allowedActions, Action::Hit));
}

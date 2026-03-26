#include <gtest/gtest.h>
#include "hand.h"

TEST(HandScoreTests, TestBasicAddCard) {
  {
    HandScore hand(2);
    hand += CardScore(3);
    EXPECT_EQ(hand.score, 5);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(12);
    hand += CardScore(3);
    EXPECT_EQ(hand.score, 15);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(10);
    hand += CardScore(3);
    EXPECT_EQ(hand.score, 13);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandScoreTests, TestAddCardThatBursts) {
  {
    HandScore hand(19);
    hand += CardScore(3);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(21);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(17);
    hand += CardScore(5);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandScoreTests, TestAddAce) {
  {
    HandScore hand(2);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 13);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(9);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 20);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(13);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 14);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(20);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandScoreTests, TestSoftHandAddCard) {
  {
    HandScore hand(11, true);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 12);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(13, true);
    hand += CardScore(7);
    EXPECT_EQ(hand.score, 20);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(12, true);
    hand += CardScore(9);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(20, true);
    hand += CardScore(9);
    EXPECT_EQ(hand.score, 19);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(17, true);
    hand += CardScore(5);
    EXPECT_EQ(hand.score, 12);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    HandScore hand(16, true);
    hand += CardScore(2);
    EXPECT_EQ(hand.score, 18);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    HandScore hand(13, true);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 14);
    EXPECT_EQ(hand.isSoft, true);
  }


  {
    HandScore hand(20, true);
    hand += CardScore(11);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, true);
  }

}

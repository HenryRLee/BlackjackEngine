#include <gtest/gtest.h>
#include "hand.h"

using namespace BlackjackEngine::StateMachine;

TEST(HandTests, TestBasicAddCard) {
  {
    Hand hand(2);
    hand += Card(3);
    EXPECT_EQ(hand.score, 5);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(12);
    hand += Card(3);
    EXPECT_EQ(hand.score, 15);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(10);
    hand += Card(3);
    EXPECT_EQ(hand.score, 13);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandTests, TestAddCardThatBursts) {
  {
    Hand hand(19);
    hand += Card(3);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(21);
    hand += Card(11);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(17);
    hand += Card(5);
    EXPECT_EQ(hand.score, 22);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandTests, TestAddAce) {
  {
    Hand hand(2);
    hand += Card(11);
    EXPECT_EQ(hand.score, 13);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(9);
    hand += Card(11);
    EXPECT_EQ(hand.score, 20);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(13);
    hand += Card(11);
    EXPECT_EQ(hand.score, 14);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(20);
    hand += Card(11);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, false);
  }
}

TEST(HandTests, TestSoftHandAddCard) {
  {
    Hand hand(11, true);
    hand += Card(11);
    EXPECT_EQ(hand.score, 12);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(13, true);
    hand += Card(7);
    EXPECT_EQ(hand.score, 20);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(12, true);
    hand += Card(9);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(20, true);
    hand += Card(9);
    EXPECT_EQ(hand.score, 19);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(17, true);
    hand += Card(5);
    EXPECT_EQ(hand.score, 12);
    EXPECT_EQ(hand.isSoft, false);
  }

  {
    Hand hand(16, true);
    hand += Card(2);
    EXPECT_EQ(hand.score, 18);
    EXPECT_EQ(hand.isSoft, true);
  }

  {
    Hand hand(13, true);
    hand += Card(11);
    EXPECT_EQ(hand.score, 14);
    EXPECT_EQ(hand.isSoft, true);
  }


  {
    Hand hand(20, true);
    hand += Card(11);
    EXPECT_EQ(hand.score, 21);
    EXPECT_EQ(hand.isSoft, true);
  }

}

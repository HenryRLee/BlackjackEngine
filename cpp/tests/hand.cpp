#include <gtest/gtest.h>
#include "hand.h"

TEST(HandScoreTests, TestAddCard) {
  HandScore hand(12);

  hand += CardScore(3);

  EXPECT_EQ(hand.score, 15);
}

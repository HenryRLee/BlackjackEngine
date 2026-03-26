#ifndef HAND_H
#define HAND_H

#include "card.h"

struct HandScore {
  unsigned char score = 0;
  bool isSoft = false;

  explicit constexpr HandScore(unsigned char v) : score(v) { }
  constexpr HandScore(unsigned char v, bool soft) : score(v), isSoft(soft) { }

  HandScore& operator+=(CardScore card) {
	score = score + card.score;

    if (score > 21) {
      if (card.score == 11) {
        score -= 10;
      }
      else if (isSoft) {
        score -= 10;
        isSoft = false;
      }
    } else if (card.score == 11) {
      isSoft = true;
    }

	return *this;
  }

  HandScore operator+(CardScore card) const {
    HandScore newScore(score);
    newScore += card;
    return newScore;
  }
};

struct DealerHandScore : public HandScore {
  constexpr DealerHandScore(const DealerHandScore& hand) = default;
  constexpr DealerHandScore(const HandScore& hand) : HandScore(hand) { }
  explicit constexpr DealerHandScore(unsigned char v) : HandScore(v) { }
};

struct PlayerHandScore : public HandScore {
  constexpr PlayerHandScore(const PlayerHandScore& hand) = default;
  constexpr PlayerHandScore(const HandScore& hand) : HandScore(hand) { }
  explicit constexpr PlayerHandScore(unsigned char v) : HandScore(v) { }
};

#endif // HAND_H

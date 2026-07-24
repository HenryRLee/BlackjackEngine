#ifndef HAND_H
#define HAND_H

#include "card.h"

namespace BlackjackEngine {

struct Hand {
  unsigned char score = 0;
  bool isSoft = false;

  explicit constexpr Hand(unsigned char v) : score(v) { }
  constexpr Hand(unsigned char v, bool soft) : score(v), isSoft(soft) { }

  constexpr Hand& operator+=(Card card) {
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

  constexpr Hand operator+(Card card) const {
    Hand newScore(*this);
    newScore += card;
    return newScore;
  }
};

struct DealerHand : public Hand {
  constexpr DealerHand(const DealerHand& hand) = default;
  constexpr DealerHand(const Hand& hand) : Hand(hand) { }
  explicit constexpr DealerHand(unsigned char v) : Hand(v) { }
  constexpr DealerHand(unsigned char v, bool soft) : Hand(v, soft) { }
};

struct PlayerHand : public Hand {
  constexpr PlayerHand(const PlayerHand& hand) = default;
  constexpr PlayerHand(const Hand& hand) : Hand(hand) { }
  explicit constexpr PlayerHand(unsigned char v) : Hand(v) { }
  constexpr PlayerHand(unsigned char v, bool soft) : Hand(v, soft) { }
};

} // namespace BlackjackEngine

#endif // HAND_H

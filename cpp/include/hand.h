#ifndef HAND_H
#define HAND_H

#include "card.h"

struct HandScore {
  unsigned score = 0;
  bool isSoft = false;

  explicit HandScore(unsigned v) : score(v) { }
  HandScore(unsigned v, bool soft) : score(v), isSoft(soft) { }

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
};

#endif // HAND_H

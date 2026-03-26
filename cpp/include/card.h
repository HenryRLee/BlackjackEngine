#ifndef CARD_H
#define CARD_H

struct CardScore {
  unsigned char score = 0;

  explicit constexpr CardScore(unsigned char v) : score(v) { }
};

#endif // CARD_H

#ifndef CARD_H
#define CARD_H

namespace BlackjackBayes {

struct CardScore {
  unsigned char score = 0;

  explicit constexpr CardScore(unsigned char v) : score(v) { }
};

} // namespace

#endif // CARD_H

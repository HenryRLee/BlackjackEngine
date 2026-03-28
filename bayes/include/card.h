#ifndef CARD_H
#define CARD_H

namespace BlackjackBayes {

struct Card {
  unsigned char score = 0;

  explicit constexpr Card(unsigned char v) : score(v) { }
};

} // namespace

#endif // CARD_H

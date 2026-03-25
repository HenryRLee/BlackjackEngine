#ifndef CARD_H
#define CARD_H

struct CardScore {
  unsigned score = 0;

  explicit CardScore(unsigned v) : score(v) { }
};

#endif // CARD_H

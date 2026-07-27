#ifndef CARD_H
#define CARD_H

namespace BlackjackEngine::StateMachine {

struct Card {
  unsigned char score = 0;

  explicit constexpr Card(unsigned char v) : score(v) {}
};

}  // namespace BlackjackEngine::StateMachine

#endif  // CARD_H

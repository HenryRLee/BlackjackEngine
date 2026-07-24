#ifndef STATE_H
#define STATE_H

#include "hand.h"

namespace BlackjackEngine {

// Whose turn it is to act, or that the round has finished.
enum class Turn : unsigned char {
  Player,
  Dealer,
  End,
};

struct State {
  Turn turn = Turn::Player;
  PlayerHand playerHand;
  DealerHand dealerHand;

  constexpr State(Turn turn, PlayerHand playerHand, DealerHand dealerHand)
      : turn(turn), playerHand(playerHand), dealerHand(dealerHand) { }
};

} // namespace BlackjackEngine

#endif // STATE_H

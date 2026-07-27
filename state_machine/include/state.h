#ifndef STATE_H
#define STATE_H

#include "action.h"
#include "hand.h"

namespace BlackjackEngine::StateMachine {

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
  Action allowedActions;

  constexpr State(Turn turn, PlayerHand playerHand, DealerHand dealerHand,
                  Action allowedActions = Action::Hit | Action::Stand |
                                          Action::Double)
      : turn(turn),
        playerHand(playerHand),
        dealerHand(dealerHand),
        allowedActions(allowedActions) {}
};

}  // namespace BlackjackEngine::StateMachine

#endif  // STATE_H

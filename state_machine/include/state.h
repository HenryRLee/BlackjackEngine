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

  // How many times this hand's lineage has been split (0 = original hand).
  unsigned splitDepth = 0;

  // The score of the single card after a split (e.g. 8 for a split pair of 8s).
  // Used to determine re-split eligibility: only when the drawn second card
  // matches this value can the hand be split again.
  unsigned splitCardScore = 0;

  constexpr State(Turn turn, PlayerHand playerHand, DealerHand dealerHand,
                  Action allowedActions = Action::Hit | Action::Stand |
                                          Action::Double | Action::Split)
      : turn(turn),
        playerHand(playerHand),
        dealerHand(dealerHand),
        allowedActions(allowedActions) {}
};

}  // namespace BlackjackEngine::StateMachine

#endif  // STATE_H

#include <utility>

#include "expected_value.h"
#include "hand.h"
#include "ruleset.h"

namespace BlackjackEngine::Bayes {

using StateMachine::DealerHand;
using StateMachine::PlayerHand;
using StateMachine::RuleSet;

ExpectedValue EvPlayerBestAction(const RuleSet& ruleset, PlayerHand playerHand,
                                 DealerHand dealerHand);

ExpectedValue EvPlayerStands(const RuleSet& ruleset, PlayerHand playerHand,
                             DealerHand dealerHand);

ExpectedValue EvPlayerHits(const RuleSet& ruleset, PlayerHand playerHand,
                           DealerHand dealerHand);

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset, PlayerHand playerHand,
                              DealerHand dealerHand);

ExpectedValue EvPlayerSplits(const RuleSet& ruleset, PlayerHand playerHand,
                             DealerHand dealerHand);

}  // namespace BlackjackEngine::Bayes

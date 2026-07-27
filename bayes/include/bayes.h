#include "expected_value.h"
#include "hand.h"
#include "ruleset.h"

#include <utility>

namespace BlackjackEngine::Bayes {

ExpectedValue EvPlayerBestAction(const RuleSet& ruleset,
                                 PlayerHand playerHand, DealerHand dealerHand);

ExpectedValue EvPlayerStands(const RuleSet& ruleset,
                             PlayerHand playerHand, DealerHand dealerHand);

ExpectedValue EvPlayerHits(const RuleSet& ruleset,
                           PlayerHand playerHand, DealerHand dealerHand);

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset,
                              PlayerHand playerHand, DealerHand dealerHand);

} // namespace BlackjackEngine::Bayes

#include "expected_value.h"
#include "hand.h"
#include "ruleset.h"

#include <utility>

ExpectedValue EvDealerTurn(const RuleSet& ruleset,
                           PlayerHandScore playerHand, DealerHandScore dealerHand);

ExpectedValue EvPlayerHitsOrStands(const RuleSet& ruleset,
                                   PlayerHandScore playerHand, DealerHandScore dealerHand);

ExpectedValue EvPlayerStands(const RuleSet& ruleset,
                             PlayerHandScore playerHand, DealerHandScore dealerHand);

ExpectedValue EvPlayerHits(const RuleSet& ruleset,
                           PlayerHandScore playerHand, DealerHandScore dealerHand);

ExpectedValue EvPlayerDoubles(const RuleSet& ruleset,
                              PlayerHandScore playerHand, DealerHandScore dealerHand);

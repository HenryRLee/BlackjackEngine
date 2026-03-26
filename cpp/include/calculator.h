#include "expected_value.h"
#include "hand.h"
#include "ruleset.h"

#include <utility>

ExpectedValue EvDealerTurn(const RuleSet& ruleset,
                           PlayerHandScore playerHand, DealerHandScore dealerHand);


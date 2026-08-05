#ifndef RULESET_H
#define RULESET_H

namespace BlackjackEngine::StateMachine {

struct RuleSet {
  bool hitOnSoft17 = false;
  unsigned maxSplittedHands = 4;
  bool resplitAces = true;
  bool standOnSplitAces = false;
  bool splitLosesOriginalToDealerBJ = false;
  bool doubleLosesOriginalToDealerBJ = false;
  bool doubleOnSplits = true;
};

}  // namespace BlackjackEngine::StateMachine

#endif  // RULESET_H

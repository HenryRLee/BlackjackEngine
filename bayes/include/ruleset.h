#ifndef RULESET_H
#define RULESET_H

namespace BlackjackBayes {

struct RuleSet {
  bool hitOnSoft17 = false;
  unsigned char numberOfDecks = 1;
};

} // namespace

#endif // RULESET_H

#ifndef EXPECTED_VALUE_H
#define EXPECTED_VALUE_H

namespace BlackjackEngine::Bayes {

struct Probability {
  double value = 0;

  explicit constexpr Probability(double v) : value(v) { }
};

struct ExpectedValue {
  double value = 0;

  explicit constexpr ExpectedValue(double v) : value(v) { }

  bool operator<(ExpectedValue other) const {
    return this->value < other.value;
  }
};

} // namespace

#endif // EXPECTED_VALUE_H

#ifndef EXPECTED_VALUE_H
#define EXPECTED_VALUE_H

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

#endif // EXPECTED_VALUE_H

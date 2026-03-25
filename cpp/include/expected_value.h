#ifndef EXPECTED_VALUE_H
#define EXPECTED_VALUE_H

struct ExpectedValue {
  double value = 0;

  double operator()() const { return value; }

  explicit ExpectedValue(double v) : value(v) { }
};

#endif // EXPECTED_VALUE_H

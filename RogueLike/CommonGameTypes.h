#pragma once
#include <limits>
struct Point {
  Point();
  Point(double X, double Y);
  double X;
  double Y;
  int get_int_X() const { return (int)X; }
  int get_int_Y() const { return (int)Y; }
};
struct VectorMath {
  double X;
  double Y;
  int get_int_X() const { return (int)X; }
  int get_int_Y() const { return (int)Y; }
};
class LimitedValue {
 public:
  LimitedValue(int value, int max = INT_MAX, int min = INT_MIN);
  LimitedValue(const LimitedValue& lv);  // copy

  int get_value() const;
  void set_value();

  int get_max() const;
  void set_max();

  int get_min() const;
  void set_min();

 private:
  int value;
  int max;
  int min;
};

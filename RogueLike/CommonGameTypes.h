#pragma once
#include <limits>
struct Point {
  Point();
  Point(double _X, double _Y);
  Point(const Point& pt);
  double X;
  double Y;
  int get_int_X() const;
  int get_int_Y() const;
  bool operator==(const Point& lhs);
};
struct VectorMath {
  double X;
  double Y;
  int get_int_X() const;
  int get_int_Y() const;
  bool operator==(const VectorMath& lhs);
};
class LimitedValue {
 public:
  LimitedValue(int value = 0, int max = INT_MAX, int min = INT_MIN);
  LimitedValue(const LimitedValue& lv);  // copy

  int get_value() const;
  void set_value(int value);

  int get_max() const;
  void set_max(int max);

  int get_min() const;
  void set_min(int min);

 private:
  int value_;
  int max_;
  int min_;
};

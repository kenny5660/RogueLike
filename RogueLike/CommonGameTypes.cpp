#include "pch.h"

Point::Point() : X(0), Y(0) {}

Point::Point(double _X, double _Y) : X(_X), Y(_Y) {}

Point::Point(const Point& pt) : X(pt.X), Y(pt.Y) {}

int Point::get_int_X() const { return (int)X; }
int Point::get_int_Y() const { return (int)Y; }
bool Point::operator==(const Point& lhs) {
  return (int)this->X == (int)lhs.X && (int)this->Y == (int)lhs.Y;
}

bool Point::operator<(const Point& pt) const {
  if (pt.X == X) {
    return pt.Y < Y; 
  }
	return pt.X < X;
}

Point Point::operator+(const Point& pt) { return Point(pt.X + X, pt.Y + Y); }


LimitedValue::LimitedValue(int value, int max, int min)
    : value_(value), max_(max), min_(min) {
  set_max(max);
  set_min(min);
  set_value(value);
}
LimitedValue::LimitedValue(const LimitedValue& lv)
    : value_(lv.get_value()), max_(lv.get_max()), min_(lv.get_min()) {}

int LimitedValue::get_value() const { return value_; }
void LimitedValue::set_value(int value) {
  value_ = value > max_ ? max_ : value;
  value_ = value_ < min_ ? min_ : value_;
}

int LimitedValue::get_max() const { return max_; }
void LimitedValue::set_max(int max) { max_ = max > min_ ? max : min_; }

int LimitedValue::get_min() const { return min_; }
void LimitedValue::set_min(int min) { min_ = min > max_ ? max_ : min; }

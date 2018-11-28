#pragma once
#include "pch.h"
using ObjectId = unsigned long long int;
class GameObject {
 public:
  virtual void Update() {}
  virtual void Draw() {}

  Point get_pos();
  void set_pos(Point pos);
  ObjectId get_id() const;
  void set_id(ObjectId id);

 protected:
  ObjectId id_;
  char texture_char_;
  Point pos_;
};
class Wall : public GameObject {
  Wall(Point pos);
};

class EmptyBlock: public GameObject {
  EmptyBlock(Point pos);
};

class Entity : public GameObject {
 public:
 protected:
  LimitedValue hp_;
  LimitedValue mp_;
  int strength_;
  int ability_;
  int intelect_;
};

class Knight : public Entity {
 public:
  Knight();
  ~Knight();
  void Update() override;
  void Draw() override;

 private:
  void pressed_Up();
  void pressed_Down();
  void pressed_Right();
  void pressed_Left();
  void Move(VectorMath vector_move);
};

#pragma once
#include "pch.h"
using ObjectId = unsigned long long int;
class GameObject {
 public:
  GameObject();
  virtual void Update() = 0;
  virtual void Draw() = 0;

  Point get_pos() const;
  void set_pos(Point pos);
  ObjectId get_id() const;
  void set_id(ObjectId id) const ;

  char get_texture() const;
  void set_texture(char texture);

 protected:
  mutable ObjectId id_;
  char texture_char_;
  Point pos_;
};
class Wall : public GameObject {
 public:
  Wall(Point pos);
  void Update() override;
  void Draw() override;
};

class EmptyBlock : public GameObject {
 public:
  EmptyBlock(Point pos);
  void Update() override;
  void Draw() override;
};

class Entity : public GameObject {
 public:
  Entity();
 protected:
  LimitedValue hp_;
  LimitedValue mp_;
  int strength_;
  int ability_;
  int intelect_;
  void Move(VectorMath vector_move);
};
class Zombie : public Entity {
 public:
  Zombie(Point pos);
  void Update() override;
  void Draw() override;
};
class Knight : public Entity {
 public:
  Knight(Point pos, char texture = 'K');
  void Update() override;
  void Draw() override;
  void key_pressed(int key);
  
 private:
  void pressed_Up();
  void pressed_Down();
  void pressed_Right();
  void pressed_Left();

};

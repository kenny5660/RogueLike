#pragma once
#include "pch.h"
using ObjectId = unsigned long long int;
class Wall;
class Zombie;
class Knight;

class GameObject {
 public:
  GameObject();
  virtual void Update() = 0;
  virtual void Draw();
  virtual void Collide(GameObject &g) {}
  virtual void Collide(Wall &g) {}
  virtual void Collide(Knight &g) {}
  virtual void Collide(Zombie &g) {}
  Point get_pos() const;
  void set_pos(Point pos);
  ObjectId get_id() const;
  void set_id(ObjectId id);

  char get_texture() const;
  void set_texture(char texture);

 protected:
  ObjectId id_;
  char texture_char_;
  Point pos_;
  Point old_pos_;
};
class Wall : public GameObject {
 public:
  Wall(Point pos);
  void Update() override;
  void Collide(GameObject &g) override;
  // bool Collide(Zombie &z);
  // bool Collide(Knight &w);
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
class Monster : public Entity {

	protected:
  VectorMath cur_vec_move_;
};
class Zombie : public Monster {
 public:
  Zombie(Point pos, char texture = 'Z');
  void Update() override;
  void Collide(GameObject &g) override;
  void Collide(Zombie &z) override;
  void Collide(Wall &w) override;
 private:
  void random_set_vec_move();
};
class Knight : public Entity {
 public:
  Knight(Point pos, char texture = 'K');
  void Update() override;
  void key_pressed(int key);
  void Collide(GameObject &g) override;
  void Collide(Zombie &z) override;
  void Collide(Wall &w) override;

 private:
  void pressed_Up();
  void pressed_Down();
  void pressed_Right();
  void pressed_Left();
};

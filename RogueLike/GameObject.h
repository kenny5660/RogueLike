#pragma once
#include "pch.h"
using ObjectId = unsigned long long int;
class GameObject;
class Wall;
class Zombie;
class Knight;
class AidKit;
class Monster;
class Projectile;
#include "GameConfig.h"
#include "Scene.h"
#include "game_database.h"

class GameObject {
 public:
  GameObject();
  virtual void Update() = 0;
  virtual void Draw();
  virtual void Collide(GameObject &g) {}
  virtual void Collide(Wall &g) {}
  virtual void Collide(Knight &g) {}
  virtual void Collide(Monster &g) {}
  virtual void Collide(AidKit &g) {}
  virtual void Collide(Projectile &g) {}
  Point Get_pos() const;
  void Set_pos(Point pos);
  Point Get_old_pos();
  ObjectId Get_id() const;
  void Set_id(ObjectId id);
  char Get_texture() const;
  void Set_texture(char texture);

 protected:
  ObjectId id_;
  char texture_char_;
  Point pos_;
  Point old_pos_;
};
class GuiPlayer : public GameObject {
 public:
  GuiPlayer() {}
  GuiPlayer(Point pos, std::shared_ptr<Knight> kn);
  void Draw() override;
  void Update() override;

 private:
  std::shared_ptr<Knight> kn_;
};
class AidKit : public GameObject {
 public:
  AidKit() {}
  AidKit(Point pos, int hp_regen);
  AidKit(const AidKit &aid, Point pos);
  void Set_hp_regen(int hp_regen);
  int Get_hp_regen();
  void Update() override;
  void Collide(GameObject &g) override;

 private:
  int hp_regen_;
  // bool Collide(Zombie &z);
  // bool Collide(Knight &w);
};
class Wall : public GameObject {
 public:
  Wall() {}
  Wall(Point pos);
  Wall(const Wall &wall, Point pos);
  void Update() override;
  void Collide(GameObject &g) override;
  // bool Collide(Zombie &z);
  // bool Collide(Knight &w);
};
class Entity : public GameObject {
 public:
  Entity();
  LimitedValue &get_hp();
  LimitedValue &get_mp();
  int Get_damage();
  void Set_damage(int damage);
  Scene *Get_parent_scene();
  void Set_parent_scene(Scene *);
  virtual void dead();

 protected:
  LimitedValue hp_;
  LimitedValue mp_;
  int damage_;
  Scene *parent_scene_;
  VectorMath cur_vec_move_ = {1,0};
  void Move(VectorMath vector_move);
};
class Projectile : public Entity {
 public:
  Projectile() {}
  Projectile(Point pos, int damage, VectorMath vec_move,
             Scene *parent_scene);
  void Update() override;
  void Collide(GameObject &g) override;
  void Collide(Wall &g) override;
  void Collide(Monster &g) override;
  void Collide(Knight &g) override;
  void Collide(Projectile &g) override;
  void Set_texture_left(char t);
  void Set_texture_down(char t);
  void Set_texture_right(char t);
  void Set_texture_up(char t);

 private:
  char texture_left_ = '<';
  char texture_right_ = '>';
  char texture_down_ = 'V';
  char texture_up_ = '^';
};
class ProjectileKnight : public Projectile {
 public:
  ProjectileKnight() {}
  ProjectileKnight(Point pos, int damage, VectorMath vec_move, Knight *kn);
  void Collide(Monster &g) override;

 private:
  Knight *kn_;
};
class Monster : public Entity {};

class Dragon : public Monster {
 public:
  Dragon() {}
  Dragon(Point pos, char texture = 'D');
  Dragon(const Dragon &dragon, Point pos, Scene *parent_scene);
  void Update() override;
  void Collide(GameObject &g) override;
  void Collide(Monster &z) override;
  void Collide(Wall &w) override;
  void Collide(Knight &k) override;
  void Collide(AidKit &g) override;
  void Collide(Projectile &g) override;

 private:
  void random_set_vec_move();
};

class Zombie : public Monster {
 public:
  Zombie() {}
  Zombie(Point pos, char texture = 'Z');
  Zombie(const Zombie &zombie, Point pos, Scene *parent_scene);
  void Update() override;
  void Collide(GameObject &g) override;
  void Collide(Monster &z) override;
  void Collide(Wall &w) override;
  void Collide(Knight &k) override;
  void Collide(AidKit &g) override;
  void Collide(Projectile &g) override;
 private:
  void random_set_vec_move();
};
class Knight : public Entity {
 public:
  Knight() {}
  Knight(Point pos, char texture = 'K');
  Knight(const Knight &knight, Point pos, Scene *parent_scene);
  void Update() override;
  void key_pressed(int key);
  void dead() override;
  void Collide(GameObject &g) override;
  void Collide(Monster &z) override;
  void Collide(Wall &w) override;
  void Collide(AidKit &g) override;
  int Get_points();
  void Set_points(int points);

 private:
  int points_ = 0;
  int damage_projectile_ = 2;
  void PressedUp();
  void PressedDown();
  void PressedRight();
  void PressedLeft();
  void PressedSpace();
};

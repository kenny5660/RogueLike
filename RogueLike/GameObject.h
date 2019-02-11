#pragma once
using ObjectId = unsigned long long int;
class GameObject;
class Wall;
class Zombie;
class Knight;
class AidKit;
class Monster;
class Projectile;
class Entity;
class Princess;
#include "GameConfig.h"
#include "Scene.h"
#include "game_database.h"

std::pair<bool, bool> fight(Entity &a, Entity &b);

class GameObject {
 public:
  GameObject();
  GameObject(Point pos, char texture);
  virtual void Update(){};
  virtual void Draw();
  virtual void Collide(GameObject &g) { return g.Collide(*this); }
  virtual void Collide(Wall &g) {}
  virtual void Collide(Knight &g) {}
  virtual void Collide(Monster &g) {}
  virtual void Collide(AidKit &g) {}
  virtual void Collide(Projectile &g) {}
  virtual void Collide(Princess &g) {}
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

 private:
  std::shared_ptr<Knight> kn_;
};
class AidKit : public GameObject {
 public:
  AidKit() {}
  AidKit(Point pos, int hp_regen, char texture = '+');
  AidKit(const AidKit &aid, Point pos);
  void Set_hp_regen(int hp_regen);
  int Get_hp_regen() const;
  void Collide(GameObject &g) override;

 private:
  int hp_regen_;
};

class Wall : public GameObject {
 public:
  Wall() {}
  Wall(Point pos, char texture = '#');
  Wall(const Wall &wall, Point pos);
  void Collide(GameObject &g) override;
};
class Entity : public GameObject {
 public:
  Entity();
  Entity(Point pos, char texture, LimitedValue hp, LimitedValue mp, int damage,
         std::shared_ptr<Scene> parent_scene, Point cur_vec_move,
         double speed);
  const LimitedValue &get_hp() const;
  const LimitedValue &get_mp() const;
  void set_hp(const LimitedValue &hp);
  void set_mp(const LimitedValue &mp);
  int Get_damage() const;
  void Set_damage(int damage);
  std::shared_ptr<Scene>  Get_parent_scene();
  void Set_parent_scene(std::shared_ptr<Scene>);
  double Get_speed() const;
  void Set_speed(double speed);
  Point Get_cur_vector_move();
  void Set_cur_vec_move(Point vec);
  virtual void dead();
  void Collide(AidKit &g) override;
  void Update() override;

 protected:
  LimitedValue hp_;
  LimitedValue mp_;
  int damage_;
  std::shared_ptr<Scene> parent_scene_;
  Point cur_vec_move_ = {1, 0};
  double speed_ = 2;
  void Move(Point vector_move);
};
class Princess : public Entity {
 public:
  Princess() {}
  Princess(Point pos, std::shared_ptr<Scene> parent_scene, char texture = 'P');
  void Collide(GameObject &g) override;
  void Collide(Knight &k) override;

 private:
};
class Projectile : public Entity {
 public:
  Projectile() {}
  Projectile(Point pos, int damage, Point vec_move, double speed,
             std::shared_ptr<Scene> parent_scene);
  void Collide(GameObject &g) override;
  void Collide(Wall &g) override;
  void Collide(Monster &g) override;
  void Collide(Knight &g) override;
  void Collide(Projectile &g) override;

 private:
  char texture_left_ = '<';
  char texture_right_ = '>';
  char texture_down_ = 'V';
  char texture_up_ = '^';
};
class ProjectileKnight : public Projectile {
 public:
  ProjectileKnight() {}
  ProjectileKnight(Point pos, int damage, Point vec_move, double speed,
                   Knight *kn);
  void Collide(Monster &g) override;

 private:
  Knight *kn_;
};
class Monster : public Entity {
 public:
  Monster() {}
  Monster(Point pos, char texture, LimitedValue hp, LimitedValue mp, int damage,
          std::shared_ptr<Scene> parent_scene, Point cur_vec_move,
          double speed);
  void Collide(Projectile &g) override;
};
class EntityWithProjoctile {
 public:
  EntityWithProjoctile(){};
  EntityWithProjoctile(int damage_projectile, double speed_projectile);
  void Set_damage_projectile(int damage_projectile);
  int Get_damage_projectile() const;
  void Set_speed_projectile(double speed_projectile);
  double Get_speed_projectile() const;

 protected:
  int damage_projectile_ = 2;
  double speed_projectile_;
};

class Dragon : public Monster, public EntityWithProjoctile {
 public:
  Dragon() {}
  Dragon(const Dragon &dragon, Point pos, std::shared_ptr<Scene> parent_scene);
  void Update() override;
  void Collide(GameObject &g) override;
  void Collide(Monster &m) override;
  void Collide(Wall &w) override;
  void Collide(Knight &k) override;
  void Set_radius(int radius);
  int Get_radius();
  void Create_projectile(Point pos, Point vec_move);

 private:
  int radius_ = 4;
  double radius_counter = 0;
  int cur_moves_i_ = 0;
  const Point vector_moves[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
};

class Zombie : public Monster {
 public:
  Zombie() {}
  Zombie(const Zombie &zombie, Point pos, std::shared_ptr<Scene> parent_scene);
  void Collide(GameObject &g) override;
  void Collide(Monster &m) override;
  void Collide(Wall &w) override;
  void Collide(Knight &k) override;

 private:
  void random_set_vec_move();
};
class Knight : public Entity, public EntityWithProjoctile {
 public:
  Knight() {}
  Knight(const Knight &knight, Point pos, std::shared_ptr<Scene> parent_scene,
         std::map<std::string, int> control_keys_);
  Knight(const Knight &knight, Point pos, std::shared_ptr<Scene> parent_scene);
  void KeyPressed(int key);
  void dead() override;
  void Collide(GameObject &g) override;
  void Collide(Monster &z) override;
  void Collide(Wall &w) override;
  int Get_points();
  void Set_points(int points);

 private:
  int points_ = 0;
  void PressedUp();
  void PressedDown();
  void PressedRight();
  void PressedLeft();
  void PressedSpace();
  std::map<std::string, int> control_keys_;
  std::map<int, void (Knight::*)()> key_map_ = {
      {KEY_UP, &Knight::PressedUp},
      {KEY_DOWN, &Knight::PressedDown},
      {KEY_LEFT, &Knight::PressedLeft},
      {KEY_RIGHT, &Knight::PressedRight},
      {' ', &Knight::PressedSpace}};
};

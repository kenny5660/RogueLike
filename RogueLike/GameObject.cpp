#include "pch.h"

#include <sstream>
enum fight_result { DEAD_A, DEAD_B, NO_DEAD, DEAD_BOTH };
std::pair<bool, bool> fight(Entity& a, Entity& b) {
  a.get_hp().set_value(a.get_hp().get_value() - b.Get_damage());
  b.get_hp().set_value(b.get_hp().get_value() - a.Get_damage());
  bool is_a_dead = a.get_hp().get_value() <= a.get_hp().get_min();
  bool is_b_dead = b.get_hp().get_value() <= b.get_hp().get_min();
  return std::make_pair(is_a_dead, is_b_dead);
}
GameObject::GameObject() {}

Point GameObject::Get_pos() const { return pos_; }

void GameObject::Set_pos(Point pos) { pos_ = pos; }

Point GameObject::Get_old_pos() { return old_pos_; }

ObjectId GameObject::Get_id() const { return id_; }

void GameObject::Set_id(ObjectId id) { id_ = id; }

char GameObject::Get_texture() const { return texture_char_; }
void GameObject::Set_texture(char texture) { texture_char_ = texture; }
void GameObject::Draw() {
  mvaddch(pos_.get_int_Y(), pos_.get_int_X(), texture_char_);
}
Wall::Wall(Point pos) {
  pos_ = pos;
  texture_char_ = '#';
}
Wall::Wall(const Wall& wall, Point pos) {
  pos_ = pos;
  texture_char_ = wall.texture_char_;
}

void Wall::Update() {}
void Wall::Collide(GameObject& g) { return g.Collide(*this); }

Entity::Entity() {}
LimitedValue& Entity::get_hp() { return hp_; }
LimitedValue& Entity::get_mp() { return mp_; }
void Entity::Update() { Move(cur_vec_move_); }
int Entity::Get_damage() { return damage_; }
void Entity::Set_damage(int damage) { damage_ = damage; }

Scene* Entity::Get_parent_scene() { return parent_scene_; }

void Entity::Set_parent_scene(Scene* scene) { parent_scene_ = scene; }

double Entity::Get_speed() { return speed_; }

void Entity::Set_speed(double speed) { speed_ = speed; }

void Entity::Set_cur_vec_move(VectorMath vec) { cur_vec_move_ = vec; }

void Entity::dead() { parent_scene_->DelObject(id_); }

void Entity::Move(VectorMath vector_move) {
  cur_vec_move_ = vector_move;
  Point newPos(
      pos_.X + vector_move.X * speed_ * parent_scene_->Get_elapsed_time(),
      pos_.Y + vector_move.Y * speed_ * parent_scene_->Get_elapsed_time());
  old_pos_.X = pos_.X;
  old_pos_.Y = pos_.Y;
  pos_.X = newPos.X;
  pos_.Y = newPos.Y;
}

Knight::Knight(Point pos, char texture) {
  pos_ = pos;
  texture_char_ = texture;
}
Knight::Knight(const Knight& knight, Point pos, Scene* parent_scene) {
  parent_scene_ = parent_scene;
  pos_ = pos;
  texture_char_ = knight.texture_char_;
  hp_ = knight.hp_;
  mp_ = knight.mp_;
  damage_ = knight.damage_;
  damage_projectile_ = knight.damage_projectile_;
  speed_ = knight.speed_;
  speed_projectile_ = knight.speed_projectile_;
}

void Knight::Collide(GameObject& g) { return g.Collide(*this); }
void Knight::Collide(Monster& z) {
  z.Set_pos(z.Get_old_pos());
  pos_ = old_pos_;
  auto result = fight(*this, z);
  if (result.first) {
    dead();
  }
  if (result.second) {
    Set_points(Get_points() + 1);
    z.dead();
  }
}
void Knight::Collide(Wall& z) { pos_ = old_pos_; }

int Knight::Get_points() { return points_; }

void Knight::Set_points(int points) { points_ = points; }

void Knight::key_pressed(int key) {
  const std::map<int, void (Knight::*)()> key_map = {
      {KEY_UP, &Knight::PressedUp},
      {KEY_DOWN, &Knight::PressedDown},
      {KEY_LEFT, &Knight::PressedLeft},
      {KEY_RIGHT, &Knight::PressedRight},
      {' ', &Knight::PressedSpace}};
  auto it = key_map.find(key);
  if (it != key_map.end()) {
    (this->*(it->second))();
  } else {
    // PressedNothing();
  }
}
void Knight::dead() { parent_scene_->Set_is_game_over(true); }
void Knight::PressedNothing() { cur_vec_move_ = {0, 0}; }
void Knight::PressedUp() { cur_vec_move_ = {0, -1}; }
void Knight::PressedDown() { cur_vec_move_ = {0, 1}; }
void Knight::PressedLeft() { cur_vec_move_ = {-1, 0}; }
void Knight::PressedRight() { cur_vec_move_ = {1, 0}; }
void Knight::PressedSpace() {
  parent_scene_->AddObject(std::shared_ptr<GameObject>(new ProjectileKnight(
      {pos_.X + cur_vec_move_.get_int_X(), pos_.Y + cur_vec_move_.get_int_Y()},
      damage_projectile_,
                           cur_vec_move_,speed_projectile_, this)));
}

Zombie::Zombie(Point pos, char texture) {
  pos_ = pos;
  texture_char_ = texture;
  cur_vec_move_ = {0, 0};
  random_set_vec_move();
}
Zombie::Zombie(const Zombie& zombie, Point pos, Scene* parent_scene) {
  parent_scene_ = parent_scene;
  pos_ = pos;
  texture_char_ = zombie.texture_char_;
  hp_ = zombie.hp_;
  mp_ = zombie.mp_;
  damage_ = zombie.damage_;
  speed_ = zombie.speed_;
  random_set_vec_move();
}
void Zombie::Collide(Knight& k) {
  k.Set_pos(k.Get_old_pos());
  pos_ = old_pos_;
  auto result = fight(*this, k);
  if (result.first) {
    k.Set_points(k.Get_points() + 1);
    dead();
  }
  if (result.second) {
    k.dead();
  }
}

void Zombie::Collide(Monster& z) {
  pos_ = old_pos_;
  random_set_vec_move();
}
void Zombie::Collide(Wall& w) {
  pos_ = old_pos_;
  random_set_vec_move();
};
void Zombie::random_set_vec_move() {
  const VectorMath vec_moves[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int new_rand = rand() % 4;
  cur_vec_move_ = vec_moves[new_rand];
}
void Zombie::Update() { Move(cur_vec_move_); }
void Zombie::Collide(GameObject& g) { return g.Collide(*this); }

AidKit::AidKit(Point pos, int hp_regen) {
  pos_ = pos;
  hp_regen_ = hp_regen;
}

AidKit::AidKit(const AidKit& aid, Point pos) {
  hp_regen_ = aid.hp_regen_;
  texture_char_ = aid.texture_char_;
  pos_ = pos;
}

void AidKit::Set_hp_regen(int hp_regen) { hp_regen_ = hp_regen; }

int AidKit::Get_hp_regen() { return hp_regen_; }

void AidKit::Update() {}

void AidKit::Collide(GameObject& g) { return g.Collide(*this); }

GuiPlayer::GuiPlayer(Point pos, std::shared_ptr<Knight> kn) {
  pos_ = pos;
  kn_ = kn;
}
void GuiPlayer::Draw() {
  std::stringstream ss;
  ss << "HP: " << kn_->get_hp().get_value() << "/" << kn_->get_hp().get_max();
  mvaddstr(pos_.get_int_Y(), pos_.get_int_X(), ss.str().c_str());
  ss.str(std::string());

  ss << "MP: " << kn_->get_mp().get_value() << "/" << kn_->get_mp().get_max();
  mvaddstr(pos_.get_int_Y() + 1, pos_.get_int_X(), ss.str().c_str());
  ss.str(std::string());

  ss << "Points: " << kn_->Get_points();
  mvaddstr(pos_.get_int_Y() + 2, pos_.get_int_X(), ss.str().c_str());
  ss.str(std::string());
}

void GuiPlayer::Update() {}

Projectile::Projectile(Point pos, int damage, VectorMath vec_move, double speed,
                       Scene* parent_scene) {
  pos_ = pos;
  cur_vec_move_ = vec_move;
  damage_ = damage;
  speed_ = speed;
  parent_scene_ = parent_scene;
  if (cur_vec_move_ == VectorMath{0, 1}) {
    texture_char_ = texture_down_;
  }
  if (cur_vec_move_ == VectorMath{0, -1}) {
    texture_char_ = texture_up_;
  }
  if (cur_vec_move_ == VectorMath{1, 0}) {
    texture_char_ = texture_right_;
  }
  if (cur_vec_move_ == VectorMath{-1, 0}) {
    texture_char_ = texture_left_;
  }
}
void Projectile::Collide(GameObject& g) { return g.Collide(*this); }

void Projectile::Collide(Wall& g) { dead(); }

void Projectile::Collide(Monster& g) {
  auto result = fight(*this, g);
  dead();
  if (result.second) {
    g.dead();
  }
}
void Projectile::Collide(Knight& g) {
  auto result = fight(*this, g);
  dead();
  if (result.second) {
    g.dead();
  }
}

void Projectile::Collide(Projectile& g) {
  g.dead();
  dead();
}

void Projectile::Update() { Move(cur_vec_move_); }

void Projectile::Set_texture_left(char t) { texture_left_ = t; }
void Projectile::Set_texture_right(char t) { texture_right_ = t; }
void Projectile::Set_texture_down(char t) { texture_down_ = t; }
void Projectile::Set_texture_up(char t) { texture_up_ = t; }

ProjectileKnight::ProjectileKnight(Point pos, int damage, VectorMath vec_move, double speed,
                                   Knight* kn)
    : Projectile(pos, damage, vec_move, speed,kn->Get_parent_scene()), kn_(kn) {}

void ProjectileKnight::Collide(Monster& g) {
  auto result = fight(*this, g);
  dead();
  if (result.second) {
    kn_->Set_points(kn_->Get_points() + 1);
    g.dead();
  }
}

Dragon::Dragon(Point pos, char texture) {
  pos_ = pos;
  texture_char_ = texture;
}

Dragon::Dragon(const Dragon& dragon, Point pos, Scene* parent_scene) {
  parent_scene_ = parent_scene;
  pos_ = pos;
  texture_char_ = dragon.texture_char_;
  hp_ = dragon.hp_;
  mp_ = dragon.mp_;
  damage_ = dragon.damage_;
  damage_projectile_ = dragon.damage_projectile_;
  radius_ = dragon.radius_;
  speed_ = dragon.speed_;
  speed_projectile_ = dragon.speed_projectile_;
  // cur_moves_i_ = rand() % 4;
}

void Dragon::Update() {
  radius_counter += speed_ * parent_scene_->Get_elapsed_time();
  if (radius_counter >= radius_ - 1) {
    cur_moves_i_++;
    radius_counter = 0;
    if (cur_moves_i_ >= 4) {
      cur_moves_i_ = 0;
    }
    int projectile_vector = rand() % 3;
    if (cur_moves_i_ == projectile_vector) projectile_vector++;
    Create_projectile(pos_, vector_moves[projectile_vector]);
  }

  Move(vector_moves[cur_moves_i_]);
}

void Dragon::Collide(GameObject& g) { return g.Collide(*this); }

void Dragon::Collide(Monster& z) {
  pos_ = old_pos_;
  radius_counter--;
}

void Dragon::Collide(Wall& w) { pos_ = old_pos_; }

void Dragon::Collide(Knight& k) {
  pos_ = old_pos_;
  radius_counter--;
  k.Set_pos(k.Get_old_pos());
  auto result = fight(*this, k);
  if (result.first) {
    k.Set_points(k.Get_points() + 1);
    dead();
  }
  if (result.second) {
    k.dead();
  }
}

void Dragon::Set_radius(int radius) { radius_ = radius; }

int Dragon::Get_radius() { return radius_; }

void Dragon::Create_projectile(Point pos, VectorMath vec_move) {
  parent_scene_->AddObject(std::shared_ptr<GameObject>(new Projectile(
      {pos.X + vec_move.get_int_X(), pos.Y + vec_move.get_int_Y()},
      damage_projectile_, vec_move,speed_projectile_, this->parent_scene_)));
}

void Entity::Collide(AidKit& g) {
  hp_.set_value(hp_.get_value() + g.Get_hp_regen());
  parent_scene_->DelObject(g.Get_id());
}

void Monster::Collide(Projectile& g) { g.Collide(*this); }

void EntityWithProjoctile::Set_damage_projectile(int damage_projectile) {
  damage_projectile_ = damage_projectile;
}

int EntityWithProjoctile::Get_damage_projectile() { return damage_projectile_; }

void EntityWithProjoctile::Set_speed_projectile(double speed_projectile) {
  speed_projectile_ = speed_projectile;
}

double EntityWithProjoctile::Get_speed_projectile() { return speed_projectile_; }

#include "pch.h"
enum fight_result { DEAD_A, DEAD_B, NO_DEAD, DEAD_BOTH };
std::pair<bool, bool> fight(Entity& a, Entity& b) {
  a.get_hp().set_value(a.get_hp().get_value() - b.get_damage());
  b.get_hp().set_value(b.get_hp().get_value() - a.get_damage());
  bool is_a_dead = a.get_hp().get_value() <= a.get_hp().get_min();
  bool is_b_dead = b.get_hp().get_value() <= b.get_hp().get_min();
  return std::make_pair(is_a_dead, is_b_dead);
}
GameObject::GameObject() {}

Point GameObject::get_pos() const { return pos_; }

void GameObject::set_pos(Point pos) { pos_ = pos; }

Point GameObject::get_old_pos() { return old_pos_; }

ObjectId GameObject::get_id() const { return id_; }

void GameObject::set_id(ObjectId id) { id_ = id; }

char GameObject::get_texture() const { return texture_char_; }
void GameObject::set_texture(char texture) { texture_char_ = texture; }
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
int Entity::get_damage() { return damage_; }
void Entity::set_damage(int damage) { damage_ = damage; }

void Entity::set_parent_scene(Scene* scene) { parent_scene_ = scene; }

void Entity::dead() { parent_scene_->DelObject(id_); }

void Entity::Move(VectorMath vector_move) {
  Point newPos(pos_.X + vector_move.X, pos_.Y + vector_move.Y);
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
}

void Knight::Update() {}
void Knight::Collide(GameObject& g) { return g.Collide(*this); }
void Knight::Collide(Zombie& z) {
  z.set_pos(z.get_old_pos());
  pos_ = old_pos_;
  auto result = fight(*this, z);
  if (result.first) {
    dead();
  }
  if (result.second) {
    set_points(get_points() + 1);
    z.dead();
  }
}
void Knight::Collide(Wall& z) { pos_ = old_pos_; }

void Knight::Collide(Aid_kit& g) {
  hp_.set_value(hp_.get_value() + g.get_hp_regen());
  parent_scene_->DelObject(g.get_id());
}

int Knight::get_points() { return points_; }

void Knight::set_points(int points) { points_ = points; }

void Knight::key_pressed(int key) {
  const std::map<int, void (Knight::*)()> key_map = {
      {KEY_UP, &Knight::pressed_Up},
      {KEY_DOWN, &Knight::pressed_Down},
      {KEY_LEFT, &Knight::pressed_Left},
      {KEY_RIGHT, &Knight::pressed_Right}};
  auto it = key_map.find(key);
  if (it != key_map.end()) {
    (this->*(it->second))();
  }
}
void Knight::dead() { parent_scene_->set_is_game_over(true); }

void Knight::pressed_Up() { Move({0, -1}); }
void Knight::pressed_Down() { Move({0, 1}); }
void Knight::pressed_Left() { Move({-1, 0}); }
void Knight::pressed_Right() { Move({1, 0}); }

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
  random_set_vec_move();
}
void Zombie::Collide(Knight& k) {
  k.set_pos(k.get_old_pos());
  pos_ = old_pos_;
  auto result = fight(*this, k);
  if (result.first) {
    k.set_points(k.get_points() + 1);
    dead();
  }
  if (result.second) {
    k.dead();
  }
}
void Zombie::Collide(Aid_kit& g) {
  hp_.set_value(hp_.get_value() + g.get_hp_regen());
  parent_scene_->DelObject(g.get_id());
}
void Zombie::Collide(Zombie& z) {
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

Aid_kit::Aid_kit(Point pos, int hp_regen) {
  pos_ = pos;
  hp_regen_ = hp_regen;
}

Aid_kit::Aid_kit(const Aid_kit& aid, Point pos) {
  hp_regen_ = aid.hp_regen_;
  texture_char_ = aid.texture_char_;
  pos_ = pos;
}

void Aid_kit::set_hp_regen(int hp_regen) { hp_regen_ = hp_regen; }

int Aid_kit::get_hp_regen() { return hp_regen_; }

void Aid_kit::Update() {}

void Aid_kit::Collide(GameObject& g) { return g.Collide(*this); }


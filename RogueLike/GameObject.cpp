#include "pch.h"

GameObject::GameObject() {}

Point GameObject::get_pos() const { return pos_; }

void GameObject::set_pos(Point pos) { pos_ = pos; }

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

void Wall::Update() {}
void Wall::Collide(GameObject& g) { return g.Collide(*this); }

EmptyBlock::EmptyBlock(Point pos) {
  pos_ = pos;
  texture_char_ = '.';
}

void EmptyBlock::Update() {}

void EmptyBlock::Draw() {
  mvaddch(pos_.get_int_Y(), pos_.get_int_X(), texture_char_);
}

Entity::Entity() {}

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

void Knight::Update() {}
void Knight::Collide(GameObject& g) { return g.Collide(*this); }
void Knight::Collide(Zombie& z) {}
void Knight::Collide(Wall& z) { pos_ = old_pos_; }

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

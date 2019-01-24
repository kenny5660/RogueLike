#include "pch.h"

GameObject::GameObject() {}

Point GameObject::get_pos() const { return pos_; }

void GameObject::set_pos(Point pos) { pos_ = pos; }

ObjectId GameObject::get_id() const { return id_; }

void GameObject::set_id(ObjectId id) const { id_ = id; }

char GameObject::get_texture() const { return texture_char_; }
void GameObject::set_texture(char texture) { texture_char_ = texture; }

Wall::Wall(Point pos) {
  pos_ = pos;
  texture_char_ = '#';
}

void Wall::Update() {}

void Wall::Draw() {
  mvaddch(pos_.get_int_Y(), pos_.get_int_X(), texture_char_);
}

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
  pos_.X += vector_move.X;
  pos_.Y += vector_move.Y;
}

Knight::Knight(Point pos, char texture) {
  pos_ = pos;
  texture_char_ = texture;
}

void Knight::Update() {}

void Knight::Draw() {
  mvaddch(pos_.get_int_Y(), pos_.get_int_X(), texture_char_);
}
void Knight::key_pressed(int key) {
  const std::map<int, void (Knight::*)()> key_map = {
      {KEY_UP, &Knight::pressed_Up},
      {KEY_DOWN, &Knight::pressed_Down},
      {KEY_LEFT, &Knight::pressed_Left},
      {KEY_RIGHT, &Knight::pressed_Right}};
  (this->*(key_map.find(key)->second))();
}
void Knight::pressed_Up() { Move({0, -1}); }
void Knight::pressed_Down() { Move({0, 1}); }
void Knight::pressed_Left() { Move({-1, 0}); }
void Knight::pressed_Right() { Move({1, 0}); }

Zombie::Zombie(Point pos) {}
void Zombie::Update() {}
void Zombie::Draw() {}
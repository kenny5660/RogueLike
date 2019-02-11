#include "pch.h"

#include <sstream>
std::pair<bool, bool> fight(Entity& a, Entity& b) {
  LimitedValue a_hp = a.get_hp();
  a_hp.set_value(a.get_hp().get_value() - b.Get_damage());
  a.set_hp(a_hp);
  LimitedValue b_hp = b.get_hp();
  b_hp.set_value(b.get_hp().get_value() - a.Get_damage());
  b.set_hp(b_hp);
  bool is_a_dead = a.get_hp().get_value() <= a.get_hp().get_min();
  bool is_b_dead = b.get_hp().get_value() <= b.get_hp().get_min();
  return {is_a_dead, is_b_dead};
}
GameObject::GameObject() {}

GameObject::GameObject(Point pos, char texture)
    : pos_(pos), texture_char_(texture), old_pos_(pos) {}

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
Wall::Wall(Point pos, char texture) : GameObject(pos, texture) {}
Wall::Wall(const Wall& wall, Point pos) : GameObject(pos, wall.texture_char_) {}

void Wall::Collide(GameObject& g) { return g.Collide(*this); }

Entity::Entity() {}
Entity::Entity(Point pos, char texture, LimitedValue hp, LimitedValue mp,
               int damage,
               Scene* parent_scene, VectorMath cur_vec_move, double speed)
    :GameObject(pos,texture), hp_(hp), mp_(mp), damage_(damage), parent_scene_(parent_scene),cur_vec_move_(cur_vec_move),speed_(speed) {}
const LimitedValue& Entity::get_hp() { return hp_; }
const LimitedValue& Entity::get_mp() { return mp_; }
void Entity::set_hp(const LimitedValue& hp) { hp_ = hp; }
void Entity::set_mp(const LimitedValue& mp) { mp_ = mp; }
void Entity::Update() { Move(cur_vec_move_); }
int Entity::Get_damage() { return damage_; }
void Entity::Set_damage(int damage) { damage_ = damage; }

Scene* Entity::Get_parent_scene() { return parent_scene_; }

void Entity::Set_parent_scene(Scene* scene) { parent_scene_ = scene; }

double Entity::Get_speed() { return speed_; }

void Entity::Set_speed(double speed) { speed_ = speed; }

void Entity::Set_cur_vec_move(VectorMath vec) { cur_vec_move_ = vec; }
VectorMath Entity::Get_cur_vector_move() { return cur_vec_move_; }

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

Knight::Knight(const Knight& knight, Point pos, Scene* parent_scene,
               std::map<std::string, int> control_keys_)
    : Knight(knight, pos, parent_scene) {
  key_map_ = {{control_keys_["up"], &Knight::PressedUp},
              {control_keys_["down"], &Knight::PressedDown},
              {control_keys_["left"], &Knight::PressedLeft},
              {control_keys_["right"], &Knight::PressedRight},
              {control_keys_["fire"], &Knight::PressedSpace}};
}
Knight::Knight(const Knight& knight, Point pos, Scene* parent_scene)
    : Entity(pos, knight.texture_char_, knight.hp_, knight.mp_, knight.damage_,
             parent_scene, knight.cur_vec_move_, knight.speed_),EntityWithProjoctile(knight.damage_projectile_,knight.speed_projectile_) {
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

void Knight::KeyPressed(int key) {
  auto it = key_map_.find(key);
  if (it != key_map_.end()) {
    (this->*(it->second))();
  } else {
    // PressedNothing();
  }
}
void Knight::dead() { parent_scene_->Set_game_result(GameResult::LOSE); }
// void Knight::PressedNothing() { cur_vec_move_ = {0, 0}; }
void Knight::PressedUp() { cur_vec_move_ = {0, -1}; }
void Knight::PressedDown() { cur_vec_move_ = {0, 1}; }
void Knight::PressedLeft() { cur_vec_move_ = {-1, 0}; }
void Knight::PressedRight() { cur_vec_move_ = {1, 0}; }
void Knight::PressedSpace() {
  parent_scene_->AddObject(std::shared_ptr<GameObject>(new ProjectileKnight(
      {pos_.X + cur_vec_move_.get_int_X(), pos_.Y + cur_vec_move_.get_int_Y()},
      damage_projectile_, cur_vec_move_, speed_projectile_, this)));
}


Zombie::Zombie(const Zombie& zombie, Point pos, Scene* parent_scene)
    : Monster(pos, zombie.texture_char_, zombie.hp_, zombie.mp_, zombie.damage_,
              parent_scene, zombie.cur_vec_move_, zombie.speed_) {
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

void Zombie::Collide(Monster& m) {
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
void Zombie::Collide(GameObject& g) { return g.Collide(*this); }

AidKit::AidKit(Point pos, int hp_regen, char texture)
    : GameObject(pos, texture), hp_regen_(hp_regen) {}

AidKit::AidKit(const AidKit& aid, Point pos)
    : GameObject(pos, aid.texture_char_), hp_regen_(aid.hp_regen_) {}

void AidKit::Set_hp_regen(int hp_regen) { hp_regen_ = hp_regen; }

int AidKit::Get_hp_regen() { return hp_regen_; }

void AidKit::Collide(GameObject& g) { return g.Collide(*this); }

GuiPlayer::GuiPlayer(Point pos, std::shared_ptr<Knight> kn):GameObject(pos,0),kn_(kn) {
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

Projectile::Projectile(Point pos, int damage, VectorMath vec_move, double speed,
                       Scene* parent_scene):Entity(pos,' ',LimitedValue(0),LimitedValue(0),damage,parent_scene,vec_move,speed) {
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

ProjectileKnight::ProjectileKnight(Point pos, int damage, VectorMath vec_move,
                                   double speed, Knight* kn)
    : Projectile(pos, damage, vec_move, speed, kn->Get_parent_scene()),
      kn_(kn) {}

void ProjectileKnight::Collide(Monster& g) {
  auto result = fight(*this, g);
  dead();
  if (result.second) {
    kn_->Set_points(kn_->Get_points() + 1);
    g.dead();
  }
}


Dragon::Dragon(const Dragon& dragon, Point pos, Scene* parent_scene)
    : Monster(pos, dragon.texture_char_, dragon.hp_, dragon.mp_, dragon.damage_,
             parent_scene, dragon.cur_vec_move_, dragon.speed_),
      EntityWithProjoctile(dragon.damage_projectile_,
                           dragon.speed_projectile_) {

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

void Dragon::Collide(Monster& m) {
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
      damage_projectile_, vec_move, speed_projectile_, this->parent_scene_)));
}

void Entity::Collide(AidKit& g) {
  hp_.set_value(hp_.get_value() + g.Get_hp_regen());
  parent_scene_->DelObject(g.Get_id());
}

Monster::Monster(Point pos, char texture, LimitedValue hp, LimitedValue mp,
                 int damage, Scene* parent_scene, VectorMath cur_vec_move,
                 double speed):Entity(pos,texture,hp,mp,damage,parent_scene,cur_vec_move,speed) {}

void Monster::Collide(Projectile& g) { g.Collide(*this); }

EntityWithProjoctile::EntityWithProjoctile(int damage_projectile,
                                           double speed_projectile):damage_projectile_(damage_projectile),speed_projectile_(speed_projectile) {}

void EntityWithProjoctile::Set_damage_projectile(int damage_projectile) {
  damage_projectile_ = damage_projectile;
}

int EntityWithProjoctile::Get_damage_projectile() { return damage_projectile_; }

void EntityWithProjoctile::Set_speed_projectile(double speed_projectile) {
  speed_projectile_ = speed_projectile;
}

double EntityWithProjoctile::Get_speed_projectile() {
  return speed_projectile_;
}

Princess::Princess(Point pos, Scene* parent_scene, char texture)
    : Entity(pos, texture, LimitedValue(0), LimitedValue(0),0,parent_scene,{0,0},0) {
}

void Princess::Collide(GameObject& g) { return g.Collide(*this); }

void Princess::Collide(Knight& k) {
  parent_scene_->Set_game_result(GameResult::WIN);
}

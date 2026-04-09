#include "turret.h"
#include "constants.h"
#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <unordered_map>

Turret::Turret(int x, int y, std::unordered_map<std::uint64_t, std::unique_ptr<Object>>* objects)
    : Object(ObjectType::Turret) {
  pos           = {(float)x, (float)y};
  size          = {1, 1};
  this->objects = objects;
}

Turret::~Turret() = default;

void Turret::draw() {
  DrawRectangle(pos.x * Constants::OFFSET,
                pos.y * Constants::OFFSET,
                size.x * Constants::OFFSET,
                size.y * Constants::OFFSET,
                BLUE);
}

void Turret::update(Player& p, Camera2D cam) {
  // get closest enemy.
  Object* closestEnemy    = nullptr;
  float   closestDistance = std::numeric_limits<float>::max();
  for (auto& [id, obj] : *objects) {
    if (obj->getType() == ObjectType::Enemy) {
      float distance = sqrt(pow(obj->getPos().x - pos.x, 2) + pow(obj->getPos().y - pos.y, 2));
      if (distance < closestDistance) {
        closestDistance = distance;
        closestEnemy    = obj.get();
      }
    }
  }

  // if enemy is in range, shoot it.
  if (closestDistance <= range * Constants::OFFSET) {
    closestEnemy->removeHealth(Constants::TURRET_DAMAGE);
  }
}

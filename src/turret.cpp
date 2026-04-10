#include "turret.h"
#include "constants.h"
#include "enemy.h"
#include "raylib.h"
#include "utils.h"
#include <cmath>
#include <limits>

Turret::Turret(int x, int y, ObjectMap* objects) : Object(ObjectType::Turret) {
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
  if (!canShoot) {
    shootTimer += 1.0f / 60.0f; // assuming 60 FPS
    if (shootTimer >= 1.0f / Constants::TURRET_FIRE_RATE) {
      canShoot   = true;
      shootTimer = 0.0f;
    }
    return;
  }

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
  if (closestEnemy && closestDistance <= range) {
    closestEnemy->removeHealth(Constants::TURRET_DAMAGE);
    canShoot   = false;
    shootTimer = 0.0f;
  }
}

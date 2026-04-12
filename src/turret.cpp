/**
 * @file turret.cpp
 * @brief Implementation of automated turret defense structures
 *
 * This file implements the Turret class, which represents automated defense structures
 * that automatically target and shoot at nearby enemies. Turrets find the closest enemy
 * within range and deal damage to them at a controlled fire rate.
 */

#include "turret.h"
#include "constants.h"
#include "enemy.h"
#include "raylib.h"
#include "textureManager.h"
#include "utils.h"
#include <cmath>
#include <limits>

extern TextureManager textureManager;

/**
 * @brief Construct a turret at grid position (x, y)
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param objects Pointer to the object map for finding enemies
 */
Turret::Turret(int x, int y, ObjectMap* objects) : Object(ObjectType::Turret) {
  pos           = {(float)x, (float)y};
  size          = {1, 1};
  this->objects = objects;
}

/**
 * @brief Construct a turret at grid position (x, y) with a texture
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param objects Pointer to the object map for finding enemies
 * @param texturePath Path to the texture file
 */
Turret::Turret(int x, int y, ObjectMap* objects, const char* texturePath)
    : Object(ObjectType::Turret) {
  pos           = {(float)x, (float)y};
  size          = {1, 1};
  this->objects = objects;
  texture       = textureManager.loadTexture(texturePath);
}

/**
 * @brief Destroy the turret
 */
Turret::~Turret() = default;

/**
 * @brief Draw the turret on screen
 */
void Turret::draw() {
  if (texture != nullptr && texture->id != 0) {
    Vector2 position = {pos.x * Constants::OFFSET, pos.y * Constants::OFFSET};
    DrawTextureEx(*texture, position, rotation, 1.0f, WHITE);
  } else {
    DrawRectangle(pos.x * Constants::OFFSET,
                  pos.y * Constants::OFFSET,
                  size.x * Constants::OFFSET,
                  size.y * Constants::OFFSET,
                  BLUE);
  }
}

/**
 * @brief Update turret state - find and shoot closest enemy
 * @param p Player reference (unused in current implementation)
 * @param cam Camera2D reference (unused in current implementation)
 */
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

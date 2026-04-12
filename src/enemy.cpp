/**
 * @file enemy.cpp
 * @brief Implementation of enemy entities that attack the core
 *
 * This file implements the Enemy class, which represents hostile entities that
 * move towards the core and damage it upon collision. Enemies spawn from spawners
 * and navigate towards the core's position. When they collide with the core,
 * they deal damage and bounce back.
 */

#include "enemy.h"
#include "constants.h"
#include "messages.h"
#include "player.h"
#include "raylib.h"
#include "textureManager.h"
#include <algorithm>
#include <cmath>

extern Messages       messages;
extern TextureManager textureManager;

/**
 * @brief Construct an enemy at position (x, y) targeting a core
 * @param x X coordinate
 * @param y Y coordinate
 * @param core Pointer to the core to target
 */
Enemy::Enemy(float x, float y, Core* core) : Object(ObjectType::Enemy), core(core) {
  pos = {x, y};
}

/**
 * @brief Construct an enemy at position (x, y) with texture targeting a core
 * @param x X coordinate
 * @param y Y coordinate
 * @param core Pointer to the core to target
 * @param texturePath Path to the texture file
 */
Enemy::Enemy(float x, float y, Core* core, const char* texturePath)
    : Object(ObjectType::Enemy), core(core) {
  pos     = {x, y};
  texture = textureManager.loadTexture(texturePath);
}

/**
 * @brief Destroy the enemy
 */
Enemy::~Enemy() = default;

/**
 * @brief Draw the enemy on screen
 */
void Enemy::draw() {
  if (texture != nullptr && texture->id != 0) {
    Vector2 position = {pos.x * Constants::OFFSET, pos.y * Constants::OFFSET};
    DrawTextureEx(*texture, position, rotation, 1.0f, WHITE);
  } else {
    DrawCircleV({pos.x * Constants::OFFSET - Constants::OFFSET / 2,
                 pos.y * Constants::OFFSET - Constants::OFFSET / 2},
                Constants::OFFSET / 2,
                RED);
  }
}

/**
 * @brief Update enemy state - move towards core and handle collision
 * @param p Player reference (unused in current implementation)
 * @param cam Camera2D reference (unused in current implementation)
 */
void Enemy::update(Player& p, Camera2D cam) {
  // calculate dircetion towards 0, 0
  float dx  = -pos.x;
  float dy  = -pos.y;
  float len = std::hypot(dx, dy);
  if (len > 0) {
    dx /= len;
    dy /= len;
  }
  pos.x += dx * 0.01f;
  pos.y += dy * 0.01f;

  // collision with core (4x4 tiles at 0,0 to 4,4)
  float enemyRadius = 0.5f;
  float closestX    = std::clamp(pos.x, 0.0f, 4.0f);
  float closestY    = std::clamp(pos.y, 0.0f, 4.0f);
  float distX       = pos.x - closestX;
  float distY       = pos.y - closestY;
  float distSquared = distX * distX + distY * distY;

  if (distSquared < enemyRadius * enemyRadius) {
    // damage the core
    if (core) {
      core->removeHealth(12);
    }
    // bounce back - push enemy outside collision and reverse direction
    float dist    = sqrt(distSquared);
    float overlap = enemyRadius - dist;
    if (dist > 0) {
      float pushX = (distX / dist) * overlap;
      float pushY = (distY / dist) * overlap;
      pos.x += pushX;
      pos.y += pushY;
    } else {
      // directly inside, push away from center
      pos.x += enemyRadius;
      pos.y += enemyRadius;
    }
    // reverse velocity to bounce back
    pos.x -= dx * 1.0f;
    pos.y -= dy * 1.0f;
  }
}

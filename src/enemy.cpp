#include "enemy.h"
#include "constants.h"
#include "player.h"
#include "raylib.h"
#include <algorithm>
#include <cmath>

Enemy::Enemy(float x, float y, Core* core) : Object(ObjectType::Enemy), core(core) {
  pos = {x, y};
}

Enemy::~Enemy() = default;

void Enemy::draw() {
  DrawCircleV({pos.x * OFFSET - OFFSET / 2, pos.y * OFFSET - OFFSET / 2}, OFFSET / 2, RED);
}

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
    pos.x -= dx * 0.05f;
    pos.y -= dy * 0.05f;
  }
}

/**
 * @file player.cpp
 * @brief Implementation of the player character
 *
 * This file implements the Player class, which represents the player character
 * in the game. The player can move using WASD keys, has an inventory system,
 * and interacts with game objects. Movement uses velocity-based physics with
 * friction for smooth control.
 */

#include "player.h"
#include "constants.h"
#include <cmath>
#include <print>
#include <raylib.h>

/**
 * @brief Update player movement based on input and delta time
 * @param dt Delta time for frame-independent movement
 */
void Player::move(double dt) {
  Vector2 dir = {0.0f, 0.0f};

  if (IsKeyDown(KEY_W))
    dir.y -= 1.0f;
  if (IsKeyDown(KEY_S))
    dir.y += 1.0f;
  if (IsKeyDown(KEY_D))
    dir.x += 1.0f;
  if (IsKeyDown(KEY_A))
    dir.x -= 1.0f;

  if (dir.x != 0.0f || dir.y != 0.0f) {
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    dir.x /= len;
    dir.y /= len;

    vel.x += dir.x * (Constants::PLAYER_SPEED / Constants::OFFSET) * dt;
    vel.y += dir.y * (Constants::PLAYER_SPEED / Constants::OFFSET) * dt;
  }

  pos.x += vel.x;
  pos.y += vel.y;

  vel.x *= 0.70f;
  vel.y *= 0.70f;
}

/**
 * @brief Get player position in grid coordinates
 * @return Grid position vector
 */
Vector2 Player::getPosGrid(void) {
  Vector2 out = {0, 0};

  if (pos.x >= 0 && pos.y >= 0) {
    out.x = std::floor(pos.x);
    out.y = std::floor(pos.y);
  } else {
    out.x = std::ceil(pos.x);
    out.y = std::ceil(pos.y);
  }

  return out;
}

/**
 * @brief Construct a Player at screen center
 */
Player::Player() {
  pos = {Constants::SCREEN_WIDTH / 2.0f / Constants::OFFSET,
         Constants::SCREEN_HEIGHT / 2.0f / Constants::OFFSET};
  vel = {0, 0};
}

/**
 * @brief Get player position
 * @return Position vector
 */
Vector2 Player::getPos() {
  return pos;
}

/**
 * @brief Set player position
 * @param newPos New position vector
 */
void Player::setPos(Vector2 newPos) {
  pos = newPos;
}

/**
 * @brief Get player velocity
 * @return Velocity vector
 */
Vector2 Player::getVel() {
  return vel;
}

/**
 * @brief Set player velocity
 * @param newVel New velocity vector
 */
void Player::setVel(Vector2 newVel) {
  vel = newVel;
}

/**
 * @brief Draw the player on screen
 */
void Player::draw() {
  DrawRectangle(pos.x * Constants::OFFSET,
                pos.y * Constants::OFFSET,
                Constants::OFFSET,
                Constants::OFFSET,
                BLACK);
}

/**
 * @brief Get player inventory
 * @return Inventory object
 */
Inventory Player::getInv() {
  return inv;
}

/**
 * @brief Set player inventory
 * @param i New inventory
 */
void Player::setInv(Inventory i) {
  inv = i;
}

/**
 * @brief Print player inventory to console
 */
void Player::drawInv() {
  for (const Slot& slot : inv.items) {
    std::print("{} x{},", (int)slot.item, slot.ammount);
  }

  std::print("\n");
}

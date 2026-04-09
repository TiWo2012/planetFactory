#include "player.h"
#include "constants.h"
#include <math.h>
#include <print>
#include <raylib.h>

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

Player::Player() {
  pos = {Constants::SCREEN_WIDTH / 2.0f / Constants::OFFSET,
         Constants::SCREEN_HEIGHT / 2.0f / Constants::OFFSET};
  vel = {0, 0};
}

Vector2 Player::getPos() {
  return pos;
}

void Player::setPos(Vector2 newPos) {
  pos = newPos;
}

Vector2 Player::getVel() {
  return vel;
}

void Player::setVel(Vector2 newVel) {
  vel = newVel;
}

void Player::draw() {
  DrawRectangle(pos.x * Constants::OFFSET,
                pos.y * Constants::OFFSET,
                Constants::OFFSET,
                Constants::OFFSET,
                BLACK);
}

Inventory Player::getInv() {
  return inv;
}

void Player::setInv(Inventory i) {
  inv = i;
}

void Player::drawInv() {
  for (const Slot& slot : inv.items) {
    std::print("{} x{},", (int)slot.item, slot.ammount);
  }

  std::print("\n");
}

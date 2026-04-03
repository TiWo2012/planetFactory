#pragma once

#include "constants.h"
#include <math.h>
#include <raylib.h>

class Player {
public:
  void move(double dt) {
    Vector2 dir = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W))
      dir.y -= 1.0f;
    if (IsKeyDown(KEY_S))
      dir.y += 1.0f;
    if (IsKeyDown(KEY_D))
      dir.x += 1.0f;
    if (IsKeyDown(KEY_A))
      dir.x -= 1.0f;

    // normalize only if moving
    if (dir.x != 0.0f || dir.y != 0.0f) {
      float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
      dir.x /= len;
      dir.y /= len;

      vel.x += dir.x * PLAYER_SPEED * dt;
      vel.y += dir.y * PLAYER_SPEED * dt;
    }

    pos.x += vel.x;
    pos.y += vel.y;

    vel.x *= 0.70f;
    vel.y *= 0.70f;
  }

  Vector2 getPosGrid(void) {
    Vector2 out = {0, 0};

    if (pos.x >= 0 && pos.y >= 0) {
      out.x = std::floor(pos.x / OFFSET);
      out.y = std::floor(pos.y / OFFSET);
    } else {
      out.x = std::ceil(pos.x / OFFSET);
      out.y = std::ceil(pos.y / OFFSET);
    }

    return out;
  }

  Player() {
    pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    vel = {0, 0};
  }

  Vector2 getPos() {
    return pos;
  }

  Vector2 getVel() {
    return vel;
  }

  void draw() {
    DrawRectangle(pos.x, pos.y, OFFSET, OFFSET, BLACK);
  }

private:
  Vector2 pos, vel;
};

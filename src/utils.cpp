#include "utils.h"
#include "belt.h"
#include "constants.h"
#include "enemy.h"
#include "spawner.h"
#include "turret.h"
#include <cmath>
#include <optional>
#include <print>
#include <raylib.h>

void drawArrow(Vector2 pos, Direction direction, Color color) {
  // Draw arrow based on direction
  switch (direction) {
  case Direction::Up:
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    break;
  case Direction::Down:
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  case Direction::Left:
    DrawLine(pos.x * Constants::OFFSET,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             color);
    DrawLine(pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  case Direction::Right:
    DrawLine(pos.x * Constants::OFFSET,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             color);
    DrawLine(pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  }
}

void drawGrid(int spacing, Camera2D cam) {
  float screenW = GetScreenWidth();
  float screenH = GetScreenHeight();

  Vector2 topLeft     = GetScreenToWorld2D({0, 0}, cam);
  Vector2 bottomRight = GetScreenToWorld2D({screenW, screenH}, cam);

  int startX = (int)floorf(topLeft.x / spacing) * spacing;
  int endX   = (int)floorf(bottomRight.x / spacing + 1) * spacing;

  int startY = (int)floorf(topLeft.y / spacing) * spacing;
  int endY   = (int)floorf(bottomRight.y / spacing + 1) * spacing;

  for (int x = startX; x <= endX; x += spacing) {
    DrawLine(x, startY, x, endY, LIGHTGRAY);
  }

  for (int y = startY; y <= endY; y += spacing) {
    DrawLine(startX, y, endX, y, LIGHTGRAY);
  }
}

void place(int x, int y, ObjectMap& o, ObjectType t, Direction dir) {
  std::uint64_t idx = 0;
  for (const auto& [key, _] : o) {
    if (key >= idx)
      idx = key + 1;
  }
  switch (t) {
  case ObjectType::Belt:
    o[idx] = std::make_unique<Belt>(x, y, dir, "assets/belt-straight.png");
    break;
  case ObjectType::Enemy:
    o[idx] = std::make_unique<Enemy>(x, y, static_cast<Core*>(o[0].get()));
    break;
  case ObjectType::Turret:
    o[idx] = std::make_unique<Turret>(x, y, &o);
    break;
  case ObjectType::Spawner:
    o[idx] = std::make_unique<Spawner>(x, y, o);
    break;
  default:
    break;
  }
}

Vector2 convertPosToGrid(Vector2 pos) {
  return {pos.x / Constants::OFFSET, pos.y / Constants::OFFSET};
}

void placeObject(ObjectMap& objects, Vector2 mousePos, Direction& placeDir) {
  Vector2 gridPos = convertPosToGrid(mousePos);

  if (IsKeyPressed(KEY_ONE)) {
    place(gridPos.x, gridPos.y, objects, ObjectType::Belt, placeDir);
  }

  if (IsKeyPressed(KEY_TWO)) {
    place(gridPos.x, gridPos.y, objects, ObjectType::Enemy, placeDir);
  }

  if (IsKeyPressed(KEY_THREE)) {
    place(gridPos.x, gridPos.y, objects, ObjectType::Turret, placeDir);
  }

  if (IsKeyPressed(KEY_FOUR)) {
    place(gridPos.x, gridPos.y, objects, ObjectType::Spawner, placeDir);
  }

  if (IsKeyPressed(KEY_R)) {
    switch (placeDir) {
    case Direction::Up:
      placeDir = Direction::Right;
      break;
    case Direction::Right:
      placeDir = Direction::Down;
      break;
    case Direction::Down:
      placeDir = Direction::Left;
      break;
    case Direction::Left:
      placeDir = Direction::Up;
      break;
    }
  }
}

std::optional<bool> drawGameOver() {
  DrawText("Game Over", 400, 300, 50, RED);

  DrawText("Press R to restart", 400, 350, 30, WHITE);
  if (IsKeyPressed(KEY_R)) {
    return std::make_optional(true);
  }

  DrawText("Press ESC to exit", 400, 380, 30, WHITE);
  if (IsKeyPressed(KEY_ESCAPE)) {
    return std::make_optional(false);
  }

  return std::nullopt;
}

void inializeObjects(ObjectMap& objects) {
  objects.clear();

  objects[0] = std::make_unique<Core>(0, 0, "assets/core.png");
  objects[1] = std::make_unique<Turret>(4, 4, &objects, "assets/turret.png");
  objects[2] = std::make_unique<Turret>(-1, -1, &objects, "assets/turret.png");
  objects[3] = std::make_unique<Turret>(4, -1, &objects, "assets/turret.png");
  objects[4] = std::make_unique<Turret>(-1, 4, &objects, "assets/turret.png");
}

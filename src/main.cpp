#include "belt.h"
#include "constants.h"
#include "core.h"
#include "enemy.h"
#include "object.h"
#include "player.h"
#include <cstddef>
#include <cstdint>
#include <format>
#include <math.h>
#include <memory>
#include <print>
#include <raylib.h>
#include <unordered_map>

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

void place(int                                                         x,
           int                                                         y,
           std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& o,
           std::uint64_t                                               idx,
           ObjectType                                                  t,
           Direction                                                   dir) {
  switch (t) {
  case ObjectType::Belt:
    o[idx] = std::make_unique<Belt>(x, y, dir);
    break;
  case ObjectType::Enemy:
    o[idx] = std::make_unique<Enemy>(x, y, static_cast<Core*>(o[0].get()));
    break;
  default:
    break;
  }
}

Vector2 convertPosToGrid(Vector2 pos) {
  return {pos.x / OFFSET, pos.y / OFFSET};
}

void placeObject(std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& objects,
                 std::uint64_t&                                              objectsIdx,
                 Vector2                                                     mousePos,
                 Direction&                                                  placeDir) {
  Vector2 gridPos = convertPosToGrid(mousePos);

  if (IsKeyPressed(KEY_ONE)) {
    place(gridPos.x, gridPos.y, objects, objectsIdx, ObjectType::Belt, placeDir);
    objectsIdx++;
  }

  if (IsKeyPressed(KEY_TWO)) {
    place(gridPos.x, gridPos.y, objects, objectsIdx, ObjectType::Enemy, placeDir);
    objectsIdx++;
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

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, std::format("Planet Factory - dev(V{})", VERSION);

  SetTargetFPS(60);

  Player player;
  double dt = 0;

  std::unordered_map<std::uint64_t, std::unique_ptr<Object>> objects;
  std::uint64_t                                              objectsIdx = 0;

  objects[0] = std::make_unique<Core>(0, 0);
  objectsIdx = 1;

  Camera2D cam            = {};
  Vector2  playerPixelPos = {player.getPos().x * OFFSET, player.getPos().y * OFFSET};
  cam.target              = playerPixelPos;
  cam.offset              = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
  cam.zoom                = 1.0f;

  Vector2   mousePos;
  Direction placeDir = Direction::Up;

  while (!WindowShouldClose()) {
    cam.target = {player.getPos().x * OFFSET, player.getPos().y * OFFSET};
    dt         = GetFrameTime();
    mousePos   = GetScreenToWorld2D(GetMousePosition(), cam);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    // display the position of the player (in grid coordinates)
    DrawText(std::format("{}, {}", player.getPosGrid().x, player.getPosGrid().y).c_str(),
             10,
             25,
             20,
             BLACK);

    BeginMode2D(cam);

    drawGrid(OFFSET, cam);

    // draw all objects
    for (size_t i = 0; i < objectsIdx; i++) {
      objects[i]->draw();
    }

    player.draw();

    EndMode2D();

    EndDrawing();

    player.move(dt);

    // handle place logic
    placeObject(objects, objectsIdx, mousePos, placeDir);

    for (size_t i = 0; i < objectsIdx; i++) {
      objects[i]->update(player, cam);
    }

    // handle resize logic
    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

#include "belt.h"
#include "constants.h"
#include "core.h"
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
           ObjectType                                                  t) {
  switch (t) {
  case ObjectType::Core:
    o[idx] = std::make_unique<Core>(x, y);
    break;
  case ObjectType::Belt:
    o[idx] = std::make_unique<Belt>(x, y);
    break;
  }
}

void placeObject(Player&                                                     player,
                 std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& objects,
                 std::uint64_t&                                              objectsIdx,
                 Vector2                                                     mousePos) {
  int gridX = (int)(mousePos.x / OFFSET);
  int gridY = (int)(mousePos.y / OFFSET);

  if (IsKeyPressed(KEY_ONE)) {
    place(gridX, gridY, objects, objectsIdx, ObjectType::Core);
    objectsIdx++;
  }

  if (IsKeyPressed(KEY_TWO)) {
    place(gridX, gridY, objects, objectsIdx, ObjectType::Belt);
    objectsIdx++;
  }
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

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

  Vector2 mousePos;

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
      objects[i].get()->draw();
    }

    player.draw();

    EndMode2D();

    EndDrawing();

    player.move(dt);

    // handle place logic
    placeObject(player, objects, objectsIdx, mousePos);

    for (size_t i = 0; i < objectsIdx; i++) {
      objects[i].get()->update(player, cam);
    }

    // handle resize logic
    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

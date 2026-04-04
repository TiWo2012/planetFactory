#include "constants.h"
#include "core.h"
#include "object.h"
#include "player.h"
#include <cstddef>
#include <cstdint>
#include <format>
#include <math.h>
#include <memory>
#include <raylib.h>
#include <unordered_map>

void drawGrid(int spacing, Camera2D cam) {
  float screenW = GetScreenWidth();
  float screenH = GetScreenHeight();

  Vector2 topLeft     = GetScreenToWorld2D((Vector2){0, 0}, cam);
  Vector2 bottomRight = GetScreenToWorld2D((Vector2){screenW, screenH}, cam);

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

void drawInv(const Inventory& inv) {}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  Player    player;
  double    dt  = 0;
  Inventory inv = {};

  std::unordered_map<std::uint64_t, std::unique_ptr<Object>> objects;
  std::uint64_t                                              objectsIdx = 0;

  objects[0] = std::make_unique<Core>(0, 0);
  objectsIdx = 1;

  Camera2D cam = {};
  cam.target   = player.getPos();
  cam.offset   = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
  cam.zoom     = 1.0f;

  while (!WindowShouldClose()) {
    cam.target = player.getPos();
    dt         = GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    DrawText(std::format("{}, {}", player.getPosGrid().x, player.getPosGrid().y).c_str(),
             10,
             25,
             20,
             BLACK);

    BeginMode2D(cam);

    drawGrid(OFFSET, cam);

    for (size_t i = 0; i < objectsIdx; i++) {
      objects[i].get()->draw();
    }

    player.draw();

    EndMode2D();

    EndDrawing();

    player.move(dt);

    for (size_t i = 0; i < objectsIdx; i++) {
      auto obj = objects[i].get();

      obj->update(player, cam);
    }

    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

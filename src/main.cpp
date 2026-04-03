#include "constants.h"
#include "player.h"
#include <array>
#include <format>
#include <math.h>
#include <print>
#include <raylib.h>

enum class Objects {
  Core,
  Belt,
  Miner,
};

enum class Items { Air = 0, Belt, Miner };

struct Slot {
  Items item;
  int   ammount;
};

struct Inventory {
  std::array<Slot, 64> items;
};

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

void drawObjectOnGrid(Objects obj, int x, int y) {
  switch (obj) {
  case Objects::Core: {
    DrawRectangle(x * OFFSET, y * OFFSET, 4 * OFFSET, 4 * OFFSET, GREEN);
  }
  }
}

void drawInv(const Inventory& inv) {
  for (const Slot& slot : inv.items) {
    std::print("{} x{},", (int)slot.item, slot.ammount);
  }

  std::print("\n");
}

Vector2 getMousePosGrid(Camera2D cam) {
  Vector2 mouseScreen = GetMousePosition();
  Vector2 mouseWorld  = GetScreenToWorld2D(mouseScreen, cam);

  Vector2 out = {0, 0};

  if (mouseWorld.x >= 0 && mouseWorld.y >= 0) {
    out.x = std::floor(mouseWorld.x / OFFSET);
    out.y = std::floor(mouseWorld.y / OFFSET);
  } else {
    out.x = std::ceil(mouseWorld.x / OFFSET);
    out.y = std::ceil(mouseWorld.y / OFFSET);
  }

  return out;
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  Player    player;
  double    dt  = 0;
  Inventory inv = {};

  Vector2 mousePos = {0, 0};

  Camera2D cam = {};
  cam.target   = player.getPos();
  cam.offset   = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
  cam.zoom     = 1.0f;

  while (!WindowShouldClose()) {
    cam.target = player.getPos();
    dt         = GetFrameTime();
    mousePos   = getMousePosGrid(cam);

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

    drawObjectOnGrid(Objects::Core, 0, 0);

    player.draw();

    EndMode2D();

    EndDrawing();

    player.move(dt);

    if (mousePos.x >= 0 && mousePos.x < 4 && mousePos.y >= 0 && mousePos.y < 4) {
      if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
        drawInv(inv);
      }
    }

    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

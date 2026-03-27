#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

struct Player {
  Vector2 pos, vel;
};

int main(void) {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  Player p = {};

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(p.pos.x, p.pos.y, 100, 100, BLACK);

    if (IsKeyDown(KEY_W)) {
      p.pos.y -= 100;
    } else if (IsKeyDown(KEY_S)) {
      p.pos.y += 100;
    }

    if (IsKeyDown(KEY_D)) {
      p.pos.x += 100;
    } else if (IsKeyDown(KEY_A)) {
      p.pos.x -= 100;
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void) {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

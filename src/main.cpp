#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 300

struct Player {
  Vector2 pos, vel;
};

int main(void) {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  Player p = {};
  double dt = 0;

  while (!WindowShouldClose()) {
    dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(p.pos.x, p.pos.y, 100, 100, BLACK);

    DrawFPS(10, 10);

    EndDrawing();

    if (IsKeyDown(KEY_W)) {
      p.vel.y -= PLAYER_SPEED * dt;
    } else if (IsKeyDown(KEY_S)) {
      p.vel.y += PLAYER_SPEED * dt;
    }

    if (IsKeyDown(KEY_D)) {
      p.vel.x += PLAYER_SPEED * dt;
    } else if (IsKeyDown(KEY_A)) {
      p.vel.x -= PLAYER_SPEED * dt;
    }

    p.pos.x = p.pos.x + p.vel.x;
    p.pos.y = p.pos.y + p.vel.y;

    p.vel.x *= 0.85;
    p.vel.y *= 0.85;
  }

  CloseWindow();
  return 0;
}

#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 300

struct Player {
  Vector2 pos, vel;
};

void drawGrid(int spacing, int width, int height) {
  width *= spacing;
  height *= spacing;

  // Vertical lines
  for (int x = 0; x <= width; x += spacing) {
    DrawLine(x, 0, x, height, BLACK);
  }

  // Horizontal lines
  for (int y = 0; y <= height; y += spacing) {
    DrawLine(0, y, width, y, BLACK);
  }
}

int main(void) {
  SetConfigFlags(FLAG_FULLSCREEN_MODE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  Player p  = {.pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, .vel = {0, 0}};
  double dt = 0;

  Camera2D cam = {};
  cam.target   = p.pos;
  cam.offset   = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
  cam.zoom     = 1.0f;

  while (!WindowShouldClose()) {
    cam.target = p.pos;
    dt         = GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    BeginMode2D(cam);

    drawGrid(32, 100, 100);

    DrawRectangle(p.pos.x, p.pos.y, 100, 100, BLACK);

    EndMode2D();

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

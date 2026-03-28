#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 300
#define OFFSET 32

struct Player {
  Vector2 pos, vel;
};

void drawGrid(int spacing, Camera2D cam) {
  float screenW = (float)GetScreenWidth();
  float screenH = (float)GetScreenHeight();

  Vector2 topLeft     = GetScreenToWorld2D((Vector2){0, 0}, cam);
  Vector2 bottomRight = GetScreenToWorld2D((Vector2){screenW, screenH}, cam);

  int startX = ((int)topLeft.x / spacing) * spacing;
  int endX   = ((int)bottomRight.x / spacing + 1) * spacing;

  int startY = ((int)topLeft.y / spacing) * spacing;
  int endY   = ((int)bottomRight.y / spacing + 1) * spacing;

  for (int x = startX; x <= endX; x += spacing) {
    DrawLine(x, startY, x, endY, LIGHTGRAY);
  }

  for (int y = startY; y <= endY; y += spacing) {
    DrawLine(startX, y, endX, y, LIGHTGRAY);
  }
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planetFactory");

  SetTargetFPS(60);

  Player p  = {.pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f}, .vel = {0, 0}};
  double dt = 0;

  Camera2D cam = {};
  cam.target   = p.pos;
  cam.offset   = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
  cam.zoom     = 1.0f;

  while (!WindowShouldClose()) {
    cam.target = p.pos;
    dt         = GetFrameTime();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    BeginMode2D(cam);

    drawGrid(OFFSET, cam);

    DrawRectangle(p.pos.x, p.pos.y, OFFSET, OFFSET, BLACK);

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

    p.pos.x += p.vel.x * dt;
    p.pos.y += p.vel.y * dt;

    p.vel.x *= 0.85;
    p.vel.y *= 0.85;

    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

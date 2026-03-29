#include <format>
#include <math.h>
#include <print>
#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 200
#define OFFSET 32

struct Player {
  Vector2 pos, vel;
};

enum class Objects {
  Core,
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

Vector2 getPosGrid(Player p) {
  Vector2 out = {0, 0};

  if (p.pos.x >= 0 && p.pos.y >= 0) {
    out.x = std::floor(p.pos.x / OFFSET);
    out.y = std::floor(p.pos.y / OFFSET);
  } else {
    out.x = std::ceil(p.pos.x / OFFSET);
    out.y = std::ceil(p.pos.y / OFFSET);
  }

  return out;
}

void drawObjectOnGrid(Objects obj, int x, int y) {
  switch (obj) {
  case Objects::Core: {
    DrawRectangle(x * OFFSET, y * OFFSET, 4 * OFFSET, 4 * OFFSET, GREEN);
  }
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

    DrawText(std::format("{}, {}", getPosGrid(p).x, getPosGrid(p).y).c_str(), 10, 25, 20, BLACK);

    BeginMode2D(cam);

    drawGrid(OFFSET, cam);

    drawObjectOnGrid(Objects::Core, 0, 0);

    // draw the player. always last!
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

    p.pos.x += p.vel.x;
    p.pos.y += p.vel.y;

    p.vel.x *= 0.70;
    p.vel.y *= 0.70;

    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }
  }

  CloseWindow();
  return 0;
}

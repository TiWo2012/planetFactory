#include "belt.h"
#include "constants.h"
#include "core.h"
#include "messages.h"
#include "object.h"
#include "player.h"
#include "textureManager.h"
#include "turret.h"
#include "utils.h"
#include <format>
#include <math.h>
#include <raylib.h>
#include <vector>

// Disclaimer: I am bad at art. don't judge my textures :)

Messages       messages;
TextureManager textureManager;

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(Constants::SCREEN_WIDTH,
             Constants::SCREEN_HEIGHT,
             std::format("Planet Factory - dev(V{})", Constants::VERSION).c_str());

  SetTargetFPS(60);

  Player player;
  double dt = 0;

  ObjectMap objects;

  objects[0] = std::make_unique<Core>(0, 0, "assets/core.png");
  objects[1] = std::make_unique<Turret>(4, 4, &objects, "assets/turret.png");
  objects[2] = std::make_unique<Turret>(-1, -1, &objects, "assets/turret.png");
  objects[3] = std::make_unique<Turret>(4, -1, &objects, "assets/turret.png");
  objects[4] = std::make_unique<Turret>(-1, 4, &objects, "assets/turret.png");

  Camera2D cam            = {};
  Vector2  playerPixelPos = {player.getPos().x * Constants::OFFSET,
                             player.getPos().y * Constants::OFFSET};
  cam.target              = playerPixelPos;
  cam.offset              = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
  cam.zoom                = 1.0f;

  Vector2   mousePos;
  Direction placeDir = Direction::Up;

  while (!WindowShouldClose()) {
    cam.target = {player.getPos().x * Constants::OFFSET, player.getPos().y * Constants::OFFSET};
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

    drawGrid(Constants::OFFSET, cam);

    // draw all objects
    for (auto& [id, obj] : objects) {
      if (obj)
        obj->draw();
    }

    player.draw();

    EndMode2D();

    EndDrawing();

    player.move(dt);

    // handle place logic
    placeObject(objects, mousePos, placeDir);

    for (auto& [id, obj] : objects) {
      if (obj)
        obj->update(player, cam);
    }

    // cleanup dead objects
    std::vector<std::uint64_t> deadObjects;
    for (auto& [id, obj] : objects) {
      if (obj && obj->isDead()) {
        deadObjects.push_back(id);
      }
    }
    for (auto id : deadObjects) {
      objects.erase(id);
    }

    // handle resize logic
    if (IsWindowResized()) {
      cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    }

    // handle zoom logic
    float zoomFactor = GetMouseWheelMove();
    if (zoomFactor != 0.0f) {
      cam.zoom += zoomFactor * 0.1f;
      if (cam.zoom < 0.5f)
        cam.zoom = 0.5f;
      if (cam.zoom > 3.0f)
        cam.zoom = 3.0f;
    }

    // handle messages
    auto msg = messages.getMessage();
    if (msg == MessageType::GameOver) {
      // TODO: show game over screen
      messages.setMessage(MessageType::None);
      break;
    }
    if (msg == MessageType::None) {
      // do nothing
      ;
    }
  }

  CloseWindow();

  return 0;
}

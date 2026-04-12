#include "belt.h"
#include "constants.h"
#include "core.h"
#include "messages.h"
#include "object.h"
#include "player.h"
#include "textureManager.h"
#include "utils.h"
#include <format>
#include <math.h>
#include <raylib.h>
#include <vector>

// Disclaimer: I am bad at art. don't judge my textures :)

Messages       messages(MessageType::None);
TextureManager textureManager;

void simulate(ObjectMap& objects,
              Player&    player,
              Camera2D&  cam,
              Vector2    mousePos,
              Direction& placeDir,
              double     dt) {
  static std::vector<Vector2> ocupied;

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

  player.move(dt);
}

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(Constants::SCREEN_WIDTH,
             Constants::SCREEN_HEIGHT,
             std::format("Planet Factory - dev(V{})", Constants::VERSION).c_str());

  SetTargetFPS(60);

  Player player;
  double dt = 0;

  ObjectMap objects;
  inializeObjects(objects);

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

    // handle messages
    auto msg = messages.getMessage();
    if (msg == MessageType::GameOver) {
      // TODO: show game over screen
      auto result = drawGameOver();
      if (result.has_value()) {
        if (result.value()) {
          // reset player
          player = Player();

          // reset camera
          Vector2 playerPixelPos = {player.getPos().x * Constants::OFFSET,
                                    player.getPos().y * Constants::OFFSET};
          cam.target             = playerPixelPos;
          cam.offset = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
          cam.zoom   = 1.0f;

          // reset objects
          inializeObjects(objects);

          // reset messages
          messages.setMessage(MessageType::None);
        } else {
          break;
        }
      }
    }
    if (msg == MessageType::None) {
      simulate(objects, player, cam, mousePos, placeDir, dt);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

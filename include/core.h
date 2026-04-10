#pragma once

#include "object.h"
#include "raylib.h"

class Player;

class Core : public Object {
public:
  Core() = default;
  Core(int x, int y);
  Core(int x, int y, const char* texturePath);
  Core(Vector2);
  Core(Vector2, const char* texturePath);
  Core(Core&&)                 = default;
  Core(const Core&)            = default;
  Core& operator=(Core&&)      = default;
  Core& operator=(const Core&) = default;
  ~Core()                      = default;

  void draw() override;
  void update(Player& p, Camera2D cam) override;

  Vector2 getCorePos() const;
  Vector2 getCoreSize() const;

  void collideWithPlayer(Player& player);

private:
};

#pragma once

#include "object.h"
#include "raylib.h"

class Player;

class Core : public Object {
public:
  Core() = default;
  Core(int x, int y);
  Core(Vector2);
  Core(Core&&)                 = default;
  Core(const Core&)            = default;
  Core& operator=(Core&&)      = default;
  Core& operator=(const Core&) = default;
  ~Core()                      = default;

  void draw();

  Vector2 getCorePos() const;
  Vector2 getCoreSize() const;

  void collideWithPlayer(Player& player);

private:
};

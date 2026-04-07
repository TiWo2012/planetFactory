#pragma once

#include "object.h"
#include "player.h"
#include "raylib.h"

class Belt : public Object {
public:
  Belt(float x, float y);
  Belt(Vector2 pos);
  Belt()                       = default;
  Belt(Belt&&)                 = default;
  Belt(const Belt&)            = default;
  Belt& operator=(Belt&&)      = default;
  Belt& operator=(const Belt&) = default;
  ~Belt()                      = default;

  void draw() override;
  void update(Player& p, Camera2D cam) override;

private:
  Items content = Items::None;
};

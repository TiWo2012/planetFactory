#pragma once

#include "core.h"
#include "object.h"

class Enemy : public Object {
public:
  Enemy(float x, float y, Core* core);
  ~Enemy();

  void draw() override;
  void update(Player& p, Camera2D cam) override;

private:
  Core* core = nullptr;
};

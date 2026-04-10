#pragma once

#include "constants.h"
#include "object.h"
#include "utils.h"

class Turret : public Object {
public:
  Turret(int x, int y, ObjectMap* objects);
  ~Turret();

  void draw() override;
  void update(Player& p, Camera2D cam) override;

private:
  ObjectMap* objects;
  int        range      = Constants::TURRET_RANGE;
  bool       canShoot   = true;
  float      shootTimer = 0.0f;
};

#pragma once

#include "constants.h"
#include "object.h"
#include <cstdint>
#include <memory>
#include <unordered_map>

class Turret : public Object {
public:
  Turret(int x, int y, std::unordered_map<std::uint64_t, std::unique_ptr<Object>>* objects);
  ~Turret();

  void draw() override;
  void update(Player& p, Camera2D cam) override;

private:
  std::unordered_map<std::uint64_t, std::unique_ptr<Object>>* objects;
  int                                                         range      = Constants::TURRET_RANGE;
  bool                                                        canShoot   = true;
  float                                                       shootTimer = 0.0f;
};

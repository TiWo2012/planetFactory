#pragma once

#include "object.h"
#include "utils.h"

class Spawner : public Object {
public:
  Spawner(int x, int y, ObjectMap& objectMap);
  ~Spawner() = default;

  void update(Player& p, Camera2D cam) override;
  void draw() override;

private:
  float      spawnTimer = 0.0f;
  bool       canSpawn   = true;
  ObjectMap* objectMap  = nullptr;
};

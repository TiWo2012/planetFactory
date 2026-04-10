#include "spawner.h"
#include "constants.h"
#include "core.h"
#include "enemy.h"
#include "raylib.h"
#include "utils.h"

Spawner::Spawner(int x, int y, ObjectMap& objectMap) : Object(ObjectType::Spawner) {
  pos             = Vector2{(float)x, (float)y};
  this->objectMap = &objectMap;
}

void Spawner::update(Player& p, Camera2D cam) {
  spawnTimer += GetFrameTime();
  if (spawnTimer >= Constants::ENEMY_SPAWN_INTERVAL) {
    spawnTimer = 0.0f;
    canSpawn   = true;
  }

  if (canSpawn == true) {
    // add new object to the map
    Core* core = static_cast<Core*>(objectMap->at(0).get());
    objectMap->insert({objectMap->size(), std::make_unique<Enemy>(pos.x, pos.y, core)});
    canSpawn = false;
  }
}

void Spawner::draw() {
  DrawRectangleV({pos.x * Constants::OFFSET, pos.y * Constants::OFFSET},
                 Vector2{2 * Constants::OFFSET, 2 * Constants::OFFSET},
                 GRAY);
}

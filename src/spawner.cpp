/**
 * @file spawner.cpp
 * @brief Implementation of enemy spawner objects
 *
 * This file implements the Spawner class, which periodically spawns enemy entities
 * at its location. Spawners use a timer system to control spawn intervals and
 * add new enemies to the object map when ready.
 */

#include "spawner.h"
#include "constants.h"
#include "core.h"
#include "enemy.h"
#include "raylib.h"
#include "textureManager.h"
#include "utils.h"

extern TextureManager textureManager;

/**
 * @brief Construct a spawner at grid position (x, y)
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param objectMap Reference to the object map for spawning enemies
 */
Spawner::Spawner(int x, int y, ObjectMap& objectMap) : Object(ObjectType::Spawner) {
  pos             = Vector2{(float)x, (float)y};
  this->objectMap = &objectMap;
}

/**
 * @brief Construct a spawner at grid position (x, y) with a texture
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param objectMap Reference to the object map for spawning enemies
 * @param texturePath Path to the texture file
 */
Spawner::Spawner(int x, int y, ObjectMap& objectMap, const char* texturePath)
    : Object(ObjectType::Spawner) {
  pos             = Vector2{(float)x, (float)y};
  this->objectMap = &objectMap;
  texture         = textureManager.loadTexture(texturePath);
}

/**
 * @brief Update spawner state - handle enemy spawning timer
 * @param p Player reference (unused in current implementation)
 * @param cam Camera2D reference (unused in current implementation)
 */
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

/**
 * @brief Draw the spawner on screen
 */
void Spawner::draw() {
  if (texture != nullptr && texture->id != 0) {
    Vector2 position = {pos.x * Constants::OFFSET, pos.y * Constants::OFFSET};
    DrawTextureEx(*texture, position, rotation, 1.0f, WHITE);
  } else {
    DrawRectangleV({pos.x * Constants::OFFSET, pos.y * Constants::OFFSET},
                   Vector2{2 * Constants::OFFSET, 2 * Constants::OFFSET},
                   GRAY);
  }
}

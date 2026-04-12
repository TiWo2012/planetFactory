/**
 * @file core.cpp
 * @brief Implementation of the Core object - the main base that players must defend
 *
 * This file implements the Core class, which represents the central base structure
 * that enemies attempt to destroy. The core has health that decreases when damaged
 * by enemies. When health reaches zero, the game ends. Players can interact with
 * the core to access their inventory.
 */

#include "core.h"
#include "constants.h"
#include "messages.h"
#include "object.h"
#include "player.h"
#include "raylib.h"
#include "textureManager.h"

extern Messages       messages;
extern TextureManager textureManager;

/**
 * @brief Construct a core at grid position (x, y)
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 */
Core::Core(int x, int y) : Object(ObjectType::Core) {
  pos  = {(float)x, (float)y};
  size = {4, 4};
}

/**
 * @brief Construct a core at grid position (x, y) with a texture
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param texturePath Path to the texture file
 */
Core::Core(int x, int y, const char* texturePath) : Object(ObjectType::Core) {
  pos     = {(float)x, (float)y};
  size    = {4, 4};
  texture = textureManager.loadTexture(texturePath);
}

/**
 * @brief Construct a core at Vector2 position
 * @param position Position vector
 */
Core::Core(Vector2 position) : Object(ObjectType::Core) {
  pos  = position;
  size = {4, 4};
}

/**
 * @brief Construct a core at Vector2 position with a texture
 * @param position Position vector
 * @param texturePath Path to the texture file
 */
Core::Core(Vector2 position, const char* texturePath) : Object(ObjectType::Core) {
  pos     = position;
  size    = {4, 4};
  texture = textureManager.loadTexture(texturePath);
}

/**
 * @brief Draw the core on screen
 */
void Core::draw() {
  if (health > 0) {
    if (texture != nullptr && texture->id != 0) {
      Vector2 position = {pos.x * Constants::OFFSET, pos.y * Constants::OFFSET};
      DrawTextureEx(*texture, position, rotation, 1.0f, WHITE);
    } else {
      DrawRectangle(pos.x * Constants::OFFSET,
                    pos.y * Constants::OFFSET,
                    size.x * Constants::OFFSET,
                    size.y * Constants::OFFSET,
                    GREEN);
    }
  }
}

/**
 * @brief Get the core position
 * @return Position vector
 */
Vector2 Core::getCorePos() const {
  return pos;
}

/**
 * @brief Get the core size
 * @return Size vector
 */
Vector2 Core::getCoreSize() const {
  return size;
}

/**
 * @brief Handle collision between core and player
 * @param player Player reference to push out of collision
 */
void Core::collideWithPlayer(Player& player) {
  Vector2 playerPos  = player.getPos();
  Vector2 playerSize = {1, 1}; // Player size in grid units
  Vector2 corePos    = getCorePos();
  Vector2 coreSize   = getCoreSize();

  if (playerPos.x < corePos.x + coreSize.x && playerPos.x + playerSize.x > corePos.x
      && playerPos.y < corePos.y + coreSize.y && playerPos.y + playerSize.y > corePos.y) {
    float overlapLeft   = (playerPos.x + playerSize.x) - corePos.x;
    float overlapRight  = (corePos.x + coreSize.x) - playerPos.x;
    float overlapTop    = (playerPos.y + playerSize.y) - corePos.y;
    float overlapBottom = (corePos.y + coreSize.y) - playerPos.y;

    float minOverlap = overlapLeft;
    if (overlapRight < minOverlap)
      minOverlap = overlapRight;
    if (overlapTop < minOverlap)
      minOverlap = overlapTop;
    if (overlapBottom < minOverlap)
      minOverlap = overlapBottom;

    if (minOverlap == overlapLeft)
      player.setPos({corePos.x - playerSize.x, playerPos.y});
    else if (minOverlap == overlapRight)
      player.setPos({corePos.x + coreSize.x, playerPos.y});
    else if (minOverlap == overlapTop)
      player.setPos({playerPos.x, corePos.y - playerSize.y});
    else
      player.setPos({playerPos.x, corePos.y + coreSize.y});
  }
}

/**
 * @brief Update core state - check collision and health
 * @param p Player reference
 * @param cam Camera2D reference
 */
void Core::update(Player& p, Camera2D cam) {
  collideWithPlayer(p);

  if (health <= 0) {
    messages.setMessage(MessageType::GameOver);
  }

  if (isClicked(cam)) {
    p.drawInv();
  }
}

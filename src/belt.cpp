/**
 * @file belt.cpp
 * @brief Implementation of conveyor belt objects that transport items and push players
 *
 * This file implements the Belt class, which represents conveyor belts in the game.
 * Belts can move items between themselves and push players in their direction of movement.
 * They support different directions (Up, Down, Left, Right) and can link to adjacent belts
 * to form conveyor systems.
 */

#include "belt.h"
#include "constants.h"
#include "object.h"
#include "raylib.h"
#include "textureManager.h"
#include "utils.h"

extern TextureManager textureManager;

/**
 * @brief Construct a belt at grid position (x, y) with default Up direction
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 */
Belt::Belt(int x, int y) : Object(ObjectType::Belt), direction(Direction::Up) {
  pos  = {(float)x, (float)y};
  size = {1, 1};
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at grid position (x, y) with a texture
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param texturePath Path to the texture file
 */
Belt::Belt(int x, int y, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up) {
  pos     = {(float)x, (float)y};
  size    = {1, 1};
  texture = textureManager.loadTexture(texturePath);
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at position (x, y) with reference to object map
 * @param x X coordinate
 * @param y Y coordinate
 * @param obj Reference to the object map for finding adjacent belts
 */
Belt::Belt(float x, float y, const ObjectMap& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  pos  = {x, y};
  size = {1, 1};
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at position (x, y) with object map and texture
 * @param x X coordinate
 * @param y Y coordinate
 * @param obj Reference to the object map for finding adjacent belts
 * @param texturePath Path to the texture file
 */
Belt::Belt(float x, float y, const ObjectMap& obj, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  pos     = {x, y};
  size    = {1, 1};
  texture = textureManager.loadTexture(texturePath);
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at Vector2 position with object map
 * @param pos Position vector
 * @param obj Reference to the object map for finding adjacent belts
 */
Belt::Belt(Vector2 pos, const ObjectMap& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at Vector2 position with object map and texture
 * @param pos Position vector
 * @param obj Reference to the object map for finding adjacent belts
 * @param texturePath Path to the texture file
 */
Belt::Belt(Vector2 pos, const ObjectMap& obj, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
  texture   = textureManager.loadTexture(texturePath);
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at grid position (x, y) with specified direction
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param dir Direction of belt movement
 */
Belt::Belt(int x, int y, Direction dir) : Object(ObjectType::Belt), direction(dir) {
  pos       = {(float)x, (float)y};
  size      = {1, 1};
  direction = dir;
  updateRotationFromDirection();
}

/**
 * @brief Construct a belt at grid position (x, y) with direction and texture
 * @param x Grid X coordinate
 * @param y Grid Y coordinate
 * @param dir Direction of belt movement
 * @param texturePath Path to the texture file
 */
Belt::Belt(int x, int y, Direction dir, const char* texturePath)
    : Object(ObjectType::Belt), direction(dir) {
  pos       = {(float)x, (float)y};
  size      = {1, 1};
  direction = dir;
  texture   = textureManager.loadTexture(texturePath);
  updateRotationFromDirection();
}

/**
 * @brief Draw the belt on screen
 */
void Belt::draw() {
  if (texture != nullptr && texture->id != 0) {
    Vector2   position = {pos.x * Constants::OFFSET + Constants::OFFSET / 2.0f,
                          pos.y * Constants::OFFSET + Constants::OFFSET / 2.0f};
    Vector2   origin   = {texture->width / 2.0f, texture->height / 2.0f};
    Rectangle source   = {0, 0, (float)texture->width, (float)texture->height};
    Rectangle dest     = {position.x, position.y, (float)texture->width, (float)texture->height};
    DrawTexturePro(*texture, source, dest, origin, rotation * 90.0f, WHITE);
  } else {
    DrawRectangle(pos.x * Constants::OFFSET,
                  pos.y * Constants::OFFSET,
                  size.x * Constants::OFFSET,
                  size.y * Constants::OFFSET,
                  ORANGE);
    drawArrow(pos, direction, BLACK);
  }
}

/**
 * @brief Update belt state - move items and push player
 * @param p Player reference
 * @param cam Camera2D reference (unused in current implementation)
 */
void Belt::update(Player& p, Camera2D cam) {
  // Update next belt reference on each frame
  if (objectsMap) {
    updateNextBelt(*objectsMap);
  }

  // Move content if this belt has an item and there's a next belt that's empty
  if (content != Items::None && hasNext() && next->getContent() == Items::None) {
    next->setContent(content);
    content = Items::None;
  }

  if (isColiding(p.getPos(), {1, 1})) {
    // Push player in belt direction (gradual movement, not instant teleport)
    const float beltSpeed = (Constants::BELT_MOVE_SPEED / Constants::OFFSET) * 0.02f;
    if (direction == Direction::Up) {
      p.setVel({p.getVel().x, -beltSpeed});
    } else if (direction == Direction::Down) {
      p.setVel({p.getVel().x, beltSpeed});
    } else if (direction == Direction::Left) {
      p.setVel({-beltSpeed, p.getVel().y});
    } else if (direction == Direction::Right) {
      p.setVel({beltSpeed, p.getVel().y});
    }
  }
}

/**
 * @brief Set the object map reference for finding adjacent belts
 * @param obj Reference to the object map
 */
void Belt::setObjectsMap(const ObjectMap& obj) {
  objectsMap = &obj;
  updateNextBelt(obj);
}

/**
 * @brief Update reference to the next belt in the chain
 * @param obj Reference to the object map
 */
void Belt::updateNextBelt(const ObjectMap& obj) {
  next = findNextBelt(obj);
}

/**
 * @brief Find the next belt in the direction of movement
 * @param obj Reference to the object map
 * @return Pointer to the next belt, or nullptr if none exists
 */
Belt* Belt::findNextBelt(const ObjectMap& obj) {
  // Calculate expected position of next belt based on direction
  Vector2 nextPos = pos;
  switch (direction) {
  case Direction::Up:
    nextPos.y -= 1;
    break;
  case Direction::Down:
    nextPos.y += 1;
    break;
  case Direction::Left:
    nextPos.x -= 1;
    break;
  case Direction::Right:
    nextPos.x += 1;
    break;
  }

  for (const auto& pair : obj) {
    if (pair.second && pair.second->getType() == ObjectType::Belt) {
      if (pair.second->getPos().x == nextPos.x && pair.second->getPos().y == nextPos.y) {
        return static_cast<Belt*>(pair.second.get());
      }
    }
  }

  return nullptr;
}

/**
 * @brief Update rotation value based on current direction
 */
void Belt::updateRotationFromDirection() {
  switch (direction) {
  case Direction::Up:
    rotation = 0.0f;
    break;
  case Direction::Right:
    rotation = 1.0f;
    break;
  case Direction::Down:
    rotation = 2.0f;
    break;
  case Direction::Left:
    rotation = 3.0f;
    break;
  }
}

/**
 * @brief Set the belt direction and update rotation
 * @param dir New direction
 */
void Belt::setDirection(Direction dir) {
  direction = dir;
  updateRotationFromDirection();
}

/**
 * @brief Get the current belt direction
 * @return Current direction
 */
Direction Belt::getDirection() const {
  return direction;
}

/**
 * @brief Set the item content on the belt
 * @param item Item to place on belt
 */
void Belt::setContent(Items item) {
  content = item;
}

/**
 * @brief Get the current item content on the belt
 * @return Current item
 */
Items Belt::getContent() const {
  return content;
}

/**
 * @brief Set the next belt reference
 * @param belt Pointer to the next belt
 */
void Belt::setNext(Belt* belt) {
  next = belt;
}

/**
 * @brief Get the next belt reference
 * @return Pointer to the next belt
 */
Belt* Belt::getNext() const {
  return next;
}

/**
 * @brief Check if there is a next belt in the chain
 * @return True if next belt exists, false otherwise
 */
bool Belt::hasNext() const {
  return next != nullptr;
}

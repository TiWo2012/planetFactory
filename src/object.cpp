/**
 * @file object.cpp
 * @brief Implementation of the base Object class for all game entities
 *
 * This file implements the Object class, which serves as the base class for all
 * game objects. It provides common functionality such as position, size, health,
 * rotation, texture loading, mouse interaction detection, and collision detection.
 * All specific game objects (Belt, Core, Enemy, Turret, Spawner) inherit from this class.
 */

#include "object.h"
#include "constants.h"
#include "raylib.h"
#include "textureManager.h"
#include <cmath>

extern TextureManager textureManager;

/**
 * @brief Construct an Object with specified type
 * @param t Object type
 */
Object::Object(ObjectType t) : type(t), texture(nullptr) {}

/**
 * @brief Destroy the Object
 */
Object::~Object() = default;

/**
 * @brief Get the object position
 * @return Position vector
 */
Vector2 Object::getPos() const {
  return pos;
}

/**
 * @brief Get the object size
 * @return Size vector
 */
Vector2 Object::getSize() const {
  return size;
}

/**
 * @brief Get the X coordinate
 * @return X coordinate
 */
float Object::getX() const {
  return pos.x;
}

/**
 * @brief Get the Y coordinate
 * @return Y coordinate
 */
float Object::getY() const {
  return pos.y;
}

/**
 * @brief Get the width
 * @return Width
 */
float Object::getWidth() const {
  return size.x;
}

/**
 * @brief Get the height
 * @return Height
 */
float Object::getHeight() const {
  return size.y;
}

/**
 * @brief Get the current health
 * @return Health value
 */
int Object::getHealth() const {
  return health;
}

/**
 * @brief Set the health value
 * @param health New health value
 */
void Object::setHealth(int health) {
  this->health = health;
}

/**
 * @brief Remove health from the object
 * @param amount Amount of health to remove
 */
void Object::removeHealth(int amount) {
  health -= amount;
  if (health < 0) {
    health = 0;
  }
}

/**
 * @brief Add health to the object, capped at MAX_HEALTH
 * @param amount Amount of health to add
 */
void Object::addHealth(int amount) {
  health += amount;
  if (health > Constants::MAX_HEALTH) {
    health = Constants::MAX_HEALTH;
  }
}

/**
 * @brief Check if the object is dead (health <= 0)
 * @return True if dead, false otherwise
 */
bool Object::isDead() const {
  return health <= 0;
}

/**
 * @brief Get the rotation value
 * @return Rotation in degrees
 */
float Object::getRotation() const {
  return rotation;
}

/**
 * @brief Set the rotation value
 * @param rotation New rotation in degrees
 */
void Object::setRotation(float rotation) {
  this->rotation = rotation;
}

/**
 * @brief Convert mouse screen position to grid coordinates
 * @param cam Camera2D reference
 * @return Grid coordinates
 */
Vector2 getMousePosGrid(Camera2D cam) {
  Vector2 mouseScreen = GetMousePosition();
  Vector2 mouseWorld  = GetScreenToWorld2D(mouseScreen, cam);

  Vector2 out = {0, 0};

  if (mouseWorld.x >= 0 && mouseWorld.y >= 0) {
    out.x = std::floor(mouseWorld.x / Constants::OFFSET);
    out.y = std::floor(mouseWorld.y / Constants::OFFSET);
  } else {
    out.x = std::ceil(mouseWorld.x / Constants::OFFSET);
    out.y = std::ceil(mouseWorld.y / Constants::OFFSET);
  }

  return out;
}

/**
 * @brief Check if the object was clicked by the mouse
 * @param cam Camera2D reference
 * @return True if clicked, false otherwise
 */
bool Object::isClicked(Camera2D cam) {
  Vector2 mouse = getMousePosGrid(cam);

  if (mouse.x >= pos.x && mouse.x <= pos.x + size.x && mouse.y >= pos.y
      && mouse.y <= pos.y + size.y) {
    if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
      return true;
    }
  }

  return false;
}

/**
 * @brief Check if the mouse is hovering over the object
 * @param cam Camera2D reference
 * @return True if hovered, false otherwise
 */
bool Object::isHovered(Camera2D cam) {
  Vector2 mouse = getMousePosGrid(cam);

  return mouse.x >= pos.x && mouse.x <= pos.x + size.x && mouse.y >= pos.y
         && mouse.y <= pos.y + size.y;
}

/**
 * @brief Check if this object is colliding with another object
 * @param otherPos Position of the other object
 * @param otherSize Size of the other object
 * @return True if colliding, false otherwise
 */
bool Object::isColiding(Vector2 otherPos, Vector2 otherSize) {
  return pos.x < otherPos.x + otherSize.x && pos.x + size.x > otherPos.x
         && pos.y < otherPos.y + otherSize.y && pos.y + size.y > otherPos.y;
}

/**
 * @brief Load a texture for this object
 * @param path Path to the texture file
 */
void Object::loadTexture(const char* path) {
  texture = textureManager.loadTexture(path);
}

/**
 * @brief Get the object type
 * @return Object type
 */
ObjectType Object::getType() const {
  return type;
}

/**
 * @brief Check if an object of a specific type is adjacent to a position
 * @param localPos Position to check around
 * @param remoteObj Object to check
 * @param type Type of object to look for
 * @return True if object of type is adjacent, false otherwise
 */
bool Object::isObjectInProximity(Vector2 localPos, const Object& remoteObj, ObjectType type) {
  auto remotePos = remoteObj.getPos();

  // check if objectType is correct first
  if (remoteObj.getType() != type)
    return false;

  // check for north, east, south and west
  if ((localPos.x + 1 == remotePos.x && localPos.y == remotePos.y)
      || (localPos.x - 1 == remotePos.x && localPos.y == remotePos.y)
      || (localPos.x == remotePos.x && localPos.y + 1 == remotePos.y)
      || (localPos.x == remotePos.x && localPos.y - 1 == remotePos.y)) {
    return true;
  }

  return false;
}

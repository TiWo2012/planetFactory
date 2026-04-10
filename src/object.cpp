#include "object.h"
#include "constants.h"
#include "raylib.h"
#include <cmath>

Object::Object(ObjectType t) : type(t) {}
Object::~Object() = default;

Vector2 Object::getPos() const {
  return pos;
}

Vector2 Object::getSize() const {
  return size;
}

float Object::getX() const {
  return pos.x;
}

float Object::getY() const {
  return pos.y;
}

float Object::getWidth() const {
  return size.x;
}

float Object::getHeight() const {
  return size.y;
}

int Object::getHealth() const {
  return health;
}

void Object::setHealth(int health) {
  this->health = health;
}

void Object::removeHealth(int amount) {
  health -= amount;
  if (health < 0) {
    health = 0;
  }
}

void Object::addHealth(int amount) {
  health += amount;
  if (health > Constants::MAX_HEALTH) {
    health = Constants::MAX_HEALTH;
  }
}

bool Object::isDead() const {
  return health <= 0;
}

float Object::getRotation() const {
  return rotation;
}

void Object::setRotation(float rotation) {
  this->rotation = rotation;
}

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

bool Object::isHovered(Camera2D cam) {
  Vector2 mouse = getMousePosGrid(cam);

  return mouse.x >= pos.x && mouse.x <= pos.x + size.x && mouse.y >= pos.y
         && mouse.y <= pos.y + size.y;
}

bool Object::isColiding(Vector2 otherPos, Vector2 otherSize) {
  return pos.x < otherPos.x + otherSize.x && pos.x + size.x > otherPos.x
         && pos.y < otherPos.y + otherSize.y && pos.y + size.y > otherPos.y;
}

void Object::loadTexture(const char* path) {
  texture = LoadTexture(path);
}

ObjectType Object::getType() const {
  return type;
}

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

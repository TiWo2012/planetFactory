#include "object.h"
#include "raylib.h"

Object::Object()  = default;
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

bool Object::isClicked() {
  Vector2 mouse = GetMousePosition();
  if (mouse.x >= pos.x && mouse.x <= pos.x + size.x && mouse.y >= pos.y
      && mouse.y <= pos.y + size.y) {
    if (IsMouseButtonReleased(MouseButton::MOUSE_BUTTON_LEFT)) {
      return true;
    }
  }
  return false;
}

bool Object::isHovered() {
  Vector2 mouse = GetMousePosition();
  return mouse.x >= pos.x && mouse.x <= pos.x + size.x && mouse.y >= pos.y
         && mouse.y <= pos.y + size.y;
}

bool Object::isColiding(Vector2 otherPos, Vector2 otherSize) {
  return pos.x < otherPos.x + otherSize.x && pos.x + size.x > otherPos.x
         && pos.y < otherPos.y + otherSize.y && pos.y + size.y > otherPos.y;
}

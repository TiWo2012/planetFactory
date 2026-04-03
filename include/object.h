#pragma once

#include "raylib.h"

class Object {
public:
  Object();
  Object(Object&&)                 = default;
  Object(const Object&)            = default;
  Object& operator=(Object&&)      = default;
  Object& operator=(const Object&) = default;
  ~Object();

  virtual void draw() = 0;

  bool isClicked();
  bool isHovered();
  bool isColiding(Vector2 otherPos, Vector2 otherSize);

  Vector2 getPos() const;
  Vector2 getSize() const;
  float   getX() const;
  float   getY() const;
  float   getWidth() const;
  float   getHeight() const;

protected:
  Vector2   pos     = {};
  Vector2   size    = {};
  Texture2D texture = {};
};

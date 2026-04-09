#pragma once

#include "player.h"
#include "raylib.h"

enum class ObjectType {
  Core,
  Belt,
  Enemy,
  Turret,
};

class Object {
public:
  Object(ObjectType t);
  Object(Object&&)                 = default;
  Object(const Object&)            = default;
  Object& operator=(Object&&)      = default;
  Object& operator=(const Object&) = default;
  ~Object();

  virtual void draw()                          = 0;
  virtual void update(Player& p, Camera2D cam) = 0;

  bool isClicked(Camera2D cam);
  bool isHovered(Camera2D cam);
  bool isColiding(Vector2 otherPos, Vector2 otherSize);

  bool isObjectInProximity(Vector2 localPos, const Object& remoteObj, ObjectType type);

  Vector2    getPos() const;
  Vector2    getSize() const;
  float      getX() const;
  float      getY() const;
  float      getWidth() const;
  float      getHeight() const;
  ObjectType getType() const;
  void       loadTexture(const char* path);
  int        getHealth() const;
  void       setHealth(int health);
  void       removeHealth(int amount);
  void       addHealth(int amount);
  bool       isDead() const;

protected:
  Vector2    pos     = {};
  Vector2    size    = {};
  Texture2D  texture = {};
  ObjectType type;
  int        health = 100;
};

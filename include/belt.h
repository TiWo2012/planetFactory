#pragma once

#include "object.h"
#include "player.h"
#include "raylib.h"
#include "utils.h"

enum class Direction { Left, Right, Up, Down };

class Belt : public Object {
public:
  Belt(int x, int y);
  Belt(int x, int y, const char* texturePath);
  Belt(float x, float y, const ObjectMap& obj);
  Belt(float x, float y, const ObjectMap& obj, const char* texturePath);
  Belt(Vector2 pos, const ObjectMap& obj);
  Belt(Vector2 pos, const ObjectMap& obj, const char* texturePath);
  Belt(int x, int y, Direction dir);
  Belt(int x, int y, Direction dir, const char* texturePath);
  Belt()                       = default;
  Belt(Belt&&)                 = default;
  Belt(const Belt&)            = default;
  Belt& operator=(Belt&&)      = default;
  Belt& operator=(const Belt&) = default;
  ~Belt()                      = default;

  void      setObjectsMap(const ObjectMap& obj);
  void      setDirection(Direction dir);
  Direction getDirection() const;
  void      setContent(Items item);
  Items     getContent() const;
  void      setNext(Belt* belt);
  Belt*     getNext() const;
  bool      hasNext() const;

  void draw() override;
  void update(Player& p, Camera2D cam) override;
  void updateNextBelt(const ObjectMap& obj);

private:
  Belt* findNextBelt(const ObjectMap& obj);
  void  updateRotationFromDirection();

private:
  Items            content = Items::None;
  Belt*            next    = nullptr;
  Direction        direction;
  const ObjectMap* objectsMap = nullptr;
};

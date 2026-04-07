#include "belt.h"
#include "constants.h"
#include "object.h"
#include "raylib.h"
#include <iterator>

Belt::Belt(float x, float y) : Object(ObjectType::Belt) {
  pos  = {x, y};
  size = {1, 1};
}

Belt::Belt(Vector2 pos) : Object(ObjectType::Belt) {
  this->pos = pos;
  size      = {1, 1};
}

void Belt::draw() {
  DrawRectangle(pos.x * OFFSET, pos.y * OFFSET, size.x * OFFSET, size.y * OFFSET, ORANGE);
}

void Belt::update(Player& p, Camera2D cam) {}

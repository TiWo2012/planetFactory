#include "belt.h"
#include "constants.h"
#include "object.h"
#include "raylib.h"
#include "utils.h"

Belt::Belt(int x, int y) : Object(ObjectType::Belt), direction(Direction::Up) {
  pos  = {(float)x, (float)y};
  size = {1, 1};
  updateRotationFromDirection();
}

Belt::Belt(int x, int y, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up) {
  pos  = {(float)x, (float)y};
  size = {1, 1};
  loadTexture(texturePath);
  updateRotationFromDirection();
}

Belt::Belt(float x, float y, const ObjectMap& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  pos  = {x, y};
  size = {1, 1};
  updateRotationFromDirection();
}

Belt::Belt(float x, float y, const ObjectMap& obj, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  pos  = {x, y};
  size = {1, 1};
  loadTexture(texturePath);
  updateRotationFromDirection();
}

Belt::Belt(Vector2 pos, const ObjectMap& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
  updateRotationFromDirection();
}

Belt::Belt(Vector2 pos, const ObjectMap& obj, const char* texturePath)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
  loadTexture(texturePath);
  updateRotationFromDirection();
}

Belt::Belt(int x, int y, Direction dir) : Object(ObjectType::Belt), direction(dir) {
  pos       = {(float)x, (float)y};
  size      = {1, 1};
  direction = dir;
  updateRotationFromDirection();
}

Belt::Belt(int x, int y, Direction dir, const char* texturePath)
    : Object(ObjectType::Belt), direction(dir) {
  pos       = {(float)x, (float)y};
  size      = {1, 1};
  direction = dir;
  loadTexture(texturePath);
  updateRotationFromDirection();
}

void Belt::draw() {
  if (texture.id != 0) {
    Vector2 position = {pos.x * Constants::OFFSET, pos.y * Constants::OFFSET};
    DrawTextureEx(texture, position, rotation * 90.0f, 1.0f, WHITE);
  } else {
    DrawRectangle(pos.x * Constants::OFFSET,
                  pos.y * Constants::OFFSET,
                  size.x * Constants::OFFSET,
                  size.y * Constants::OFFSET,
                  ORANGE);
    drawArrow(pos, direction, BLACK);
  }
}

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

void Belt::setObjectsMap(const ObjectMap& obj) {
  objectsMap = &obj;
  updateNextBelt(obj);
}

void Belt::updateNextBelt(const ObjectMap& obj) {
  next = findNextBelt(obj);
}

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

void Belt::setDirection(Direction dir) {
  direction = dir;
  updateRotationFromDirection();
}

Direction Belt::getDirection() const {
  return direction;
}

void Belt::setContent(Items item) {
  content = item;
}

Items Belt::getContent() const {
  return content;
}

void Belt::setNext(Belt* belt) {
  next = belt;
}

Belt* Belt::getNext() const {
  return next;
}

bool Belt::hasNext() const {
  return next != nullptr;
}

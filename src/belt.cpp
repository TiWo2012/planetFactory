#include "belt.h"
#include "constants.h"
#include "object.h"
#include "raylib.h"
#include "utlis.h"

Belt::Belt(int x, int y) : Object(ObjectType::Belt), direction(Direction::Up) {
  pos  = {(float)x, (float)y};
  size = {1, 1};
}

Belt::Belt(float x, float y, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  pos  = {x, y};
  size = {1, 1};
}

Belt::Belt(Vector2 pos, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj)
    : Object(ObjectType::Belt), direction(Direction::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
}

Belt::Belt(int x, int y, Direction dir) : Object(ObjectType::Belt), direction(dir) {
  pos       = {(float)x, (float)y};
  size      = {1, 1};
  direction = dir;
}

void Belt::draw() {
  DrawRectangle(pos.x * Constants::OFFSET,
                pos.y * Constants::OFFSET,
                size.x * Constants::OFFSET,
                size.y * Constants::OFFSET,
                ORANGE);

  drawArrow(pos, direction, BLACK);
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

void Belt::setObjectsMap(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj) {
  objectsMap = &obj;
  updateNextBelt(obj);
}

void Belt::updateNextBelt(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj) {
  next = findNextBelt(obj);
}

Belt* Belt::findNextBelt(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj) {
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

void Belt::setDirection(Direction dir) {
  direction = dir;
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

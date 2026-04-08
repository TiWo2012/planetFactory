#include "belt.h"
#include "constants.h"
#include "object.h"
#include "raylib.h"

Belt::Belt(int x, int y) : Object(ObjectType::Belt), direction(BeltDirection::Up) {
  pos  = {(float)x, (float)y};
  size = {1, 1};
}

Belt::Belt(float x, float y, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj)
    : Object(ObjectType::Belt), direction(BeltDirection::Up), objectsMap(&obj) {
  pos  = {x, y};
  size = {1, 1};
}

Belt::Belt(Vector2 pos, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj)
    : Object(ObjectType::Belt), direction(BeltDirection::Up), objectsMap(&obj) {
  this->pos = pos;
  size      = {1, 1};
}

void Belt::draw() {
  DrawRectangle(pos.x * OFFSET, pos.y * OFFSET, size.x * OFFSET, size.y * OFFSET, ORANGE);
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

  if (isColiding(p.getPos(), {OFFSET, OFFSET})) {
    // Push player in belt direction (gradual movement, not instant teleport)
    const float beltSpeed = BELT_MOVE_SPEED * 0.02f;
    if (direction == BeltDirection::Up) {
      p.setPos({p.getPos().x, p.getPos().y - beltSpeed});
    } else if (direction == BeltDirection::Down) {
      p.setPos({p.getPos().x, p.getPos().y + beltSpeed});
    } else if (direction == BeltDirection::Left) {
      p.setPos({p.getPos().x - beltSpeed, p.getPos().y});
    } else if (direction == BeltDirection::Right) {
      p.setPos({p.getPos().x + beltSpeed, p.getPos().y});
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
  case BeltDirection::Up:
    nextPos.y -= 1;
    break;
  case BeltDirection::Down:
    nextPos.y += 1;
    break;
  case BeltDirection::Left:
    nextPos.x -= 1;
    break;
  case BeltDirection::Right:
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

void Belt::setDirection(BeltDirection dir) {
  direction = dir;
}

BeltDirection Belt::getDirection() const {
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

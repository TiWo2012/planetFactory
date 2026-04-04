#include "core.h"
#include "constants.h"
#include "object.h"
#include "player.h"
#include "raylib.h"

Core::Core(int x, int y) : Object(ObjectType::Core) {
  pos  = {(float)x, (float)y};
  size = {4, 4};
}

Core::Core(Vector2 position) : Object(ObjectType::Core) {
  pos  = position;
  size = {4, 4};
}

void Core::draw() {
  if (texture.id == 0) {
    DrawRectangle(pos.x * OFFSET, pos.y * OFFSET, size.x * OFFSET, size.y * OFFSET, GREEN);
  } else {
    DrawTextureV(texture, pos, WHITE);
  }
}

Vector2 Core::getCorePos() const {
  return {pos.x * OFFSET, pos.y * OFFSET};
}

Vector2 Core::getCoreSize() const {
  return {size.x * OFFSET, size.y * OFFSET};
}

void Core::collideWithPlayer(Player& player) {
  Vector2 playerPos  = player.getPos();
  Vector2 playerSize = {OFFSET, OFFSET};
  Vector2 corePos    = getCorePos();
  Vector2 coreSize   = getCoreSize();

  if (playerPos.x < corePos.x + coreSize.x && playerPos.x + playerSize.x > corePos.x
      && playerPos.y < corePos.y + coreSize.y && playerPos.y + playerSize.y > corePos.y) {
    float overlapLeft   = (playerPos.x + playerSize.x) - corePos.x;
    float overlapRight  = (corePos.x + coreSize.x) - playerPos.x;
    float overlapTop    = (playerPos.y + playerSize.y) - corePos.y;
    float overlapBottom = (corePos.y + coreSize.y) - playerPos.y;

    float minOverlap = overlapLeft;
    if (overlapRight < minOverlap)
      minOverlap = overlapRight;
    if (overlapTop < minOverlap)
      minOverlap = overlapTop;
    if (overlapBottom < minOverlap)
      minOverlap = overlapBottom;

    if (minOverlap == overlapLeft)
      player.setPos({corePos.x - playerSize.x, playerPos.y});
    else if (minOverlap == overlapRight)
      player.setPos({corePos.x + coreSize.x, playerPos.y});
    else if (minOverlap == overlapTop)
      player.setPos({playerPos.x, corePos.y - playerSize.y});
    else
      player.setPos({playerPos.x, corePos.y + coreSize.y});
  }
}

ObjectType Core::getType() const {
  return type;
}

void Core::update(Player& p, Camera2D cam) {
  collideWithPlayer(p);

  if (isClicked(cam)) {
    p.drawInv();
  }
}

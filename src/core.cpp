#include "core.h"
#include "constants.h"
#include "messages.h"
#include "object.h"
#include "player.h"
#include "raylib.h"

extern Messages messages;

Core::Core(int x, int y) : Object(ObjectType::Core) {
  pos  = {(float)x, (float)y};
  size = {4, 4};
}

Core::Core(int x, int y, const char* texturePath) : Object(ObjectType::Core) {
  pos  = {(float)x, (float)y};
  size = {4, 4};
  loadTexture(texturePath);
}

Core::Core(Vector2 position) : Object(ObjectType::Core) {
  pos  = position;
  size = {4, 4};
}

Core::Core(Vector2 position, const char* texturePath) : Object(ObjectType::Core) {
  pos  = position;
  size = {4, 4};
  loadTexture(texturePath);
}

void Core::draw() {
  if (health > 0) {
    if (texture.id != 0) {
      DrawTextureV(texture, pos, WHITE);
    } else {
      DrawRectangle(pos.x * Constants::OFFSET,
                    pos.y * Constants::OFFSET,
                    size.x * Constants::OFFSET,
                    size.y * Constants::OFFSET,
                    GREEN);
    }
  }
}

Vector2 Core::getCorePos() const {
  return pos;
}

Vector2 Core::getCoreSize() const {
  return size;
}

void Core::collideWithPlayer(Player& player) {
  Vector2 playerPos  = player.getPos();
  Vector2 playerSize = {1, 1}; // Player size in grid units
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

void Core::update(Player& p, Camera2D cam) {
  collideWithPlayer(p);

  if (health <= 0) {
    messages.setMessage(MessageType::GameOver);
  }

  if (isClicked(cam)) {
    p.drawInv();
  }
}

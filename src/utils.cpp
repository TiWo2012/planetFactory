#include "constants.h"
#include "utlis.h"
#include <raylib.h>

void drawArrow(Vector2 pos, Direction direction, Color color) {
  // Draw arrow based on direction
  switch (direction) {
  case Direction::Up:
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    break;
  case Direction::Down:
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + Constants::OFFSET / 2,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 10,
             pos.x * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  case Direction::Left:
    DrawLine(pos.x * Constants::OFFSET,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             color);
    DrawLine(pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET - 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET - 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  case Direction::Right:
    DrawLine(pos.x * Constants::OFFSET,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             color);
    DrawLine(pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * Constants::OFFSET + 10,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2,
             pos.x * Constants::OFFSET + 5,
             pos.y * Constants::OFFSET + Constants::OFFSET / 2 + 5,
             color);
    break;
  }
}

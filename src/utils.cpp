#include "constants.h"
#include "utlis.h"
#include <raylib.h>

void drawArrow(Vector2 pos, Direction direction, Color color) {
  // Draw arrow based on direction
  switch (direction) {
  case Direction::Up:
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 - 10,
             color);
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 - 10,
             pos.x * OFFSET + OFFSET / 2 - 5,
             pos.y * OFFSET + OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 - 10,
             pos.x * OFFSET + OFFSET / 2 + 5,
             pos.y * OFFSET + OFFSET / 2 - 5,
             color);
    break;
  case Direction::Down:
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 + 10,
             color);
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 + 10,
             pos.x * OFFSET + OFFSET / 2 - 5,
             pos.y * OFFSET + OFFSET / 2 + 5,
             color);
    DrawLine(pos.x * OFFSET + OFFSET / 2,
             pos.y * OFFSET + OFFSET / 2 + 10,
             pos.x * OFFSET + OFFSET / 2 + 5,
             pos.y * OFFSET + OFFSET / 2 + 5,
             color);
    break;
  case Direction::Left:
    DrawLine(pos.x * OFFSET,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET - 10,
             pos.y * OFFSET + OFFSET / 2,
             color);
    DrawLine(pos.x * OFFSET - 10,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET - 5,
             pos.y * OFFSET + OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * OFFSET - 10,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET - 5,
             pos.y * OFFSET + OFFSET / 2 + 5,
             color);
    break;
  case Direction::Right:
    DrawLine(pos.x * OFFSET,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET + 10,
             pos.y * OFFSET + OFFSET / 2,
             color);
    DrawLine(pos.x * OFFSET + 10,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET + 5,
             pos.y * OFFSET + OFFSET / 2 - 5,
             color);
    DrawLine(pos.x * OFFSET + 10,
             pos.y * OFFSET + OFFSET / 2,
             pos.x * OFFSET + 5,
             pos.y * OFFSET + OFFSET / 2 + 5,
             color);
    break;
  }
}

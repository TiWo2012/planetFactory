#pragma once

#include <raylib.h>

class Player {
public:
  Player();

  void move(double dt);
  void draw();

  Vector2 getPosGrid(void);
  Vector2 getPos();
  Vector2 getVel();

private:
  Vector2 pos, vel;
};

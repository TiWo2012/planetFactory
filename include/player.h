#pragma once

#include <array>
#include <raylib.h>

enum class Items { None = 0, Belt, Miner };

struct Slot {
  Items item;
  int   ammount;
};

struct Inventory {
  std::array<Slot, 64> items;
};

class Player {
public:
  Player();

  void move(double dt);
  void draw();

  Vector2   getPosGrid(void);
  Vector2   getPos();
  void      setPos(Vector2 newPos);
  Vector2   getVel();
  void      setVel(Vector2 newVel);
  Inventory getInv();
  void      setInv(Inventory i);
  void      drawInv();

private:
  Vector2   pos, vel;
  Inventory inv;
};

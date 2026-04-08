#pragma once

#include "object.h"
#include "player.h"
#include "raylib.h"
#include <memory>
#include <unordered_map>

enum class BeltDirection { Left, Right, Up, Down };

class Belt : public Object {
public:
  Belt(int x, int y);
  Belt(float x, float y, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj);
  Belt(Vector2 pos, const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj);
  Belt()                       = default;
  Belt(Belt&&)                 = default;
  Belt(const Belt&)            = default;
  Belt& operator=(Belt&&)      = default;
  Belt& operator=(const Belt&) = default;
  ~Belt()                      = default;

  void setObjectsMap(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj);
  void setDirection(BeltDirection dir);
  BeltDirection getDirection() const;
  void          setContent(Items item);
  Items         getContent() const;
  void          setNext(Belt* belt);
  Belt*         getNext() const;
  bool          hasNext() const;

  void draw() override;
  void update(Player& p, Camera2D cam) override;
  void updateNextBelt(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj);

private:
  Belt* findNextBelt(const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>& obj);

private:
  Items                                                             content = Items::None;
  Belt*                                                             next    = nullptr;
  BeltDirection                                                     direction;
  const std::unordered_map<std::uint64_t, std::unique_ptr<Object>>* objectsMap = nullptr;
};

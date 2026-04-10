#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "raylib.h"

class Object;
enum class Direction;

using ObjectMap = std::unordered_map<std::uint64_t, std::unique_ptr<Object>>;

void drawArrow(Vector2 pos, Direction direction, Color color);

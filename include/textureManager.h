#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>

class TextureManager {
public:
  static Texture2D* loadTexture(const char* path);

private:
  static std::unordered_map<std::string, Texture2D> textures;
};

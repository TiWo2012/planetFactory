#include "textureManager.h"

std::unordered_map<std::string, Texture2D> TextureManager::textures;

Texture2D* TextureManager::loadTexture(const char* path) {
  // Check if texture is already loaded
  if (textures.find(path) != textures.end()) {
    return &textures[path];
  }

  // Load the texture
  Texture2D texture = LoadTexture(path);
  textures[path]    = texture;
  return &textures[path];
}

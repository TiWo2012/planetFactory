/**
 * @file textureManager.cpp
 * @brief Implementation of texture loading and caching system
 *
 * This file implements the TextureManager class, which handles loading and caching
 * of game textures. It uses a static map to store loaded textures by their file path,
 * preventing duplicate loads and improving performance.
 */

#include "textureManager.h"

std::unordered_map<std::string, Texture2D> TextureManager::textures;

/**
 * @brief Load a texture from file, caching if already loaded
 * @param path Path to the texture file
 * @return Pointer to the loaded texture
 */
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

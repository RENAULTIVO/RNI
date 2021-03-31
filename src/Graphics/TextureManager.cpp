#include "TextureManager.hpp"
#include "../Core/Core.hpp"

TextureManager *TextureManager::instance = nullptr;

TextureManager *TextureManager::getInstance() {

  if (instance == nullptr) {
    instance = new TextureManager();
  }

  return instance;

}

bool TextureManager::load(
  std::string textureID,
  std::string fileName
) {

  SDL_Surface *surface = IMG_Load(fileName.c_str());

  if (surface == nullptr) {
    SDL_Log("Failed to load file \"%s\": %s", fileName.c_str(), SDL_GetError());
    return false;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(
    Core::getInstance()->getRenderer(),
    surface    
  );

  if (texture == nullptr) {
    SDL_Log("Failed to create texture \"%s\": %s", fileName.c_str(), SDL_GetError());
    return false;
  }

  textureMap[textureID] = texture;
  return true;

}

void TextureManager::draw(
  std::string textureID,
  int x, int y,
  int width, int height,
  SDL_RendererFlip flip
) {

  SDL_Rect sourceRect;
  SDL_Rect destinationRect;

  sourceRect.x = 0;
  sourceRect.y = 0;
  sourceRect.w = width;
  sourceRect.h = height;

  destinationRect.x = x;
  destinationRect.y = y;
  destinationRect.w = width;
  destinationRect.h = height;

  SDL_RenderCopyEx(
    Core::getInstance()->getRenderer(),
    textureMap[textureID],
    &sourceRect, &destinationRect,
    0, nullptr,
    SDL_FLIP_NONE
  );

}

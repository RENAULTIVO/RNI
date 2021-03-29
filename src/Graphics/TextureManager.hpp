#ifndef TEXTUREHANDLER_HPP
#define TEXTUREHANDLER_HPP
#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {

  private:
    std::map<std::string, SDL_Texture*> textureMap;
    TextureManager() {}
    static TextureManager *instance;

  public:
    bool load(std::string textureID, std::string fileName);
    void draw(
      std::string textureID,
      int x, int y,
      int width, int height,
      SDL_RendererFlip flip = SDL_FLIP_NONE
    );
    void clean();
    void drawFrame();
    static TextureManager *getInstance();

};

#endif

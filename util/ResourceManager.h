#pragma once

#include <string>
#include <map>
#include <SDL.h>

class ResourceManager {
public:
    SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
        if (textures.count(path) == 0) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(path.c_str()));
            textures[path] = texture;
        }
        return textures[path];
    }

    void unloadTexture(const std::string& path) {
        if (textures.count(path) > 0) {
            SDL_DestroyTexture(textures[path]);
            textures.erase(path);
        }
    }

private:
    std::map<std::string, SDL_Texture*> textures;
};

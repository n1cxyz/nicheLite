#pragma once

#include "SDL.h"

class Texture;

class Tile {
    private:
        SDL_Rect box_;
        int type_;

        Texture* tileTexture;
        SDL_Rect* gTileClips;

    public:
        Tile(int x, int y, int tileType, Texture* tileTexture, SDL_Rect* gTileClips);
        void render(SDL_Rect& camera);

        int getType();
        SDL_Rect getBox();
};
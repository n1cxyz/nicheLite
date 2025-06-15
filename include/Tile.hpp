#pragma once

#include "SDL.h"

class Tile {
    private:
        SDL_Rect box_;
        int type_;

        SDL_Rect* clip_;

    public:
        Tile(int x, int y, int type, SDL_Rect* clip);
        void render(SDL_Renderer* renderer, SDL_Rect& camera);

        int getType();
        SDL_Rect getBox();
};
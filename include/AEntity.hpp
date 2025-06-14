#pragma once

#include "SDL.h"

class TextureManager;

class AEntity {
    protected:
        // X and Y offsets
        float posX_;
        float posY_;

        // dimensions
        const int width_;
        const int height_;

        // collision box
        SDL_Rect box_;

    public:
        AEntity();
        //virtual void update() = 0;
        virtual ~AEntity();

        //void render();

};
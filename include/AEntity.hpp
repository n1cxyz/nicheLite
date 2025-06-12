#pragma once

#include "All.hpp"
class Texture;

class AEntity {
    protected:
        // X and Y offsets
        float posX_;
        float posY_;

        // dimensions
        const int width_;
        const int height_;

        // collision box
        SDL_Rect box;
    public:
        AEntity();
        virtual ~AEntity();

        void render();

        Texture* texture_ = nullptr;
};
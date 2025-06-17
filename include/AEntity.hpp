#pragma once

#include "SDL.h"
#include "Enums.hpp"

//class TextureManager;

class AEntity {
    protected:
        Type type_;

        // X and Y offsets
        float posX_;
        float posY_;

        // dimensions
        const int width_;
        const int height_;

        // collision box
        SDL_Rect box_;

    public:
        AEntity(Type type);
        //virtual void update() = 0;
        virtual ~AEntity();

        //void render();
        Type getType() const { return type_; }

};
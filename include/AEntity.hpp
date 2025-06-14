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

        TextureManager* texture_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;

    public:
        AEntity();
        //virtual void update() = 0;
        virtual ~AEntity();

        void render();

        void setTexture(TextureManager* txt);
        TextureManager* getTexture() const;
        void setRenderer(SDL_Renderer* renderer_);

        SDL_Rect spriteClips[16];
};
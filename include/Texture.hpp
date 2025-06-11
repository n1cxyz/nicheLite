#pragma once

#include "All.hpp"

class Texture {
    private:
        SDL_Texture* texture_;

        int width_;
        int height_;
    public:
        Texture();
        ~Texture();

        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y, SDL_Rect* clip = NULL);
    
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);

        int getWidth();
        int getHeight();
};
#pragma once

#include "SDL.h"
#include "iostream"
#include "unordered_map"

class TextureManager {
    private:
        TextureManager() {}

        std::unordered_map<std::string, SDL_Texture*> textures;
/*         SDL_Texture* texture_;
        SDL_Renderer* renderer_ = nullptr;

        int width_;
        int height_; */
    public:
        static TextureManager& getInstance() {
            static TextureManager instance;
            return instance;
        }

        SDL_Texture* loadTexture(const std::string& filePath);
        SDL_Texture* getTexture(const std::string& key);
/*         bool loadFromFile(std::string path);
        void free();
        void render(int x, int y, SDL_Rect* clip = nullptr);
    
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);

        SDL_Texture* getTexture() const;
        int getWidth();
        int getHeight();
        void setRenderer(SDL_Renderer* renderer_) {this->renderer_ = renderer_;} */
};
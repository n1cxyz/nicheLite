#pragma once

#include "SDL.h"
#include "iostream"
#include "unordered_map"
#include "ACharacter.hpp"
#include "EnumPairHash.hpp"


class TextureManager {
    private:
        TextureManager() {}

        std::unordered_map<std::pair<State, Direction>, SDL_Texture*, EnumPairHash> playerTextures_;
        std::unordered_map<std::string, SDL_Texture*> tileTextures_;
    
        SDL_Renderer* renderer_;
/*         SDL_Texture* texture_;
        SDL_Renderer* renderer_ = nullptr;

        int width_;
        int height_; */
    public:
        static TextureManager& getInstance() {
            static TextureManager instance;
            return instance;
        }

        SDL_Texture* initTexture(const std::string& filePath);
        bool loadTexture(const std::pair<State,Direction>& key, const std::string& filePath);
        bool loadTexture(const std::string& key, const std::string& filePath);

        SDL_Texture* getTexture(const std::pair<State,Direction>& key);
        SDL_Texture* getTexture(const std::string& key);
        void setRenderer(SDL_Renderer* renderer) { this->renderer_ = renderer; }
        //void render(int x, int y, SDL_Rect* clip = nullptr);
        
        //void free(SDL_Texture* txt);
        //void clear();
        /*
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha);

        SDL_Texture* getTexture() const;
        int getWidth();
        int getHeight();
        void setRenderer(SDL_Renderer* renderer_) {this->renderer_ = renderer_;} */
};
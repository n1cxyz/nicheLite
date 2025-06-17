#pragma once

#include "SDL.h"
#include "iostream"
#include "unordered_map"
#include "ACharacter.hpp"
#include "Enums.hpp"
#include <tuple>


class TextureManager {
    private:
        TextureManager() {}

        std::unordered_map<std::tuple<State, Direction, Type>, SDL_Texture*, TupleHash> entityTextures_;
        std::unordered_map<std::string, SDL_Texture*> tileTextures_;
    
        SDL_Renderer* renderer_;

    public:
        static TextureManager& getInstance() {
            static TextureManager instance;
            return instance;
        }

        SDL_Texture* initTexture(const std::string& filePath);
       
        bool loadTexture(const std::tuple<State,Direction,Type>& key, const std::string& filePath);
        bool loadTexture(const std::string& key, const std::string& filePath);

        SDL_Texture* getTexture(const std::tuple<State,Direction,Type>& key);
        SDL_Texture* getTexture(const std::string& key);
        
        void setRenderer(SDL_Renderer* renderer) { this->renderer_ = renderer; }
        
/*         void free(SDL_Texture* txt);
        void clear();

        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setAlpha(Uint8 alpha); */
};
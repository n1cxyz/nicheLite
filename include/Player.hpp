#pragma once

#include "SDL.h"
#include "ACharacter.hpp"

class Player : public ACharacter {
    private:
    public:
        Player() : ACharacter(Type::Player) {}
        ~Player() {}
    
        //void render(SDL_Rect& camera);
        void handleEvent(SDL_Event& e);
        void setCamera(SDL_Rect& camera);
};
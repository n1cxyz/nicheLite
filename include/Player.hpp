#pragma once

#include "All.hpp"
class Character;

class Player : public ACharacter {
    private:
    public:
        void render(SDL_Rect& camera);
        void handleEvent(SDL_Event& e);
        void setCamera(SDL_Rect& camera);
};
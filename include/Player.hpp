#pragma once

#include "All.hpp"
class Character;

class Player : public Character {
    private:
    public:
        void handleEvent(SDL_Event& e);
        void move();
};
#pragma once

#include "All.hpp"
class Character;

class Player : public ACharacter {
    private:
    public:
        void handleEvent(SDL_Event& e);
};
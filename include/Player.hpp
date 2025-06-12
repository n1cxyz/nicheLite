#pragma once

#include "All.hpp"
class Character;

class Player : public Character {
    private:
    public:
        void handleEvent(SDL_Event& e);
        // moves and cheks for collision
        void move(Tile *tiles[]);
};
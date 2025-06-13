#pragma once

#include "All.hpp"
class AEntity;

class ACharacter : public AEntity {
    protected:
        // velocity
        int velX_;
        int velY_;
        // Maximum axis velocity
        const int maxVel_;
    public:
        ACharacter();
        virtual ~ACharacter();

        // moves and cheks for collision
        void move(Tile *tiles[]);

};
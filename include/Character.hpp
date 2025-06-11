#pragma once

#include "All.hpp"

class Character : public AEntity {
    protected:
        // velocity
        int velX_;
        int velY_;
        // Maximum axis velocity
        const int maxVel_;
    public:
        Character();
        ~Character();

};
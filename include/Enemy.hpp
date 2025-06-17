#pragma once

#include "ACharacter.hpp"

class Enemy : public ACharacter {
    private:
    public:
        Enemy() : ACharacter(Type::Enemy) {}
        ~Enemy() {}

    void handleEvent(SDL_Event& e){ (void)e; }

};
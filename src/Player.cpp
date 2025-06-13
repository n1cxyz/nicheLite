#include "All.hpp"

void Player::handleEvent(SDL_Event& e) {
    // key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY_ -= maxVel_; break;
            case SDLK_DOWN: velY_ += maxVel_; break;
            case SDLK_LEFT: velX_ -= maxVel_; break;
            case SDLK_RIGHT: velX_ += maxVel_; break;
        }
    } 
    // key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY_ += maxVel_; break;
            case SDLK_DOWN: velY_ -= maxVel_; break;
            case SDLK_LEFT: velX_ += maxVel_; break;
            case SDLK_RIGHT: velX_ -= maxVel_; break;
        }
    }
}

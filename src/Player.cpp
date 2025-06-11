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

void Player::move() {
    // Move left or right
    posX_ += velX_;

    // If moved too far
    if ((posX_ < 0) || (posX_ + width_ > SCREEN_WIDTH)) {
        // move back
        posX_ -= velX_;
    }

    // Move up or down
    posY_ += velY_;

    // If moved too far
    if ((posY_ < 0) || (posY_ + height_ > SCREEN_HEIGHT)) {
        // move back
        posY_ -= velY_;
    }
}
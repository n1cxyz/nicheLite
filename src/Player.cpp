#include "Player.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

//TextureManager gPlayerTexture;

void Player::handleEvent(SDL_Event& e) {
    // key was pressed
/*     if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY_ -= maxVel_; setDirection(Direction::Up); setState(State::Run); break;
            case SDLK_DOWN: velY_ += maxVel_; setDirection(Direction::Down); setState(State::Run); break;
            case SDLK_LEFT: velX_ -= maxVel_; setDirection(Direction::Left); setState(State::Run); break;
            case SDLK_RIGHT: velX_ += maxVel_; setDirection(Direction::Right); setState(State::Run); break;
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
    } */
}

/* void Player::setCamera(SDL_Rect& camera) {
    // Center the camera over player
    camera.x = (box_.x + width_ / 2) - SCREEN_WIDTH / 2;
    camera.y = (box_.y + height_ / 2) - SCREEN_HEIGHT / 2;

    // Keep camera in bounds
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
} */

/* void Player::render(SDL_Rect& camera) {
    texture_->render(box_.x - camera.x, box_.y - camera.y);
    //gPlayerTexture.render(3, 1);
} */
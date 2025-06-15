#include "ACharacter.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(10) {

    animations[State::Idle] = Animation{
        { {0, 0, 64, 64} },
        200 // ms per frame
    };
};
ACharacter::~ACharacter() {};

void ACharacter::render(SDL_Renderer* renderer) {
    const Animation& anim = animations[currentState];
    const SDL_Rect& srcRect = anim.frames[currentFrameIndex];
    SDL_Rect dest = {
        static_cast<int>(posX_), 
        static_cast<int>(posY_),
        srcRect.w * 2, srcRect.h * 2
    };
    TextureManager& tm = TextureManager::getInstance();

    SDL_RenderCopy(renderer, tm.getTexture("PLAYER_IDLE"), &srcRect, &dest);
}

void ACharacter::update(Uint32 currentTime) {
    const Animation anim = animations[currentState];

    if (currentTime - lastFrameTime >= anim.frameDuration) {
        currentFrameIndex = (currentFrameIndex + 1) % anim.frames.size();
        lastFrameTime = currentTime;
    }
}

void ACharacter::setState(State newState) {
    if (currentState != newState) {
        currentState = newState;
        currentFrameIndex = 0;
        lastFrameTime = SDL_GetTicks();
    }
}

void ACharacter::move(Tile *tiles[]) {
/*     // Move left or right
    box_.x += velX_;

    // If moved too far or touched Wall
    if ((box_.x < 0) || (box_.x + width_ > SCREEN_WIDTH) || touchesWall(box_, tiles)) {
        box_.x -= velX_;
    }
    // Move up or down
    box_.y += velY_;

    if ((box_.y < 0) || (box_.y + height_ > SCREEN_HEIGHT) || touchesWall(box_, tiles)) {
        box_.y -= velY_;
    } */


    // Move left or right
    posX_ += velX_;

    // If moved too far or touched Wall
    if ((posX_ < 0) || (posX_ + width_ > SCREEN_WIDTH)) {
        posX_ -= velX_;
    }
    // Move up or down
    posY_ += velY_;

    if ((posY_ < 0) || (posY_ + height_ > SCREEN_HEIGHT)) {
        posY_ -= velY_;
    }
}

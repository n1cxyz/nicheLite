#include "ACharacter.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(10) {
    box_.x = 0;
    box_.y = 0;
    box_.w = 64;
    box_.h = 64;

    animations[{State::Idle, Direction::Down}] = Animation{
        { 
            {48, 48, 64, 64},
            {112, 48, 64, 64},
            {176, 48, 64, 64}
        },
        100 // ms per frame
    };
};
ACharacter::~ACharacter() {};

void ACharacter::render(SDL_Renderer* renderer) {
    const Animation& anim = animations[{currentState, currentDirection}];
    const SDL_Rect& srcRect = anim.frames[currentFrameIndex];

    SDL_Rect dest = {box_.x, box_.y, srcRect.w * 2, srcRect.h * 2};
    TextureManager& tm = TextureManager::getInstance();

    SDL_RenderCopy(renderer, tm.getTexture({currentState, currentDirection}), &srcRect, &dest);
}

void ACharacter::update(Uint32 currentTime) {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);

    velX_ = 0;
    velY_ = 0;

    if (keystate[SDL_SCANCODE_UP]) {
        velY_ = -maxVel_;
        setDirection(Direction::Up);
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
        velY_ = maxVel_;
        setDirection(Direction::Down);
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
        velX_ = -maxVel_;
        setDirection(Direction::Left);
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        velX_ = maxVel_;
        setDirection(Direction::Right);
    }

    if (velX_ != 0 || velY_ != 0) {
        setState(State::Run);
    } else if (currentState != State::Attack) {
        setState(State::Idle);
    }

    const Animation& anim = animations[{currentState, currentDirection}];

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

void ACharacter::setDirection(Direction newDirection) {
    if (currentDirection != newDirection) {
        currentDirection = newDirection;
        currentFrameIndex = 0;
        lastFrameTime = SDL_GetTicks();
    }
}


void ACharacter::move(Tile *tiles[]) {
    // Move left or right
    box_.x += velX_;

    // If moved too far or touched Wall
    if ((box_.x < 0) || (box_.x + width_ > SCREEN_WIDTH) || touchesWall(box_, tiles)) {
        box_.x -= velX_;
    }
    // Move up or down
    box_.y += velY_;

    if ((box_.y < 0) || (box_.y + height_ > SCREEN_HEIGHT) || touchesWall(box_, tiles)) {
        box_.y -= velY_;
    }

/*     // Move left or right
    posX_ += velX_;

    // If moved too far or touched Wall
    if ((posX_ < 0) || (posX_ + width_ > SCREEN_WIDTH)) {
        posX_ -= velX_;
    }
    // Move up or down
    posY_ += velY_;

    if ((posY_ < 0) || (posY_ + height_ > SCREEN_HEIGHT)) {
        posY_ -= velY_;
    } */
}

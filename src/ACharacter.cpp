#include "ACharacter.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(4) {
    box_.x = 0;
    box_.y = 0;
    box_.w = 32;
    box_.h = 32;

    std::vector<SDL_Rect>frames = {
        {48, 48, 32, 32},
        {176, 48, 32, 32},
        {304, 48, 32, 32},
        {432, 48, 32, 32},
        {560, 48, 32, 32}
    };

    std::vector<State> states = {State::Idle, State::Run};
    std::vector<Direction> directions = {Direction::Down, Direction::Left, Direction::Right, Direction::Up};


    for (const auto& state : states) {
        for (const auto& dir : directions) {
            if (state == State::Idle) {
                animations[{state, dir}] = Animation{ frames, 200 };  // Idle/Down with 200ms per frame
            } else {
                animations[{state, dir}] = Animation{ frames, 100 };    // Others with 100ms per frame
            }
        }
    }    
};
ACharacter::~ACharacter() {};

void ACharacter::render(SDL_Renderer* renderer) {
    const auto key = std::make_pair(currentState, currentDirection); //?
    if (animations.find(key) == animations.end()) {
        SDL_Log("Missing animation for state=%d, dir=%d", (int)currentState, (int)currentDirection);
        return;
    }
    const Animation& anim = animations[{currentState, currentDirection}];
    if (anim.frames.empty()) {
        SDL_Log("Frames are empty!");
        return;
    }
    if (currentFrameIndex >= anim.frames.size()) {
        SDL_Log("Invalid frame index: %d >= %zu", currentFrameIndex, anim.frames.size());
        currentFrameIndex = 0;
        return;
    }
    const SDL_Rect& srcRect = anim.frames[currentFrameIndex];

    SDL_Rect dest = {box_.x, box_.y, srcRect.w * 3, srcRect.h * 3};
    TextureManager& tm = TextureManager::getInstance();

    //SDL_Log("Render: state = %d, dir = %d", static_cast<int>(currentState), static_cast<int>(currentDirection));
    SDL_Texture* tex = tm.getTexture(key); //?
    if (!tex) SDL_Log("❌ Texture not found for this state/direction");

    if (!tex) {
        SDL_Log("Texture is null! State: %d, Dir: %d", (int)currentState, (int)currentDirection);
        return;
    }

    SDL_Log("🔎 Rendering frame idx=%d for state=%d dir=%d", currentFrameIndex, (int)currentState, (int)currentDirection);

    //const SDL_Rect& srcRectt = anim.frames[0];
    SDL_RenderCopy(renderer, tex, &srcRect, &dest);
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

    auto it = animations.find({currentState, currentDirection});
    if (it == animations.end()) {
        SDL_Log("❌ Missing animation for state=%d, dir=%d", static_cast<int>(currentState), static_cast<int>(currentDirection));
        return;
    }
    const Animation& anim = it->second;

    if (currentTime - lastFrameTime >= anim.frameDuration && !anim.frames.empty()) {
        currentFrameIndex = (currentFrameIndex + 1) % anim.frames.size();
        lastFrameTime = currentTime;
    }

    //SDL_Log("Update: velocity (%d, %d), state = %d, dir = %d", velX_, velY_, static_cast<int>(currentState), static_cast<int>(currentDirection));
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

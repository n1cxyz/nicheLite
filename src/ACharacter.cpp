#include "ACharacter.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"
#include "Utils.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(4) {

    std::vector<SDL_Rect>frames = {
        {0, 0, 128, 128},
        {128, 0, 128, 128},
        {256, 0, 128, 128},
        {384, 0, 128, 128},
        {512, 0, 128, 128}
    };

    std::vector<SDL_Rect>aFrames = {
        {0, 0, 128, 128},
        {128, 0, 128, 128},
        {256, 0, 128, 128},
        {384, 0, 128, 128},
        {512, 0, 128, 128},
        {640, 0, 128, 128},
        {768, 0, 128, 128},
        {896, 0, 128, 128},
    };

    std::vector<State> states = {State::Idle, State::Run, State::Attack};
    std::vector<Direction> directions = {Direction::Down, Direction::Left, Direction::Right, Direction::Up};

    for (const auto& state : states) {
        for (const auto& dir : directions) {
            if (state == State::Attack) {
                animations[{state, dir}] = Animation{ aFrames, 100 };
            } else if (state == State::Idle) {
                animations[{state, dir}] = Animation{ frames, 200 };
            } else {
                animations[{state, dir}] = Animation{ frames, 100 };
            }
        }
    } 

};
ACharacter::~ACharacter() {};

void ACharacter::render(SDL_Renderer* renderer) {
    std::pair<State, Direction> key = {currentState, currentDirection};

    // Get animation
    auto animIt = animations.find(key);
    if (animIt == animations.end() || animIt->second.frames.empty()) {
        SDL_Log("Missing or empty animation for state=%d, dir=%d", (int)currentState, (int)currentDirection);
        return;
    }

    const Animation& anim = animIt->second;

    // Validate frame index
    if (currentFrameIndex >= anim.frames.size()) {
        SDL_Log("Frame index out of bounds: %zu (size=%zu). Resetting.", currentFrameIndex, anim.frames.size());
        currentFrameIndex = 0;
    }

    const SDL_Rect& srcRect = anim.frames[currentFrameIndex];
    SDL_Rect destRect = {box_.x, box_.y, srcRect.w * SCALE, srcRect.h * SCALE};

    // Get texture
    SDL_Texture* tex = TextureManager::getInstance().getTexture(key);
    if (!tex) {
        SDL_Log("Texture not found for state=%d, dir=%d", (int)currentState, (int)currentDirection);
        return;
    }

    // draw hitbox
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderDrawRect(renderer, &box_);

    //printf("hello\n");
    // Render
    SDL_RenderCopy(renderer, tex, &srcRect, &destRect);
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

    if (keystate[SDL_SCANCODE_Q]) {
        setState(State::Attack);
    }

    auto it = animations.find({currentState, currentDirection});
    if (it == animations.end()) {
        SDL_Log("Missing animation for state=%d, dir=%d", static_cast<int>(currentState), static_cast<int>(currentDirection));
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


void ACharacter::move(std::vector<Tile*> tiles) {
    // Move left or right
    box_.x += velX_;

    // If moved too far or touched Wall
    if ((box_.x < 0) || (box_.x + width_ > SCREEN_WIDTH) || Utils::touchesWall(box_, tiles)) {
        box_.x -= velX_;
    }
    // Move up or down
    box_.y += velY_;

    if ((box_.y < 0) || (box_.y + height_ > SCREEN_HEIGHT) || Utils::touchesWall(box_, tiles)) {
        box_.y -= velY_;
    }
}

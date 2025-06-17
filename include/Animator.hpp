#pragma once

#include "SDL.h"
#include <vector>

struct Animation {
    std::vector<SDL_Rect> frames;
    Uint32 frameDuration;
};


class Animator {
private:
    Animation* current;
    size_t currentFrameIndex = 0;
    Uint32 lastFrameTime = 0;

public:
    Animator();
    ~Animator();

    void update(int deltaTime);
    void setAnimation(Animation* anim);
    SDL_Rect* getCurrentFrame() const;
};
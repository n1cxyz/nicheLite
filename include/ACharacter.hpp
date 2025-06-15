#pragma once

#include "AEntity.hpp"
#include <vector>
#include <unordered_map>

class Tile;

enum class State { Idle, Run, Attack };

struct Animation {
    std::vector<SDL_Rect> frames;
    int frameDuration;
};

class ACharacter : public AEntity {
    protected:
        // map of animations
        std::unordered_map<State, Animation> animations;

        State currentState = State::Idle;
        int currentFrameIndex = 0;
        Uint32 lastFrameTime = 0;
    
        // velocity
        int velX_;
        int velY_;

        // Maximum axis velocity
        const int maxVel_;

    public:
        ACharacter();
        virtual ~ACharacter();

        // moves and cheks for collision
        //void move(Tile* tiles[]);

        void update(Uint32 currentTime);
        void render(SDL_Renderer* renderer, SDL_Texture* texture);
        void setState(State newState);

        State getState() const { return currentState; }
};
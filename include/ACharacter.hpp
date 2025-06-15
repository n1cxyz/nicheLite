#pragma once

#include "AEntity.hpp"
#include <vector>
#include <unordered_map>
#include "EnumPairHash.hpp"

class Tile;

struct Animation {
    std::vector<SDL_Rect> frames;
    int frameDuration;
};

class ACharacter : public AEntity {
    protected:

        // map of animations
        std::unordered_map<std::pair<State, Direction>, Animation, EnumPairHash> animations;

        State currentState = State::Idle;
        Direction currentDirection = Direction::Down;
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
        void move(Tile* tiles[]);

        void update(Uint32 currentTime);
        void render(SDL_Renderer* renderer);

        void setState(State newState);
        void setDirection(Direction newDirection);

        State getState() const { return currentState; }
};
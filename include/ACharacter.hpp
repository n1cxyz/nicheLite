#pragma once

#include "AEntity.hpp"
#include <vector>
#include <unordered_map>

class Tile;

enum class State { Idle, Run, Attack };
enum class Direction { Left, Right, Up, Down };

struct Animation {
    std::vector<SDL_Rect> frames;
    int frameDuration;
};

struct EnumPairHash {
    std::size_t operator()(const std::pair<State, Direction>& p) const {
        return std::hash<int>()(static_cast<int>(p.first)) ^ (std::hash<int>()(static_cast<int>(p.second)) << 1);
    }
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
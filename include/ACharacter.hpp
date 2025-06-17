#pragma once

#include "AEntity.hpp"
#include <vector>
#include <unordered_map>
//#include "EnumPairHash.hpp"
//#include "Enums.hpp"

class Tile;

struct Animation {
    std::vector<SDL_Rect> frames;
    Uint32 frameDuration;
};

class ACharacter : public AEntity {
    protected:

        // map of animations
        std::unordered_map<std::tuple<State,Direction,Type>, Animation, TupleHash> animations;

        State currentState_ = State::Idle;
        Direction currentDirection_ = Direction::Down;
        size_t currentFrameIndex = 0;
        Uint32 lastFrameTime = 0;
    
        // velocity
        int velX_;
        int velY_;

        // Maximum axis velocity
        int maxVel_;

    public:
        ACharacter(Type type);
        virtual ~ACharacter();

        // moves and cheks for collision
        void move(std::vector<Tile*> tiles);

        void update(Uint32 currentTime);
        void render(SDL_Renderer* renderer);

        void setState(State newState);
        void setDirection(Direction newDirection);

        State getState() const { return currentState_; }
};
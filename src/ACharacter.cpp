#include "All.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(10) {};
ACharacter::~ACharacter() {};

void ACharacter::move(Tile *tiles[]) {
    // Move left or right
    posX_ += velX_;

    // If moved too far or touched Wall
    if ((posX_ < 0) || (posX_ + width_ > SCREEN_WIDTH) || touchesWall(box_, tiles)) {
        posX_ -= velX_;
    }

    // Move up or down
    posY_ += velY_;

    if ((posY_ < 0) || (posY_ + height_ > SCREEN_HEIGHT) || touchesWall(box_, tiles)) {
        posY_ -= velY_;
    }
}
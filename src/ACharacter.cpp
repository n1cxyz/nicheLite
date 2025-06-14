#include "ACharacter.hpp"
#include "Constants.hpp"

ACharacter::ACharacter() : velX_(0), velY_(0), maxVel_(10) {};
ACharacter::~ACharacter() {};

void render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect& desRect) {
    SDL_RenderCopy(renderer, texture, )
}
/* void ACharacter::move(Tile *tiles[]) {

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

} */

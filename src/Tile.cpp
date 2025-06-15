#include "Tile.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"

Tile::Tile(int x, int y, int type, SDL_Rect* clip) {
    // get offsets
    box_.x = x;
    box_.y = y;

    // set collision box
    box_.w = TILE_WIDTH;
    box_.h = TILE_HEIGHT;

    type_ = type;
    this->clip_ = clip;
}

void Tile::render(SDL_Renderer* renderer, SDL_Rect& camera) {
    // if tile is on  screen
    if (checkCollision(camera, box_)) {
        TextureManager& tm = TextureManager::getInstance();
        SDL_Rect srcRect = {clip_ ? clip_->x : 0, clip_ ? clip_->y : 0, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect destRect = {box_.x - camera.x, box_.y - camera.y, TILE_WIDTH, TILE_HEIGHT};
        SDL_RenderCopy(renderer, tm.getTexture("TILES"), &srcRect, &destRect);
    }
}

int Tile::getType() {
    return type_;
}

SDL_Rect Tile::getBox() {
    return box_;
}
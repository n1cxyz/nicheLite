#include "Tile.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "TextureManager.hpp"

Tile::Tile(int x, int y, int type, SDL_Rect* clip) {
    // get offsets
    box_.x = x;
    box_.y = y;

    // set collision box
    box_.w = TILE_WIDTH;
    box_.h = TILE_HEIGHT;

    this->type_ = type;
    this->clip_ = clip;
}

void Tile::render(SDL_Renderer* renderer, SDL_Rect& camera) {
    // if tile is on  screen
    if (Utils::checkCollision(camera, box_)) {
        TextureManager& tm = TextureManager::getInstance();
        SDL_Texture* tex = tm.getTexture("TILES");
        SDL_Rect srcRect = {clip_ ? clip_->x : 0, clip_ ? clip_->y : 0, TILE_WIDTH, TILE_HEIGHT};
        SDL_Rect destRect = {box_.x - camera.x, box_.y - camera.y, TILE_WIDTH * SCALE, TILE_HEIGHT * SCALE};
        //printf("x: %d\n", box_.x - camera.x);
        //printf("y: %d\n", box_.y - camera.y);
        SDL_SetTextureColorMod(tex, 50, 50, 50);
        SDL_RenderCopy(renderer, tex, &srcRect, &destRect);
    }
    
}

const int& Tile::getType() const {
    return type_;
}

const SDL_Rect& Tile::getBox() const{
    return box_;
}
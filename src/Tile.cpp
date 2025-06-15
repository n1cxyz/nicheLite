#include "Tile.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"
/* TextureManager gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ]; */

Tile::Tile(int x, int y, int tileType, SDL_Rect* gTileClips) {
    // get offsets
    box_.x = x;
    box_.y = y;

    // set collision box
    box_.w = TILE_WIDTH;
    box_.h = TILE_HEIGHT;

    type_ = tileType;

    this->gTileClips = gTileClips;
}

void Tile::render(SDL_Renderer* renderer, SDL_Rect& camera) {
    // if tile is on  screen
    if (checkCollision(camera, box_)) {
        TextureManager& tm = TextureManager::getInstance();
        SDL_Rect srcRect = {gTileClips ? gTileClips->x : 0, gTileClips ? gTileClips->y : 0, TILE_WIDTH, TILE_HEIGHT};
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
#include "Tile.hpp"
#include "Constants.hpp"
#include "TextureManager.hpp"
/* TextureManager gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ]; */

Tile::Tile(int x, int y, int tileType, TextureManager* tileTexture, SDL_Rect* gTileClips) {
    // get offsets
    box_.x = x;
    box_.y = y;

    // set collision box
    box_.w = TILE_WIDTH;
    box_.h = TILE_HEIGHT;

    type_ = tileType;

    this->tileTexture = tileTexture;
    this->gTileClips = gTileClips;
}

void Tile::render(SDL_Rect& camera) {
    // if tile is on  screen
    if (checkCollision(camera, box_)) {
        tileTexture->render(box_.x - camera.x, box_.y - camera.y, &gTileClips[type_]);
    }
}

int Tile::getType() {
    return type_;
}

SDL_Rect Tile::getBox() {
    return box_;
}
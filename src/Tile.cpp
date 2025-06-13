#include "All.hpp"
Texture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

Tile::Tile(int x, int y, int tileType) {
    // get offsets
    box_.x = x;
    box_.y = y;

    // set collision box
    box_.w = TILE_WIDTH;
    box_.h = TILE_HEIGHT;

    type_ = tileType;
}

void Tile::render(SDL_Rect& camera) {
    // if tile is on  screen
    if (checkCollision(camera, box_)) {
        gTileTexture.render(box_.x - camera.x, box_.y - camera.y, &gTileClips[type_]);
    }
}

int Tile::getType() {
    return type_;
}

SDL_Rect Tile::getBox() {
    return box_;
}
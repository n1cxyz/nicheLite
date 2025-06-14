#pragma once

#include "SDL.h"
#include "Constants.hpp"
#include "Texture.hpp"

class Tile;


class Game {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    Texture tileTexture;
    SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

public:
    Game();
    ~Game();

    bool init();
    void run();
    bool loadMedia(Tile* tiles[], Texture* playerTexture);
    void shutdown(Tile* tiles[]);

    //bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool setTiles(Tile* tiles[]);
    //bool touchesWall(SDL_Rect box, Tile* tiles[]);

    SDL_Renderer* getRenderer() const;
};
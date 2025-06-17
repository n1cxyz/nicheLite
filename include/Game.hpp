#pragma once

#include "SDL.h"
//#include "Constants.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"

class Game {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    Map map;

    //SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
    //Tile* tileSet[TOTAL_TILES];

public:
    Game();
    ~Game();

    bool init();
    void run();
    bool loadMedia(TextureManager& tm);
    // void shutdown(Tile* tiles[]);
    
    void loadLevel(const std::string& levelFile);
    void renderLevel(SDL_Renderer* renderer, SDL_Rect& camera);

    //bool checkCollision(SDL_Rect a, SDL_Rect b);
    //bool setTiles(Tile* tiles[]);
    //bool touchesWall(SDL_Rect box, Tile* tiles[]);

    //SDL_Renderer* getRenderer() const;
};
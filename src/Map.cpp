#include "Map.hpp"
#include "fstream"
#include "Constants.hpp"

Map::Map() {
    //tiles.resize(TOTAL_TILES);
    clips.resize(TOTAL_TILE_SPRITES);
}

void Map::loadFromFile(const std::string& levelFile) {
    clips[0] = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    clips[1] = {0, 32, TILE_WIDTH, TILE_HEIGHT};

    int x = 0, y = 0;
    
    std::ifstream map(levelFile);
    if (map.fail()) {
        printf("Failed to open map %s\n", levelFile.c_str());
        return;
    }
    for (int i = 0; i < TOTAL_TILES; ++i) {

        int tileType = -1;

        // read tile from map file
        map >> tileType;
        if (map.fail()) {
            printf("Error loading map: Unexpected end of file!\n");
            return;
        }
        // if the number is a valid tile number
        if (tileType == 0 || tileType == 1) {
            tiles.push_back(new Tile(x, y, tileType, &clips[tileType]));
            //printf("Tile %d: (%d, %d) type: %d\n", i, x, y, tileType);
        } else {
           // printf("Invalid tile type %d at tile %d (%d, %d)\n", tileType, i, x, y);
           // printf("Error loading map: Invalid tile type at %d!\n", i);
            return;
        }

        // move to next tile spot
        x += TILE_WIDTH;

        if (x >= LEVEL_WIDTH * TILE_WIDTH) {
            x = 0;
            y += TILE_HEIGHT;
        }
    }

    printf("size: %zu\n", tiles.size());
    map.close();
    /* for (int i = 0; i < TOTAL_TILE_SPRITES; ++i) {
        clips[i] = {}
    } */
}

void Map::renderLevel(SDL_Renderer* renderer, SDL_Rect& camera) {
    for (int i = 0; i < TOTAL_TILES; ++i) {
        tiles[i]->render(renderer, camera);
    }
    //printf("Camera: x=%d y=%d w=%d h=%d\n", camera.x, camera.y, camera.w, camera.h);
}


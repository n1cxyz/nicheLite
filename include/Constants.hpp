#pragma once

#include "Tile.hpp"
#include "SDL.h"

const int FPS = 60;

const int SCALE = 3;

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

//The dimensions of the level
const int LEVEL_WIDTH = 64;
const int LEVEL_HEIGHT = 40;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int TOTAL_TILES = LEVEL_WIDTH * LEVEL_HEIGHT;
const int TOTAL_TILE_SPRITES = 2;

const int TILE_GRASS = 0;
/* //The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11; */

// Player walking animation
const int WALKING_ANIMATION_FRAMES = 16;

#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#include <iostream>
#include <fstream>

#include "AEntity.hpp"
#include "Game.hpp"
#include "Map.hpp"
#include "Texture.hpp"
#include "Tile.hpp"
#include "ACharacter.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include "Timer.hpp"


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_FPS 60;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;
extern SDL_Texture* gTexture;

bool init();
bool loadTexture();
void close();
#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#include <iostream>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Surface* gScreenSurface;
extern SDL_Texture* gTexture;

bool init();
bool loadMedia();
void close();
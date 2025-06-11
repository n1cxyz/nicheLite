#include "All.hpp"

// Starts up SDL and creates window + renderer
bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Create renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

                // Initialize PNG loading
                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadTexture() {
    bool success = true;

    SDL_Surface* loadedSurface = IMG_Load("assets/trans_char.png");
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", "assets/trans_char.png", IMG_GetError());
        success = false;
    }
    else {
        gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (gTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", "assets/trans_char.png", SDL_GetError());
            success = false;
        } else {
            // Enable alpha blending for transparent PNGs
            SDL_SetTextureBlendMode(gTexture, SDL_BLENDMODE_BLEND);
        }

        SDL_FreeSurface(loadedSurface);
    }

    return success;
}

// Frees media and shuts down SDL
void close() {
    // Free loaded texture
    if (gTexture != nullptr) {
        SDL_DestroyTexture(gTexture);
        gTexture = nullptr;
    }

    // Destroy renderer
    if (gRenderer != nullptr) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = nullptr;
    }

    // Destroy window
    if (gWindow != nullptr) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    // Quit SDL_image
    IMG_Quit();

    // Quit SDL
    SDL_Quit();
}

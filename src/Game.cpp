#include "Game.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "Tile.hpp"
//#include "TextureManager.hpp"
//#include "SDL.h"
#include "SDL_image.h"
#include "fstream"

Game::Game() {}
Game::~Game() {}

bool Game::init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        // Create window
        window_ = SDL_CreateWindow("nicheLite",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window_ == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            // Create renderer
            renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer_ == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);

                // init texture manager
                TextureManager& tm = TextureManager::getInstance();
                tm.setRenderer(renderer_);

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

//const int SCREEN_TICKS_PER_FRAME = 1000 / FPS;

void Game::run() {

    // Main loop flag
    bool quit = false;

    // Event handler
	SDL_Event e;

    // camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    Player player;

    Map map;

    TextureManager& tm = TextureManager::getInstance();

    if (!loadMedia(tm)) {
        printf( "Failed to load media!\n" ); return;
    }
    
    loadLevel("assets/lazy.map");
    
    while (!quit) {
        //capTimer.start();

        // handle events
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Handle player input
            player.handleEvent(e);           
        } 
        //rplayer.setCamera(camera);

        // clear screen
        SDL_RenderClear(renderer_);

        // render level
/*  		for (int i = 0; i < TOTAL_TILES; ++i) {
			tiles[i]->render(renderer_, camera);
		}  */
        renderLevel(renderer_, camera);

        // render player
        //player.render(camera);

        Uint32 currentTime = SDL_GetTicks();

        player.update(currentTime);
        player.move(map.getTiles());
        player.render(renderer_);

        // update screen
        SDL_RenderPresent(renderer_);
    }
}

bool Game::loadMedia(TextureManager& tm) {
	// Loading success flag
	bool success = true;

	// Load player texture
	tm.loadTexture({State::Idle, Direction::Down}, "assets/TDTA/Sheets/Sword/Sword_1_ID.png");
    tm.loadTexture({State::Idle, Direction::Left}, "assets/TDTA/Sheets/Sword/Sword_1_IL.png");
    tm.loadTexture({State::Idle, Direction::Right}, "assets/TDTA/Sheets/Sword/Sword_1_IR.png");
    tm.loadTexture({State::Idle, Direction::Up}, "assets/TDTA/Sheets/Sword/Sword_1_IU.png");
    
    tm.loadTexture({State::Run, Direction::Down}, "assets/TDTA/Sheets/Sword/Sword_2_RD.png");
    tm.loadTexture({State::Run, Direction::Left}, "assets/TDTA/Sheets/Sword/Sword_2_RL.png");
    tm.loadTexture({State::Run, Direction::Right}, "assets/TDTA/Sheets/Sword/Sword_2_RR.png");
    tm.loadTexture({State::Run, Direction::Up}, "assets/TDTA/Sheets/Sword/Sword_2_RU.png");

    // load tile texture
    if (!tm.loadTexture("TILES", "assets/peaceful_pixels/tiles_free.png")) {
        printf("Failed to load file set texture!");
        success = false;
    } else {
        printf("successfully loaded file set texture\n");
    }

    return success;
}

void Game::loadLevel(const std::string& levelFile) {
    map.loadFromFile(levelFile);
}

void Game::renderLevel(SDL_Renderer* renderer, SDL_Rect& camera) {
    map.renderLevel(renderer, camera);
}
/* void Game::shutdown(Tile* tiles[]) {
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (tiles[i] != nullptr) {
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }

    tileTexture.free();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    renderer_ = nullptr;
    window_ = nullptr;

    IMG_Quit();
    SDL_Quit();
} */


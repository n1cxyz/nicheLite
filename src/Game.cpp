#include "Game.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "Tile.hpp"
//#include "TextureManager.hpp"
//#include "SDL.h"
#include "SDL_image.h"
#include "fstream"

/* TextureManager gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES]; */
//SDL_Renderer* renderer_ = nullptr;


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

//const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

void Game::run() {

    // Main loop flag
    bool quit = false;

    // Event handler
	SDL_Event e;

    //Tile* tileSet[TOTAL_TILES];

    Player player;

    TextureManager& tm = TextureManager::getInstance();

    if (!loadMedia(tm)) {
        printf( "Failed to load media!\n" );
        return;
    } else {
        printf("Successfully loaded media!\n");
    }

    // SDL_SetTextureBlendMode(player.getTexture()->getTexture(), SDL_BLENDMODE_BLEND);

/*     const int start_x = 36;
    const int start_y = 50;
    const int horizontal_space = 64;

    for (int i = 0; i < 16; ++i) {
        player.spriteClips[i].x = start_x + i * horizontal_space;
        player.spriteClips[i].y = start_y;
        player.spriteClips[i].w = 32;
        player.spriteClips[i].h = 32;
    } */

    // current animation frame
    //int frame = 0;
    
    // camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

/*     Timer fpsTimer;
    Timer capTimer;
    int countedFrames = 0;
    fpsTimer.start(); */
    
    while (!quit) {
        //capTimer.start();

        // handle events
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            //float avgFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
            /* if (avgFps > 2000000) {
                avgFps = 0;
            } */

            // Handle player input
            player.handleEvent(e);           
        }
        //player.setCamera(camera);

        // clear screen
		SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
		SDL_RenderClear(renderer_);

        // render level
 		for (int i = 0; i < TOTAL_TILES; ++i) {
			tileSet[i]->render(renderer_, camera);
		} 

        // render player
        //player.render(camera);
        //SDL_Rect* currentClip = &player.spriteClips[frame / 4];
        //assert(currentClip->w > 0 && currentClip->h > 0);
/*         player.getTexture()->render(
            (SCREEN_WIDTH - currentClip->w) / 2, 
            (SCREEN_HEIGHT - currentClip->h) / 2, 
            currentClip); */
        Uint32 currentTime = SDL_GetTicks();
        player.update(currentTime);
        player.move(tileSet);
        player.render(renderer_);

       // ++frame;

        // cycle animation
 /*        if (frame >= 16 * 4) {
            frame = 0;
        } */
        // update screen
        SDL_RenderPresent(renderer_);

        //++countedFrames;
        // if frame finished eaerly
        /* int frameTicks = capTimer.getTicks();
        if (frameTicks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
        } */
    }
}

bool Game::loadMedia(TextureManager& tm) {
	// Loading success flag
	bool success = true;

	// Load player texture
	if (!(tm.loadTexture({State::Idle, Direction::Down}, "assets/TopDownTemplateAnimations/SpriteSheets/Sword/Sword_1_Template_Idle_Down-Sheet.png")))	{
		printf( "Failed to load player texture!\n" );
		success = false;
	} else {
        // set sprite clips
        printf("successfully loaded player texture\n");
    }

    // load tile texture
    if (!tm.loadTexture("TILES", "assets/tiles.png")) {
        printf("Failed to load file set texture!");
        success = false;
    } else {
        printf("successfully loaded file set texture\n");
    }

    // load tile map
    if (!setTiles(tileSet)) {
        printf("Failed to load tile set!\n");
        success = false;
    } else {
        printf("successfullu loaded file set\n");
    }

    return success;
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

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // sides of rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // calculate the sides of  rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // if any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }
    if (topA >= bottomB) {
        return false;
    }
    if (rightA <= leftB) {
        return false;
    }
    if (leftA >= rightB) {
        return false;
    }

    return true;
}

bool Game::setTiles(Tile* tiles[]) {
    bool tilesLoaded = true;

    int x = 0, y = 0;

    std::ifstream map("assets/lazy.map");
    if (map.fail()) {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
        return false;
    } else {
        // init tiles
        for (int i = 0; i < TOTAL_TILES; ++i) {
            // determine what kind of tile will be made
            int tileType = -1;

            // read tile from map file
            map >> tileType;
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                tilesLoaded = false;
                break;
            }
            // if the number is a valid tile number
            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                tiles[i] = new Tile(x, y, tileType, &gTileClips[tileType]);
            } else {
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            // move to next tile spot
            x += TILE_WIDTH;

            if (x >= LEVEL_WIDTH) {
                x = 0;
                y += TILE_HEIGHT;
            }
        }

        //Clip the sprite sheet
		if( tilesLoaded )
		{
			gTileClips[ TILE_RED ].x = 0;
			gTileClips[ TILE_RED ].y = 0;
			gTileClips[ TILE_RED ].w = TILE_WIDTH;
			gTileClips[ TILE_RED ].h = TILE_HEIGHT;

			gTileClips[ TILE_GREEN ].x = 0;
			gTileClips[ TILE_GREEN ].y = 80;
			gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
			gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;

			gTileClips[ TILE_BLUE ].x = 0;
			gTileClips[ TILE_BLUE ].y = 160;
			gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
			gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPLEFT ].x = 80;
			gTileClips[ TILE_TOPLEFT ].y = 0;
			gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_LEFT ].x = 80;
			gTileClips[ TILE_LEFT ].y = 80;
			gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMLEFT ].x = 80;
			gTileClips[ TILE_BOTTOMLEFT ].y = 160;
			gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOP ].x = 160;
			gTileClips[ TILE_TOP ].y = 0;
			gTileClips[ TILE_TOP ].w = TILE_WIDTH;
			gTileClips[ TILE_TOP ].h = TILE_HEIGHT;

			gTileClips[ TILE_CENTER ].x = 160;
			gTileClips[ TILE_CENTER ].y = 80;
			gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
			gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOM ].x = 160;
			gTileClips[ TILE_BOTTOM ].y = 160;
			gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

			gTileClips[ TILE_TOPRIGHT ].x = 240;
			gTileClips[ TILE_TOPRIGHT ].y = 0;
			gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_RIGHT ].x = 240;
			gTileClips[ TILE_RIGHT ].y = 80;
			gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

			gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
			gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
			gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
			gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
		}

        map.close();
        //printf("Success\n");
        return tilesLoaded;
    }
}

bool touchesWall(SDL_Rect box, Tile* tiles[]) {
    for (int i = 0; i < TOTAL_TILES; ++i) {
        // if the tile is a wall type 
        if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT)) {
            //printf("AAAAAAaaaaaaaaaaa\n");
            // if the collision box touches the wall tile
            if (checkCollision(box, tiles[i]->getBox())) {
                //printf("touches wall\n");
                return true;
            }
        }
    }

    return false;
}

/* SDL_Renderer* Game::getRenderer() const {
    return renderer_;
} */
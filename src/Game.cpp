#include "All.hpp"

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
            renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
            if (renderer_ == nullptr) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                // Initialize renderer color
                SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0);

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

void Game::run() {

    Tile* tileset[TOTAL_TILES];

    // Main loop flag
    bool quit = false;

    // Event handler
	SDL_Event e;

    Player player;

    if (!loadMedia(tileset, player.getTexture())) {
        printf( "Failed to load media!\n" );
        return;
    }
    
    // camera
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    while (quit) {
        // handle events
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Handle player input
            player.handleEvent(e);           
        }

        player.move(tileset);
        player.setCamera(camera);

        // clear screen
		SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer_);

        // render level
		for (int i = 0; i < TOTAL_TILES; ++i) {
			tileSet[ i ]->render( camera );
		}

        // render player
        player.render(camera);

        // update screen
        SDL_RenderPresent(renderer_);
    }
}

bool Game::loadMedia(Tile* tiles[], Texture* playerTexture) {
	// Loading success flag
	bool success = true;

	// Load player texture
	if (!playerTexture->loadFromFile("assets/trans_char.png"))	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

    // load tile texture
    
    // load tile map
    if (!setTiles(tiles)) {
        printf("Failed to load tile set!\n");
        success = false;
    }

    return success;
}
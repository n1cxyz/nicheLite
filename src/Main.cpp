#include "Game.hpp"

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool touchesWall( SDL_Rect box, Tile* tiles[] );
bool setTiles( Tile *tiles[] );

//Scene textures
TextureManager gDotTexture;

//const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS


int main(void) {
    Game game;
    if (!game.init()) {
        printf("Failed to initialize!\n");
    } else {
        game.run();
    }
    /* TextureManager txt;
    txt.loadFromFile("assets/trans_char.png");
    Player* man = new (Player);
    man->texture = &txt;
    // Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        // Load media
        if (!loadTexture()) {
            printf("Failed to load media!\n");
        }
        else {
            TextureManager txt;
            txt.loadFromFile("assets/trans_char.png");
            Player* man = new (Player);
            man->texture = &txt;
            // Main loop flag
            bool quit = false;
            // Event handler
            SDL_Event e;{}
            
            Timer fpsTimer;
            Timer capTimer;
            int countedFrames = 0;
            fpsTimer.start();

            while (!quit) {
                capTimer.start();

                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    man->handleEvent(e);
                }
                float avgFps = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if (avgFps > 2000000) {
                    avgFps = 0;
                }


                man->move();
                // Clear screen
                SDL_RenderClear(gRenderer);
                // Render texture to screen
                //SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);
                man->render();
                // Update screen
                SDL_RenderPresent(gRenderer);
                ++countedFrames;
                // if frame finished eaerly
                int frameTicks = capTimer.getTicks();
                if (frameTicks < SCREEN_TICKS_PER_FRAME) {
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
                }
            }
        }
    }
    // Free resources and close SDL
    close(); */
    return 0;
}

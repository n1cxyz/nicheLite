#include "All.hpp"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The surface contained by the window
SDL_Texture* gTexture = nullptr;

//The image we will load and show on the screen
SDL_Renderer* gRenderer = nullptr;

const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS

int main(int argc, char* args[]) {
    (void)argc;
    (void)args;
    
    Texture txt;
    txt.loadFromFile("assets/trans_char.png");
    Character* man = new (Character);
    man->texture_ = &txt;
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
            Texture txt;
            txt.loadFromFile("assets/trans_char.png");
            Player* man = new (Player);
            man->texture_ = &txt;
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
    close();
    return 0;
}

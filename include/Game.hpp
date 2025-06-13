#pragma once

class Game {
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

public:
    Game();
    ~Game();

    bool init();
    void run();
    bool loadMedia(Tile* tiles[], Texture* playerTexture);
    void shutdown();

    SDL_Renderer* getRenderer() const { return renderer_; }
};
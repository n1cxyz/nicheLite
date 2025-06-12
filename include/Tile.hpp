
class Tile {
    private:
        SDL_Rect box_;
        int type_;
    public:
        Tile(int x, int y, int tileType);
        void render(SDL_Rect& camera);

        int getType();
        SDL_Rect getBox();
};
#pragma once

//#include "AEntity.hpp"
#include "Animator.hpp"
//#include "SDL.h"
#include "Enums.hpp"
#include <vector>
#include <unordered_map>

class AEntity;
class Map;

class levelManager {
private:
    std::vector<AEntity*>   entities_;
    Map&    currentMap_;

    std::unordered_map<std::tuple<State,Direction,Type>, Animation, TupleHash> animations;

public:
    levelManager(Map& Map);
    ~levelManager();

    void setLevel();

    void loadMap(const std::string& mapFile);
    void loadEntities();
    void loadAnimations();
    // void renderLevel(SDL_Renderer* renderer, SDL_Rect& camera);
};
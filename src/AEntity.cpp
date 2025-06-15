#include "AEntity.hpp"
#include "TextureManager.hpp"

AEntity::AEntity() : posX_(0), posY_(0), width_(32), height_(32) {
    box_ = {0, 0, 32, 32};
}
AEntity::~AEntity() {}




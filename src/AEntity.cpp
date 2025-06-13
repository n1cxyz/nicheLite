#include "All.hpp"

AEntity::AEntity() : posX_(0), posY_(0), width_(20), height_(20) {};
AEntity::~AEntity() {};

void AEntity::render() {
    texture->render(posX_, posY_);
}
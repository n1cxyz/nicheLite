#include "AEntity.hpp"
#include "TextureManager.hpp"

AEntity::AEntity() : posX_(0), posY_(0), width_(20), height_(20) {}
AEntity::~AEntity() {}

/* void AEntity::render() {
    texture_->render(posX_, posY_);
}

void AEntity::setTexture(TextureManager* txt) {
    texture_ = txt;
}

TextureManager* AEntity::getTexture() const {
    return texture_;
}

void AEntity::setRenderer(SDL_Renderer* renderer_) {
    this->renderer_ = renderer_;
} */


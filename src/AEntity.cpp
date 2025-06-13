#include "All.hpp"

AEntity::AEntity() : posX_(0), posY_(0), width_(2000), height_(2000) {}
AEntity::~AEntity() {}

void AEntity::render() {
    texture_->render(posX_, posY_);
}

void AEntity::setTexture(Texture* txt) {
    texture_ = txt;
}

Texture* AEntity::getTexture() const {
    return texture_;
}

void AEntity::setRenderer(SDL_Renderer* renderer_) {
    this->renderer_ = renderer_;
}


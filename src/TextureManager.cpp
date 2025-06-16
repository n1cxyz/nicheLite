#include "TextureManager.hpp"
#include "SDL_image.h"
#include "EnumPairHash.hpp"


SDL_Texture* TextureManager::initTexture(const std::string& filePath) {
	//Get rid of preexisting texture
	//free();

	SDL_Texture* newTexture = nullptr;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
	if (loadedSurface == nullptr) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", filePath.c_str(), IMG_GetError() );
	} else {
		//Color key image
		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (newTexture == nullptr) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError() );
		} else {
			SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
		} 

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

bool TextureManager::loadTexture(const std::pair<State,Direction>& key, const std::string& filePath) {
	SDL_Texture* newTexture = initTexture(filePath);
	if (!newTexture) {
		printf("Failed to load player Texture %s\n", filePath.c_str());
		return false;
	} 

	auto it = playerTextures_.find(key);
	if (it != playerTextures_.end()) {
		SDL_DestroyTexture(it->second);
		playerTextures_.erase(it);
	}

	// add texture to map
	playerTextures_[key] = newTexture;
	SDL_Log("Added texture: state=%d, dir=%d", static_cast<int>(key.first), static_cast<int>(key.second));

	//printf("Success loading player Texture %s\n", filePath.c_str());
	return true;
}

bool TextureManager::loadTexture(const std::string& key, const std::string& filePath) {

	SDL_Texture* newTexture = initTexture(filePath);
	if (!newTexture) {
		return false;
	} 

	auto it = tileTextures_.find(key);
	if (it != tileTextures_.end()) {
		SDL_DestroyTexture(it->second);
		tileTextures_.erase(it);
	}

	// add texture to map
	tileTextures_[key] = newTexture;

	return true;
}

SDL_Texture* TextureManager::getTexture(const std::pair<State,Direction>& key) {
	auto it = playerTextures_.find(key);
    if (it != playerTextures_.end()) {
        return it->second;
    }
	printf("missing texture!\n");
	return nullptr;
}

SDL_Texture* TextureManager::getTexture(const std::string& key) {
	auto it = tileTextures_.find(key);
    if (it != tileTextures_.end()) {
        return it->second;
    }
	printf("missing texture!\n");
	return nullptr;
}
/* void TextureManager::free(SDL_Texture* txt) {
	//Free texture if it exists
	if (txt != nullptr)
	{
		SDL_DestroyTexture(txt);
		txt = nullptr;
		//width_ = 0;
		//height_ = 0;
	}
} */

/* void TextureManager::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(texture_, red, green, blue);
}
		
void TextureManager::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture_, alpha);
}

void TextureManager::	render(int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, clip ? clip->w : width_, clip ? clip->h : height_ };

	if (renderer_ == nullptr) {
		printf("Warning TextureManager::render\n");
	}
	SDL_RenderCopy(renderer_, texture_, clip, &renderQuad);
}

int TextureManager::getWidth() {
	return width_;
}

int TextureManager::getHeight() {
	return height_;
}

SDL_Texture* TextureManager::getTexture() const {
	return texture_;
} */

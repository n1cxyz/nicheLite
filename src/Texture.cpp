#include "TextureManager.hpp"
#include "SDL_image.h"



bool TextureManager::loadTexture(const std::string& id, const std::string& filePath) {

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
		} /* 		else {
			//Get image dimensions
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		} */

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	auto it = textures_.find(id);
	if (it != textures_.end()) {
		SDL_DestroyTexture(it->second);
	}

	// add texture to map
	textures_[id] = newTexture;

	return true;
}

SDL_Texture* TextureManager::getTexture(const std::string& key) {
	SDL_Texture* tex = textures_.at(key);
	return tex;
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

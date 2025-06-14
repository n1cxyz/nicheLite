#include "All.hpp"

Texture::Texture() {
	texture_ = nullptr;
	width_ = 0;
	height_ = 0;
}

Texture::~Texture() {
	free();
}

bool Texture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if (loadedSurface == nullptr)
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer_, loadedSurface);
		if (newTexture == nullptr)
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width_ = loadedSurface->w;
			height_ = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	texture_ = newTexture;
	return texture_ != nullptr;
}

void Texture::free() {
	//Free texture if it exists
	if (texture_ != nullptr)
	{
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	//Modulate texture rgb
	SDL_SetTextureColorMod(texture_, red, green, blue);
}
		
void Texture::setAlpha(Uint8 alpha) {
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture_, alpha);
}

void Texture::	render(int x, int y, SDL_Rect* clip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, width_, height_};

	//Set clip rendering dimensions
	if (clip != nullptr)
	{
		//printf("ggg\n");
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	if (renderer_ == nullptr) {
		printf("Warning Texture::render\n");
	}
	SDL_RenderCopy(renderer_, texture_, clip, &renderQuad);
}

int Texture::getWidth() {
	return width_;
}

int Texture::getHeight() {
	return height_;
}
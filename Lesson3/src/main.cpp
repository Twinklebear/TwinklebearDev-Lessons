#include <stdexcept>
#include <string>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

/*
*  Lesson 3: SDL Extension Libraries
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//We'll be scaling our tiles to be 40x40
const int TILE_SIZE = 40;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}
/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = IMG_Load(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr)
			logSDLError(std::cout, "CreateTextureFromSurface");
	}
	else
		logSDLError(std::cout, "LoadBMP");

	return texture;
}
/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param rend The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
* @param w The width of the texture to draw, default of -1 specifies to use texture width
* @param h The height of the texture to draw, default of -1 specifies to use texture height
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *rend, int x, int y, int w = -1, int h = -1){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	//Set w/h as appropriate based on input
	if (dst.w == -1)
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	else if (dst.h == -1)
		SDL_QueryTexture(tex, NULL, NULL, NULL, &dst.h);

	SDL_RenderCopy(rend, tex, NULL, &dst);
}

int main(int argc, char** argv){
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		logSDLError(std::cout, "CreateWindow");
		return 2;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		return 3;
	}
	
	//The textures we'll be using
	SDL_Texture *background = loadTexture("../res/Lesson3/background.png", renderer);
	SDL_Texture *image = loadTexture("../res/Lesson3/image.png", renderer);
	//Make sure they both loaded ok
	if (background == nullptr || image == nullptr)
		return 4;

	//Clear the window
	SDL_RenderClear(renderer);

	//Determine how many tiles we'll need to fill the screen
	int xTiles = SCREEN_WIDTH / TILE_SIZE;
	int yTiles = SCREEN_HEIGHT / TILE_SIZE;

	//Draw the tiles by calculating their positions
	for (int i = 0; i < xTiles * yTiles; ++i){
		int x = i % xTiles;
		int y = i / xTiles;
		renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}

	//Draw our image in the center of the window
	//We need the foreground image's width to properly compute the position
	//of it's top left corner so that the image will be centered
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	renderTexture(image, renderer, x, y);

	//Update the screen
	SDL_RenderPresent(renderer);
	SDL_Delay(2000);

	//Destroy the various items
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	
	return 0;
}

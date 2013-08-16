#include <stdexcept>
#include <string>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_image.h>
#elif defined(__clang__)
#include <SDL2_image/SDL_image.h>
#elif defined(__clang__) or defined(__GNUC__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL_image.h>
#endif

/*
*  Lesson 3: SDL Extension Libraries
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//Globals for window and renderer
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

/*
*  Loads an image directly to texture using SDL_image's
*  built in function IMG_LoadTexture
*  @param file the image file to load
*  @return SDL_Texture* to the loaded texture
*/
SDL_Texture* LoadImage(std::string file){
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(renderer, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}
/*
*  Draw an SDL_Texture to an SDL_Renderer at position x, y
*  @param x x coordinate to draw too
*  @param y y coordinate to draw too
*  @param tex the source texture we want to draw
*  @param rend the renderer we want to draw too
*/
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend){
	//First we must create an SDL_Rect for the position of the image, as SDL
	//won't accept raw coordinates as the image's position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	//We also need to query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(rend, tex, NULL, &pos);
}

int main(int argc, char** argv){
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	//Setup our window and renderer
	window = SDL_CreateWindow("Lesson 3", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 2;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED 
		| SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 3;
	}
	
	//The textures we'll be using
	SDL_Texture *background = nullptr, *image = nullptr;
	try {
		background = LoadImage("../res/Lesson3/background.png");
		image = LoadImage("../res/Lesson3/image.png");
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		return 4;
	}

	//Clear the window
	SDL_RenderClear(renderer);

	//Get the width and height from the texture so we know how much to move x,y by
	//to tile it correctly
	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
	//We want to tile our background so draw it 4 times
	ApplySurface(0, 0, background, renderer);
	ApplySurface(bW, 0, background, renderer);
	ApplySurface(0, bH, background, renderer);
	ApplySurface(bW, bH, background, renderer);
	//Draw our image in the center of the window
	//We also need its width so query it as well
	int iW, iH;
	SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	ApplySurface(x, y, image, renderer);

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

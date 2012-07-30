#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <string>
#include <iostream>

/*
*  Lesson 5: Clipping Sprite Sheets
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//Globals for window and renderer
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;

/**
*  Loads an image directly to texture using SDL_image's
*  built in function IMG_LoadTexture
*  @param file The image file to load
*  @return SDL_Texture* to the loaded texture
*/
SDL_Texture* LoadImage(std::string file){
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(renderer, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file);
	return tex;
}
/**
*  Draw an SDL_Texture to an SDL_Renderer at position x, y
*  @param x The x coordinate to draw too
*  @param y The y coordinate to draw too
*  @param tex The source texture we want to draw
*  @param rend The renderer we want to draw too
*  @param clip The clip to take from the texture, NULL is default
*/
void ApplySurface(int x, int y, SDL_Texture *tex, SDL_Renderer *rend, SDL_Rect *clip = NULL){
	//First we must create an SDL_Rect for the position of the image, as SDL
	//won't accept raw coordinates as the image's position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	//Detect if we should use clip width settings or texture width
	if (clip != NULL){
		pos.w = clip->w;
		pos.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	}
	SDL_RenderCopy(rend, tex, clip, &pos);
}

int main(int argc, char** argv){
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 1;

	//Setup our window and renderer
	window = SDL_CreateWindow("Lesson 5", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		return 2;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		return 3;
	
	SDL_Texture *image = nullptr;
	try {
		image = LoadImage("Lesson5res/image.png");
	}
	catch (const std::runtime_error &e){
		std::cout << e.what() << std::endl;
		return 4;
	}
	//Setup image positioning
	int iW = 100, iH = 100;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;
	//Setup the clips
	//iW and iH are the desired clip width and height
	SDL_Rect clips[4];
	//We use a for loop this time to setup our clips
	int column = 0;
	for (int i = 0; i < 4; ++i){
		if (i != 0 && i % 2 == 0)
			++column;
		
		clips[i].x = column * iW;
		clips[i].y = i % 2 * iH;
		clips[i].w = iW;
		clips[i].h = iH;
	}
	//Specify a default clip to start with
	int useClip = 0;

	//Our event type
	SDL_Event e;
	//For tracking if we want to quit
	bool quit = false;
	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			//If user closes he window
			if (e.type == SDL_QUIT)
				quit = true;
			//If user presses any key
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					case SDLK_1:
						useClip = 0;
						break;
					case SDLK_2:
						useClip = 1;
						break;
					case SDLK_3:
						useClip = 2;
						break;
					case SDLK_4:
						useClip = 3;
						break;
					//For quitting, escape key
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
		}
		//Rendering
		SDL_RenderClear(renderer);
		//Draw the image
		ApplySurface(x, y, image, renderer, &clips[useClip]);

		//Update the screen
		SDL_RenderPresent(renderer);
	}

	//Destroy the various items
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
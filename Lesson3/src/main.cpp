#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <string>
//TODO: Write this lesson
/*
*	Lesson 3: SDL Extension Libraries NOT YET WRITTEN
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP	= 32;
//Globals for window and renderer
SDL_Renderer *ren = nullptr;
SDL_Window *win = nullptr;

/*
*  Loads an image directly to texture using SDL_image's
*  built in function IMG_LoadTexture
*  @param file: the image file to load
*  @returns SDL_Texture* to the loaded texture
*/
SDL_Surface* LoadImage(std::string file){
	SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(ren, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file);
	return tex;
}
/*
*  Draw an SDL_Texture to an SDL_Renderer at position x, y
*  @param x: x coordinate to draw too
*  @param y: y coordinate to draw too
*  @param tex: the source texture we want to draw
*  @param rend: the renderer we want to draw too
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
	//TODO: Add Init() CleanUp() and such functions to get stuff out of main
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << "SDL_Init failed" << std::endl;
		return 1;
	}
	//The surfaces we'll be using
	SDL_Surface *screen = NULL, *background = NULL, *image = NULL;
	//setup our screen
	screen =  SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (screen == NULL){
		std::cout << "Couldn't open screen" << std::endl;
		return 1;
	}
	//Set a window caption
	SDL_WM_SetCaption("Lesson 2", NULL);
	
	//Load the images
	background = LoadImage("Lesson3res/background.bmp");
	image = LoadImage("Lesson3res/image.bmp");
	//Make sure it went ok
	if (background == NULL || image == NULL){
		std::cout << "Couldn't load images" << std::endl;
		return 1;
	}
	//Our event queue
	SDL_Event event;
	//Our 'game' loop
	bool quit = false;
	while (!quit){
		//Event Polling & Handling
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT)
				quit = true;
		}
		//Rendering 
		//We want to tile our background so draw it 4 times
		ApplySurface(0, 0, background, screen);
		ApplySurface(background->w, 0, background, screen);
		ApplySurface(0, background->h, background, screen);
		ApplySurface(background->w, background->h, background, screen);
		//Draw our image in the center of the 
		int x = SCREEN_WIDTH / 2 - image->w / 2;
		int y = SCREEN_HEIGHT / 2 - image->h / 2;
		ApplySurface(x, y, image, screen);

		//Update the screen
		if (SDL_Flip(screen) == -1){
			std::cout << "Couldn't flip screen" << std::endl;
			return 1;
		}
	}
	//Free the surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(image);

	SDL_Quit();
	
	return 0;
}
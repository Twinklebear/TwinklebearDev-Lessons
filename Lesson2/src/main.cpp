#include "SDL.h"
#include <iostream>
#include <string>

/*
*	Lesson 2: Optimized Surface Loading and Blitting
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP	= 32;

/*
*	Loads a bmp image, converts it to match the BPP of the screen 
*	so we don't convert each time we blit
*	@param file: the image file to load
*	@returns SDL_Surface* to the optimized surface
*/
SDL_Surface* LoadImage(std::string file){
	//The temporary surface to store the unoptimized image in
	SDL_Surface *loadedImage = NULL;
	//the surface we will store the optimized image in
	SDL_Surface *optimizedImage = NULL;
	
	//Load the image
	loadedImage = SDL_LoadBMP(file.c_str());
	//if the loading went ok, optimized the surface and return it
	if (loadedImage != NULL){
		//SDL display format converts the passed surface to a format suitable for fast blitting
		optimizedImage = SDL_DisplayFormat(loadedImage);
		//Free the old image
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}
/*
*	Draw an SDL_Surface source to some SDL_Surface destination, at position x, y
*	@param x: x coordinate to draw too
*	@param y: y coordinate to draw too
*	@param src: the source surface we want to draw
*	@param dest: the destination surface we want to blit to
*/
void ApplySurface(int x, int y, SDL_Surface *src, SDL_Surface *dest){
	//First we must create an SDL_Rect for the position of the image, as SDL
	//won't accept raw coordinates as the image's position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	//Now we can blit the surface, note that we pass pos by address because BlitSurface takes a pointer, ie. address
	SDL_BlitSurface(src, NULL, dest, &pos);
}

int main(int argc, char** argv){
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
	background = LoadImage("Lesson2res/background.bmp");
	image = LoadImage("Lesson2res/image.bmp");
	//Make sure it went ok
	if (background == NULL || image == NULL){
		std::cout << "Couldn't load images" << std::endl;
		return 1;
	}

	//We want to tile our background so draw it 4 times
	ApplySurface(0, 0, background, screen);
	ApplySurface(320, 0, background, screen);
	ApplySurface(0, 240, background, screen);
	ApplySurface(320, 240, background, screen);
	//Draw our image in the center of the 
	int x = SCREEN_WIDTH / 2 - image->w / 2;
	int y = SCREEN_HEIGHT / 2 - image->h / 2;
	ApplySurface(x, y, image, screen);

	//Update the screen
	if (SDL_Flip(screen) == -1){
		std::cout << "Couldn't flip screen" << std::endl;
		return 1;
	}
	SDL_Delay(2000);

	//Free the surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(image);

	SDL_Quit();
	
	return 0;
}
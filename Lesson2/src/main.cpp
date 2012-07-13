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
	
}

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Quit();
	
	return 0;
}
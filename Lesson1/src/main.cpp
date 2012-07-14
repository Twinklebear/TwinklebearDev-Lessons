#include <iostream>
#include "SDL.h"

/*
* Lesson 1: Hello world!
*/
int main(int argc, char** argv){
	//Our SDL_Surfaces, these will be pointers to our image's location in memory
	//or in the case of the screen, it's location. We set them to NULL initially
	//so we can make sure they load correctly
	SDL_Surface *screen = NULL, *image = NULL;
	//Next start up SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Here we create our screen. We tell SDL we want it to be 640px wide, 480px tall
	//and with 32bits per pixel, we also pass a flag to tell SDL to create it as a 
	//softwar surface
	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	//if SDL failed to create our screen, abort
	if (screen == NULL){
		std::cout << "Failed to create screen" << std::endl;
		return 1;
	}
	//Next we will use SDL's Load_BMP function to load our bmp image, pass it the 
	//filepath relative to where the executable will be located
	image = SDL_LoadBMP("Lesson1res/hello.bmp");
	//if our image failed to load
	if (image == NULL){
		std::cout << "Failed to load image" << std::endl;
		return 1;
	}

	//Blit the surface to the screen
	SDL_BlitSurface(image, NULL, screen, NULL);
	//Update the screen
	SDL_Flip(screen);
	
	//Have the program wait for 2000ms
	SDL_Delay(2000);

	//Free the loaded image
	SDL_FreeSurface(image);

	SDL_Quit();
	
	return 0;
}
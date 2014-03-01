#include <iostream>
#include <SDL.h>
#include "asset.h"

/*
 * Lesson 0: Test to make sure SDL is setup properly
 */
#undef main
int main(int argc, char **argv){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Quit();

	return 0;
}


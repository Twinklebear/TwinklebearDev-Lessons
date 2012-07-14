#include "SDL.h"

/*
* Lesson0: A simple program to make sure your SDL environment is set up correctly
*/
int main(int argc, char** argv){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Quit();
	
	return 0;
}
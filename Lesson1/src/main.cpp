#include <iostream>
#include <SDL.h>
#include "asset.h"

/*
 * Lesson 1: Hello World!
 */
int main(int argc, char** argv){
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	//Now create a window with title "Hello World" at 100, 100 on the screen with w:640 h:480 and show it
	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//Make sure creating our window went ok
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create a renderer that will draw to the window, -1 specifies that we want to load whichever
	//video driver supports the flags we're passing
	//Flags: SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering
	//SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
	//synchornized with the monitor's refresh rate
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//SDL 2.0 now uses textures to draw things but SDL_LoadBMP returns a surface
	//this lets us choose when to upload or remove textures from the GPU
	SDL_Surface *bmp = SDL_LoadBMP(ASSET("Lesson1/hello.bmp"));
	if (bmp == nullptr){
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//To use a hardware accelerated texture for rendering we can create one from
	//the surface we loaded
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
	//We no longer need the surface
	SDL_FreeSurface(bmp);
	if (tex == nullptr){
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	//Now lets draw our image
	//First clear the renderer
	SDL_RenderClear(ren);
	//Draw the texture
	SDL_RenderCopy(ren, tex, NULL, NULL);
	//Update the screen
	SDL_RenderPresent(ren);

	//Have the program wait for 2000ms so we get a chance to see the screen
	SDL_Delay(2000);

	//Clean up our objects and quit
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return 0;
}


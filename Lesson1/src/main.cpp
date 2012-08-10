#include <iostream>
#include "SDL.h"

/*
*  Lesson 1: Hello world!
*/
int main(int argc, char** argv){
	//First we need to start up SDL, and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	
	//First we need to create a window to draw things in
	SDL_Window *win = nullptr;
	//Create a window with title "Hello World" at 100, 100 on the screen with w:640 h:480 and show it
	win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	//Make sure creating our window went ok
	if (win == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	//Now we create our renderer
	SDL_Renderer *ren = nullptr;
	//Create a renderer that will draw to window, -1 specifies that we want to load whichever 
	//video driver supports the flags we're passing
	//Flags: SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering, b/c it rocks!
	//SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
	//synchornized with the monitor's refresh rate
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}

	//SDL 2.0 now uses textures to draw things, but without the SDL_image extension we still
	//must load the image as a bmp SDL_Surface and the convert it
	SDL_Surface *bmp = nullptr;
	bmp = SDL_LoadBMP("../res/Lesson1/hello.bmp");
	if (bmp == nullptr){
		std::cout << SDL_GetError() << std::endl;
		return 1;
	}
	//The texture we'll be drawing
	SDL_Texture *tex = nullptr;
	//Now convert it to a texture that is optimized for our renderer
	tex = SDL_CreateTextureFromSurface(ren, bmp);
	//Now we no longer need the image so we can free it
	SDL_FreeSurface(bmp);

	//Now lets draw our image
	//First clear the renderer
	SDL_RenderClear(ren);
	//Now draw the texture
	SDL_RenderCopy(ren, tex, NULL, NULL);
	//Update the screen
	SDL_RenderPresent(ren);

	//Have the program wait for 2000ms
	SDL_Delay(2000);

	//Destroy our stuff
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);

	SDL_Quit();
	
	return 0;
}
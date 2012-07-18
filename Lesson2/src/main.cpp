#include "SDL.h"
#include <string>

/*
* Lesson 2: Don't Put Everything in Main
*/
//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//Our window and renderer
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

/*
*  Loads a BMP image and converts it to an SDL_Texture that we can use
*  for hardware accelerated rendering
*  @param file: the image file to load
*  @returns SDL_Texture* to the loaded texture
*/
SDL_Texture* LoadImage(std::string file){
	//The temporary surface to store the loaded bmp image in
	SDL_Surface *loadedImage = nullptr;
	//The texture we will store the converted texture in
	SDL_Texture *texture = nullptr;
	
	//Load the image
	loadedImage = SDL_LoadBMP(file.c_str());
	//if the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		//Free the old image
		SDL_FreeSurface(loadedImage);
	}
	return texture;
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
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return 1;

	//Setup our window and renderer
	window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		return 2;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
		return 3;

	//The textures we'll be using
	SDL_Texture *background = nullptr, *image = nullptr;
	background = LoadImage("Lesson2res/background.bmp");
	image = LoadImage("Lesson2res/image.bmp");
	//Make sure it went ok
	if (background == nullptr || image == nullptr)
		return 4;

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
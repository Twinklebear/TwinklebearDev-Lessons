#include <SDL.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include "window.h"

int main(int argc, char** argv){
    //Start our window
    try {
        Window::Init("Lesson 7");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }

    //Our event structure
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
					//For quitting, escape key
					case SDLK_ESCAPE:
						quit = true;
						break;
					default:
						break;
				}
			}
		}
        //RENDERING
        Window::Clear();


        Window::Present();
	}
    Window::Quit();
	
	return 0;
}
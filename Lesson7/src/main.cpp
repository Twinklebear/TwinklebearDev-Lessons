#include <SDL.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include "window.h"

/*
*  Lesson 7: Taking advantage of classes
*/
int main(int argc, char** argv){
    //Start our window
    try {
        Window::Init("Lesson 7");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }

    //Load up an image
    SDL_Texture *img;
    try {
        std::string file = "../res/Lesson7/image.png";
        img = Window::LoadImage(file);
    }
    catch (const std::runtime_error &e){
        //Catch error and crash
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }
    //Set a position to draw it with
    SDL_Rect pos = { Window::Box().w / 2 - 100 / 2,
                     Window::Box().h / 2 - 100 / 2,
                     100, 100 };
    //The angle to draw at, so we can play with it
    int angle = 0;

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
                    //For rotating image
                    case SDLK_d:
                        angle += 2;
                        break;
                    case SDLK_a:
                        angle -= 2;
                        break;
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
        //Draw our image with a 45 degree rotation
        Window::Draw(img, pos, NULL, angle);

        Window::Present();
	}
	
	return 0;
}
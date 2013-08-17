#include <stdexcept>
#include <string>
#include <iostream>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "../include/window.h"

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
        Window::Quit();
        return -1;
    }

    //Load up an image and some text
    SDL_Texture *img, *msg;
    try {
        //Load the image
        std::string imgFile = "../res/Lesson7/image.png";
        img = Window::LoadImage(imgFile);
        //Load the font and message
        std::string fontFile = "../res/Lesson7/SourceSansPro-Regular.ttf";
        std::string text = "TTF Fonts too!";
        SDL_Color color = { 255, 255, 255 };
        msg = Window::RenderText(text, fontFile, color, 25);
    }
    catch (const std::runtime_error &e){
        //Catch error and crash
        std::cout << e.what() << std::endl;
        Window::Quit();
        return -1;
    }
    //Set a position to draw it with
    SDL_Rect pos = { Window::Box().w / 2 - 150 / 2,
        Window::Box().h / 2 - 150 / 2, 150, 150 };
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

        Window::Draw(img, pos, NULL, angle);
        Window::Draw(msg, pos, NULL, angle, 0, 0, SDL_FLIP_VERTICAL);

        Window::Present();
	}
    SDL_DestroyTexture(img);
    SDL_DestroyTexture(msg);
	Window::Quit();

	return 0;
}
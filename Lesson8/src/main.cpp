#include <SDL.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include "window.h"
#include "timer.h"

int main(int argc, char** argv){
    //Start our window
    try {
        Window::Init("Lesson 8");
    }
    catch (const std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }

    //Our timer:
    Timer timer;
    //Textures to display a message and ticks elapsed
    SDL_Texture *msg = nullptr, *ticks = nullptr;
    //Color for the text
    SDL_Color white = { 255, 255, 255 };
    //Rects for the text
    SDL_Rect msgBox, ticksBox;
    
    //Setup msg text
    msg = Window::RenderText("Ticks Elapsed: ", "../res/Lesson8/SourceSansPro-Regular.ttf", white, 30);
    //Setup msg dstRect
    msgBox.x = 0;
    msgBox.y = Window::Box().h / 2;
    //Query w & h from texture
    SDL_QueryTexture(msg, NULL, NULL, &msgBox.w, &msgBox.h);
    
    //Setup ticks message
    //We must use a stringstream to convert int to string
    std::stringstream ssTicks;
    ssTicks << timer.Ticks();
    ticks = Window::RenderText(ssTicks.str(), "../res/Lesson8/SourceSansPro-Regular.ttf", white, 30);
    //clear the stream
    ssTicks.str("");
    //Setup the ticks dstRect
    ticksBox.x = msgBox.w + 20;
    ticksBox.y = Window::Box().h / 2;
    SDL_QueryTexture(ticks, NULL, NULL, &ticksBox.w, &ticksBox.h);

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
                    //Start/stop the timer
                    case SDLK_s:
                        //If timer was running, stop it
                        if (timer.Started())
                            timer.Stop();
                        else
                            timer.Start();
                        break;
                    case SDLK_p:
                        if (timer.Paused())
                            timer.Unpause();
                        else
                            timer.Pause();
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
        //LOGIC
        //If the timer is running, update the ticks message
        if (timer.Started() && !timer.Paused()){
            //Update text
            ssTicks << timer.Ticks();
            SDL_DestroyTexture(ticks);
            ticks = Window::RenderText(ssTicks.str(), "../res/Lesson8/SourceSansPro-Regular.ttf", white, 30);
            ssTicks.str("");
            //Update w/h
            SDL_QueryTexture(ticks, NULL, NULL, &ticksBox.w, &ticksBox.h);
        }
        //RENDERING
        Window::Clear();

        Window::Draw(msg, msgBox);
        Window::Draw(ticks, ticksBox);

        Window::Present();
	}
    Window::Quit();
	
	return 0;
}
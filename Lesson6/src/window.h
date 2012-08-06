#include <string>
#include <stdexcept>
#include "SDL.h"

/*
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window{
public:
	/*
	*  Initialize SDL, setup the window and renderer
	*  @param title: the window title
	*/
	static void Init(std::string title = "Window");
	/*
	*  Quit SDL and destroy the window and renderer
	*/
	static void Quit();
	/*
	*  Draw a texture to the screen, with no scaling applied
	*  @param x: The x coordinate to draw too
	*  @param y: The y coordinate to draw too
	*  @param tex: The SDL_Texture* to draw
	*  @param clip: The clip rect to apply to the texture, if desired
	*/
	static void Draw(int x, int y, SDL_Texture *tex, SDL_Rect *clip = NULL);
	/*
	*  Load an image file into an SDL_Texture and return it
	*  @param file: the image file to load
	*  @return SDL_Texture* of the texture loaded
	*/
	static SDL_Texture* LoadTexture(std::string file);
	/*
	*  Clear the renderer
	*/
	static void Clear();
	/*
	*  Render the renderer to window
	*/
	static void Flip();
	/*
	*  Handle window events
	*/
	static void HandleEvents(SDL_Event &e);
	/*
	*  Return the window box
	*/
	static SDL_Rect Box();

private:
	static SDL_Window *mWindow;
	static SDL_Renderer *mRenderer;
	//TODO: Replace with Rect<int>
	static SDL_Rect mBox;
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
};
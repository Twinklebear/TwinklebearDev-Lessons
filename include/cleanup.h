#ifndef CLEANUP_H
#define CLEANUP_H

#include <SDL.h>

/*
 * Clean up each argument in the list
 */
template<typename T, typename... Args>
void cleanup(T *t, Args&&... args){
	cleanup(t);
	cleanup(std::forward<Args>(args)...);
}
/*
 * These serve to free the passed argument and also provide the
 * base cases for the template recursion
 */
template<>
void cleanup<SDL_Window>(SDL_Window *win){
	SDL_DestroyWindow(win);
}
template<>
void cleanup<SDL_Renderer>(SDL_Renderer *ren){
	SDL_DestroyRenderer(ren);
}
template<>
void cleanup<SDL_Texture>(SDL_Texture *tex){
	SDL_DestroyTexture(tex);
}
template<>
void cleanup<SDL_Surface>(SDL_Surface *surf){
	SDL_FreeSurface(surf);
}

#endif


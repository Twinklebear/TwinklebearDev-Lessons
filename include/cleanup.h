#ifndef CLEANUP_H
#define CLEANUP_H

#include <SDL.h>

/*
 * These serve to free the passed argument and also provide the
 * base cases for the template recursion
 */
void cleanup(SDL_Window *win){
	SDL_DestroyWindow(win);
}
void cleanup(SDL_Renderer *ren){
	SDL_DestroyRenderer(ren);
}
void cleanup(SDL_Texture *tex){
	SDL_DestroyTexture(tex);
}
void cleanup(SDL_Surface *surf){
	SDL_FreeSurface(surf);
}
/*
 * Clean up each argument in the list
 */
template<typename T, typename... Args>
void cleanup(T *t, Args&&... args){
	cleanup(t);
	cleanup(args...);
}

#endif


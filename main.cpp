#include <stdlib.h>

#include <iostream>

#include <SDL.h>

int
main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}

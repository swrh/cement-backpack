#include <stdlib.h>

#include "game.hpp"

int
main(int argc, const char *argv[])
{
	const Uint32 MIN_FRAME_TIME = 16;

	Game game;

	game.init("foobar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game.running()) {
		Uint32 frameTime = SDL_GetTicks();

		game.handleEvents();
		game.update();
		game.render();

		frameTime = SDL_GetTicks() - frameTime;
		if (frameTime < MIN_FRAME_TIME)
			SDL_Delay(MIN_FRAME_TIME - frameTime);
	}

	game.terminate();

	return EXIT_SUCCESS;
}

// vim:set sw=4 ts=4 noet:

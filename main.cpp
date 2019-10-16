#include <stdlib.h>

#include "game.hpp"
#include "sdl.hpp"

int
main(int argc, char *argv[])
{
	sdl::Init init(SDL_INIT_VIDEO);

	Game game("cb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	for (;;) {
		bool hadEvent = game.handleEvents();
		if (!game.isRunning())
			break;
		game.update();
		game.draw();
		if (!hadEvent)
			game.delay();
	}

	return EXIT_SUCCESS;
}

// vim:set sw=4 ts=4 noet:

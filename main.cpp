#include <stdlib.h>

#include "game.hpp"

int
main(int argc, const char *argv[])
{
	Game game;

	game.init("Foobar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game.running()) {
		game.handleEvents();
		game.update();
		game.render();
	}

	game.clean();

	return EXIT_SUCCESS;
}

// vim:set sw=4 ts=4 noet:

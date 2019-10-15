#include <stdlib.h>

#include "game.hpp"
#include "sdl.hpp"
#include "ticks.hpp"

int
main(int argc, char *argv[])
{
	sdl::Init init(SDL_INIT_EVERYTHING);

	const Uint32 MIN_FRAME_TIME = 16;

	Game game("cb", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	Ticks ticks;

	while (game.isRunning()) {
		Uint32 current = ticks.update();

		bool hadEvent = game.handleEvents();
		game.update();
		if (hadEvent)
			continue;

		game.draw();

		Uint32 diff = ticks.now() - current;
		if (diff < MIN_FRAME_TIME)
			SDL_Delay(MIN_FRAME_TIME - diff);
	}

	return EXIT_SUCCESS;
}

// vim:set sw=4 ts=4 noet:

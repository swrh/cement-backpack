#if !defined(GAME_HPP)
#define GAME_HPP

#include <SDL2/SDL.h>

#include "exception.hpp"

class
Game
{
private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

public:
	Game()
	{
	}

	~Game()
	{
	}

private:
	bool initialized = false;
public:
	void
	init(const char *title, std::size_t xpos, std::size_t ypos, std::size_t width, std::size_t height, bool fullscreen)
	{
		if (!initialized) {
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
				throw Exception("SDL_Init failed");
			initialized = true;
		}

		if (!window) {
			int flags = 0;
			if (fullscreen)
				flags |= SDL_WINDOW_FULLSCREEN;
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			if (!window)
				throw Exception("SDL_CreateWindow failed");
		}

		if (!renderer) {
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (!renderer)
				throw Exception("SDL_CreateRenderer failed");

			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	void
	handleEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
		}
	}

	void
	update()
	{
	}

	void
	render()
	{
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}

	void clean()
	{
		if (window)
			SDL_DestroyWindow(window);
		window = nullptr;

		if (renderer)
			SDL_DestroyRenderer(renderer);
		renderer = nullptr;

		SDL_Quit();
	}

private:
	bool isRunning = false;
public:
	bool running()
	{
		return isRunning;
	}

};

#endif // !defined(GAME_HPP)

// vim:set sw=4 ts=4 noet:

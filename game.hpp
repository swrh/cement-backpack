#if !defined(GAME_HPP)
#define GAME_HPP

#include <SDL2/SDL.h>

#include "exception.hpp"
#include "gameobject.hpp"
#include "sdl.hpp"

class
Game
{
private:
	Sdl::WindowPtr window;
	Sdl::RendererPtr renderer;

	std::shared_ptr<GameObject> player;

public:
	Game(const char *title, std::size_t x, std::size_t y, std::size_t w, std::size_t h, bool fullscreen)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw Exception("SDL_Init failed");
		isInitialized = true;

		int flags = 0;
		if (fullscreen)
			flags |= SDL_WINDOW_FULLSCREEN;
		window = Sdl::makeWindow(title, x, y, w, h, flags);

		renderer = Sdl::makeRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

		player = std::make_shared<GameObject>("assets/guy1idle0.png", renderer, 0, 0);

		isRunning = true;
	}

	~Game()
	{
		player.reset();
		renderer.reset();
		window.reset();

		if (isInitialized)
			SDL_Quit();
		isInitialized = false;
	}

private:
	bool isInitialized = false;
public:
	void
	handleEvents()
	{
		SDL_Event event;

		if (!SDL_PollEvent(&event))
			return;

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
		player->update();
	}

	void
	render()
	{
		SDL_RenderClear(renderer.get());

		player->render();

		SDL_RenderPresent(renderer.get());
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

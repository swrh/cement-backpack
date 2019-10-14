#if !defined(GAME_HPP)
#define GAME_HPP

#include <SDL.h>

#include "sdl.hpp"

class
Game
{
private:
	sdl::WindowPtr window_;
	sdl::RendererPtr renderer_;

	SDL_Event event_;

public:
	Game(const char *title, std::size_t x, std::size_t y, std::size_t w, std::size_t h, bool fullscreen)
	{
		Uint32 flags = 0;
		if (fullscreen)
			flags |= SDL_WINDOW_FULLSCREEN;
		window_ = sdl::makeWindow(title, x, y, w, h, flags);

		renderer_ = sdl::makeRenderer(*window_, -1, 0);
	}

	~Game()
	{
		renderer_.reset();
		window_.reset();
	}

public:
	bool
	handleEvents()
	{
		bool hadEvent = !!SDL_PollEvent(&event_);
		if (hadEvent) {
			if (event_.type == SDL_QUIT) {
				running_ = false;
			}
		} else {
			SDL_zero(event_);
		}
		return hadEvent;
	}

	void
	update()
	{
	}

	void
	draw()
	{
		SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer_.get());

		SDL_RenderPresent(renderer_.get());
	}

private:
	bool running_ = true;
public:
	bool isRunning()
	{
		return running_;
	}

};

#endif // !defined(GAME_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(GAME_HPP)
#define GAME_HPP

#include <SDL.h>

#include "boxcomponent.hpp"
#include "drawcolorcomponent.hpp"
#include "entity.hpp"
#include "keyboardcomponent.hpp"
#include "manager.hpp"
#include "point.hpp"
#include "rectanglecomponent.hpp"
#include "sdl.hpp"
#include "ticks.hpp"
#include "transformcomponent.hpp"

class
Game
{
private:
	constexpr static Uint32 MIN_FRAME_TIME = 16;

	SDL_Event event_ = {};

	sdl::WindowPtr window_;
	sdl::RendererPtr renderer_;

	Ticks ticks_;
	Manager manager_;

	Entity &player_ = manager_.addEntity();
	Entity &ground_ = manager_.addEntity();

public:
	Game(const char *title, std::size_t x, std::size_t y, std::size_t w, std::size_t h)
		: window_(sdl::makeWindow(title, x, y, w, h, 0))
		, renderer_(sdl::makeRenderer(*window_, -1, 0))
	{
		player_.addComponent<TransformComponent>(ticks_, Point<double> { 10, 10 });
		player_.addComponent<KeyboardComponent>(event_);
		player_.addComponent<DrawColorComponent>(*renderer_, SDL_Color { 100, 200, 200, 255 });
		player_.addComponent<BoxComponent>(*renderer_, SDL_Point { 20, 20 });

		ground_.addComponent<DrawColorComponent>(*renderer_, SDL_Color { 200, 100, 200, 255 });
		ground_.addComponent<RectangleComponent>(*renderer_, SDL_Rect { 0, 500, 800, 20 });
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
		bool hadEvent;
		for (;;) {
			hadEvent = !!SDL_PollEvent(&event_);
			// Ignore all key up/down repeat events
			if (!hadEvent || (event_.type != SDL_KEYDOWN && event_.type != SDL_KEYUP) || (event_.key.repeat == 0))
				break;
		}
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
		ticks_.update();
		manager_.refresh();
		manager_.update();
	}

	void
	draw()
	{
		SDL_SetRenderDrawColor(renderer_.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer_.get());
		manager_.draw();
		SDL_RenderPresent(renderer_.get());
	}

	void
	sleep()
	{
		Uint32 delta = ticks_.now() - ticks_.current();
		if (delta < MIN_FRAME_TIME)
			SDL_WaitEventTimeout(nullptr, MIN_FRAME_TIME - delta);
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

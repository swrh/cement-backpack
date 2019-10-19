#if !defined(GAME_HPP)
#define GAME_HPP

#include <SDL.h>

#include "collision.hpp"
#include "entity.hpp"
#include "exception.hpp"
#include "keyboardcomponent.hpp"
#include "manager.hpp"
#include "map.hpp"
#include "playerspritesheet.hpp"
#include "point.hpp"
#include "recoilcomponent.hpp"
#include "sdl.hpp"
#include "spritecomponent.hpp"
#include "spritesheetcomponent.hpp"
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

	std::unique_ptr<Map> map_;
	std::unique_ptr<PlayerSpriteSheet> playerSpriteSheet_;

	Ticks ticks_;
	Manager manager_;
	Entity &player_ = manager_.addEntity();
	Entity &wall_ = manager_.addEntity();

	std::vector<ColliderComponent *> colliders_;

public:
	Game(const char *title, std::size_t x, std::size_t y, std::size_t w, std::size_t h)
		: window_(sdl::makeWindow(title, x, y, w, h, 0))
		, renderer_(sdl::makeRenderer(*window_, -1, 0))
	{
		map_.reset(new Map("assets/map.txt", *renderer_));
		playerSpriteSheet_.reset(new PlayerSpriteSheet(*renderer_));

		player_.addComponent<TransformComponent>(ticks_, Point<double> { 0, 0 }, SDL_Point { 19, 34 }, 1);
		player_.addComponent<SpriteSheetComponent>(*renderer_, *playerSpriteSheet_).selectSprites(playerSpriteSheet_->getIdleSprites(), 100);
		player_.addComponent<KeyboardComponent>(event_);
		player_.addComponent<ColliderComponent>("player");
		player_.addComponent<RecoilComponent>(colliders_);

		wall_.addComponent<TransformComponent>(ticks_, Point<double> { 300, 300 }, SDL_Point { 20, 300 }, 1);
		wall_.addComponent<SpriteComponent>(*renderer_, "assets/grass.png");
		colliders_.push_back(&wall_.addComponent<ColliderComponent>("wall"));
	}

	~Game()
	{
		playerSpriteSheet_.reset();
		map_.reset();

		renderer_.reset();
		window_.reset();
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
		map_->draw();
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

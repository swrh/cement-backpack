#if !defined(GAME_HPP)
#define GAME_HPP

#include <memory>

#include <SDL.h>

#include "collision.hpp"
#include "components.hpp"
#include "ecs.hpp"
#include "exception.hpp"
#include "map.hpp"
#include "sdl.hpp"

class
Game
{
private:
	Sdl::WindowPtr window;
	Sdl::RendererPtr renderer;

	std::unique_ptr<Map> map;

	Manager manager;
	Entity &player = manager.addEntity();
	Entity &wall = manager.addEntity();

	std::vector<ColliderComponent *> colliders;

	SDL_Event event;

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

		renderer = Sdl::makeRenderer(*window, -1, 0);
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);

		map.reset(new Map("assets/map.txt", *renderer));

		player.addComponent<TransformComponent>(Vector2D(0, 0), Vector2D(19, 34), 2);
		player.addComponent<SpriteComponent>(*renderer, "assets/player/idle.png", 12);
		//player.addComponent<SpriteComponent>(*renderer, "assets/player/running.png", 8);
		//player.addComponent<SpriteComponent>(*renderer, "assets/player/falling.png", 2);
		//player.addComponent<SpriteComponent>(*renderer, "assets/player/ledge-grabbing.png", 6);
		//player.addComponent<SpriteComponent>(*renderer, "assets/player/jumping.png");
		//player.addComponent<SpriteComponent>(*renderer, "assets/player/landing.png");
		player.addComponent<KeyboardController>(event);
		player.addComponent<ColliderComponent>("player");
		player.addComponent<RecoilComponent>(colliders);

		wall.addComponent<TransformComponent>(Vector2D(300, 300), Vector2D(20, 300), 1);
		wall.addComponent<SpriteComponent>(*renderer, "assets/grass.png");
		colliders.push_back(&wall.addComponent<ColliderComponent>("wall"));

		isRunning = true;
	}

	~Game()
	{
		map.reset();

		renderer.reset();
		window.reset();

		if (isInitialized)
			SDL_Quit();
		isInitialized = false;
	}

private:
	bool isInitialized = false;
public:
	bool
	handleEvents()
	{
		bool hadEvent = !!SDL_PollEvent(&event);
		if (hadEvent) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		} else {
			SDL_zero(event);
		}
		return hadEvent;
	}

	void
	update()
	{
		manager.refresh();
		manager.update();
	}

	void
	draw()
	{
		SDL_RenderClear(renderer.get());

		map->draw();
		manager.draw();

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

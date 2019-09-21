#if !defined(PLAYER_HPP)
#define PLAYER_HPP

#include <SDL2/SDL_image.h>

#include "exception.hpp"

class
Player
{
private:
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *texture = nullptr;

public:
	void
	init(SDL_Renderer *renderer_)
	{
		if (!texture) {
			if (!renderer_)
				throw Exception("Player::init: invalid argument received");
			renderer = renderer_;

			SDL_Surface *surface = IMG_Load("assets/guy1idle0.png");
			if (!surface)
				throw Exception("SDL_Surface failed"); // TODO add path info

			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (!texture)
				throw Exception("SDL_CreateTextureFromSurface failed"); // TODO add path info

			SDL_FreeSurface(surface);
		}
	}

	void
	render()
	{
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	}

};

#endif // !defined(PLAYER_HPP)

// vim:set sw=4 ts=4 noet:

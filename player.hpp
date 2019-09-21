#if !defined(PLAYER_HPP)
#define PLAYER_HPP

#include <SDL2/SDL_image.h>

#include "exception.hpp"
#include "texturemanager.hpp"

class
Player
{
private:
	SDL_Renderer *renderer = nullptr;
	SdlTexturePtr texture;

public:
	void
	init(SDL_Renderer *renderer_)
	{
		if (texture)
			throw Exception("Player::init: already initialized");

		if (!renderer_)
			throw Exception("Player::init: invalid argument received");
		renderer = renderer_;

		texture = TextureManager::makeTexture("assets/guy1idle0.png", renderer);
	}

	void
	render()
	{
		SDL_RenderCopy(renderer, texture.get(), nullptr, nullptr);
	}

};

#endif // !defined(PLAYER_HPP)

// vim:set sw=4 ts=4 noet:

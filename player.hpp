#if !defined(PLAYER_HPP)
#define PLAYER_HPP

#include "exception.hpp"
#include "texturemanager.hpp"

class
Player
{
private:
	Sdl::RendererPtr &renderer;
	Sdl::TexturePtr texture;

public:
	Player(Sdl::RendererPtr &renderer_)
	: renderer(renderer_)
	{
		if (!renderer)
			throw Exception("Player: invalid renderer");

		texture = TextureManager::makeTexture("assets/guy1idle0.png", renderer);
	}

	void
	render()
	{
		SDL_RenderCopy(renderer.get(), texture.get(), nullptr, nullptr);
	}

};

#endif // !defined(PLAYER_HPP)

// vim:set sw=4 ts=4 noet:

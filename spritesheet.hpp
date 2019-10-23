#if !defined(SPRITESHEET_HPP)
#define SPRITESHEET_HPP

#include <SDL.h>

#include <vector>

#include "sdl.hpp"

class
SpriteSheet
{
protected:
	SDL_Renderer &renderer;
	sdl::TexturePtr texture;
	Point<unsigned int> textureSize;
	const std::vector<SDL_Rect> &coordinates;

	SpriteSheet(SDL_Renderer &renderer_, const char *path, std::vector<SDL_Rect> &coordinates_)
		: renderer(renderer_), coordinates(coordinates_)
	{
		if (!path)
			throw Exception("SpriteSheet: null path");

		texture = TextureManager::makeTexture(renderer, path);

		int w, h;
		if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h) != 0)
			throw Exception("SDL_QueryTexture failed");

		textureSize = Point<unsigned int> { static_cast<unsigned int>(w), static_cast<unsigned int>(h) };
	}

public:
	const SDL_Rect &
	getRectangle(std::size_t sprite) const
	{
		return coordinates.at(sprite);
	}

	void
	draw(std::size_t sprite, const SDL_Rect &destination)
	{
		TextureManager::render(renderer, *texture, getRectangle(sprite), destination);
	}

};

#endif // !defined(SPRITESHEET_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(GAMEOBJECT_HPP)
#define GAMEOBJECT_HPP

#include "texturemanager.hpp"
#include "sdl.hpp"

class
GameObject
{
private:
	Sdl::RendererPtr &renderer;
	Sdl::TexturePtr texture;
	SDL_Rect sourceRectangle, destinationRectangle;
	Uint32 x, y;

public:
	GameObject(const char *textureSheet, Sdl::RendererPtr &renderer_, Uint32 x_, Uint32 y_)
		: renderer(renderer_)
		, texture(TextureManager::makeTexture(textureSheet, renderer))
		, x(x_)
		, y(y_)
	{
		if (!renderer)
			throw Exception("GameObject: invalid renderer");
	}

	void
	update()
	{
		++x;
		++y;

		sourceRectangle.h = sourceRectangle.w = 32;
		sourceRectangle.x = sourceRectangle.y = 0;

		destinationRectangle.x = x;
		destinationRectangle.y = y;
		destinationRectangle.w = sourceRectangle.w * 2;
		destinationRectangle.h = sourceRectangle.h * 2;
	}

	void
	render()
	{
		SDL_RenderCopy(renderer.get(), texture.get(), &sourceRectangle, &destinationRectangle);
	}

};

#endif // !defined(GAMEOBJECT_HPP)

// vim:set sw=4 ts=4 noet:

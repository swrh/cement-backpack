#if !defined(SDL_HPP)
#define SDL_HPP

#include "exception.hpp"

#include <SDL.h>

class
Sdl
{
public:
	typedef std::shared_ptr<SDL_Renderer> RendererPtr;
	typedef std::shared_ptr<SDL_Surface> SurfacePtr;
	typedef std::shared_ptr<SDL_Texture> TexturePtr;
	typedef std::shared_ptr<SDL_Window> WindowPtr;

public:
	static WindowPtr
	makeWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
	{
		SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (!window)
			throw Exception("SDL_CreateWindow failed");
		return WindowPtr(window, SDL_DestroyWindow);
	}

	static RendererPtr
	makeRenderer(SDL_Window &window, int index, Uint32 flags)
	{
		SDL_Renderer *renderer = SDL_CreateRenderer(&window, -1, 0);
		if (!renderer)
			throw Exception("SDL_CreateRenderer failed");
		return RendererPtr(renderer, SDL_DestroyRenderer);
	}

	static TexturePtr
	makeTexture(SDL_Renderer &renderer, SDL_Surface &surface)
	{
		SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, &surface);
		if (!texture)
			throw Exception("SDL_CreateTextureFromSurface failed");
		return TexturePtr(texture, SDL_DestroyTexture);
	}

};

#endif // !defined(SDL_HPP)

// vim:set sw=4 ts=4 noet:

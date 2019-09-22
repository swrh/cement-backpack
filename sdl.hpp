#if !defined(SDLSTUFF_HPP)
#define SDLSTUFF_HPP

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
	makeRenderer(WindowPtr &window, int index, Uint32 flags)
	{
		SDL_Renderer *renderer = SDL_CreateRenderer(window.get(), -1, 0);
		if (!renderer)
			throw Exception("SDL_CreateRenderer failed");
		return RendererPtr(renderer, SDL_DestroyRenderer);
	}

};

#endif // !defined(SDLSTUFF_HPP)

// vim:set sw=4 ts=4 noet:

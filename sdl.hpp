#if !defined(SDL_HPP)
#define SDL_HPP

#include <SDL.h>

#include "exception.hpp"
#include "memory.hpp"

namespace sdl {

typedef UniquePtr<SDL_Renderer, SDL_DestroyRenderer> RendererPtr;
typedef UniquePtr<SDL_Surface, SDL_FreeSurface> SurfacePtr;
typedef UniquePtr<SDL_Texture, SDL_DestroyTexture> TexturePtr;
typedef UniquePtr<SDL_Window, SDL_DestroyWindow> WindowPtr;

class
Exception
: public ::Exception
{
public:
	Exception(const char *function)
		: ::Exception(std::string(function) + ": " + SDL_GetError())
	{
	}
};

class
Init
{
public:
	Init(Uint32 flags)
	{
		if (SDL_Init(flags) != 0)
			throw Exception("SDL_Init");
	}

	~Init()
	{
		SDL_Quit();
	}
};

inline RendererPtr
makeRenderer(SDL_Window &window, int index, Uint32 flags)
{
	SDL_Renderer *renderer = SDL_CreateRenderer(&window, -1, 0);
	if (!renderer)
		throw Exception("SDL_CreateRenderer");
	return RendererPtr(renderer);
}

inline TexturePtr
makeTexture(SDL_Renderer &renderer, SDL_Surface &surface)
{
	SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, &surface);
	if (!texture)
		throw Exception("SDL_CreateTextureFromSurface");
	return TexturePtr(texture);
}

inline WindowPtr
makeWindow(const char *title, int x, int y, int w, int h, Uint32 flags)
{
	SDL_Window *window = SDL_CreateWindow(title, x, y, w, h, flags);
	if (!window)
		throw Exception("SDL_CreateWindow");
	return WindowPtr(window);
}

}

#endif // !defined(SDL_HPP)

// vim:set sw=4 ts=4 noet:

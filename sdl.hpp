#if !defined(SDL_HPP)
#define SDL_HPP

#include <memory>

#include <SDL.h>

#include "exception.hpp"

namespace sdl {

typedef std::unique_ptr<SDL_Renderer, std::integral_constant<std::decay_t<decltype(SDL_DestroyRenderer)>, SDL_DestroyRenderer>> RendererPtr;
typedef std::unique_ptr<SDL_Surface, std::integral_constant<std::decay_t<decltype(SDL_FreeSurface)>, SDL_FreeSurface>> SurfacePtr;
typedef std::unique_ptr<SDL_Texture, std::integral_constant<std::decay_t<decltype(SDL_DestroyTexture)>, SDL_DestroyTexture>> TexturePtr;
typedef std::unique_ptr<SDL_Window, std::integral_constant<std::decay_t<decltype(SDL_DestroyWindow)>, SDL_DestroyWindow>> WindowPtr;

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

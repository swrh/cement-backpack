#if !defined(TEXTUREMANAGER_HPP)
#define TEXTUREMANAGER_HPP

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "sdl.hpp"
#include "sdlimage.hpp"

class
TextureManager
{
public:
	static Sdl::TexturePtr
	makeTexture(SDL_Renderer &renderer, const char *path)
	{
		return Sdl::makeTexture(renderer, *SdlImage::load(path));
	}

	static void
	render(SDL_Renderer &renderer, SDL_Texture &texture, const SDL_Rect &src, const SDL_Rect &dest)
	{
		SDL_RenderCopy(&renderer, &texture, &src, &dest);
	}

};

#endif // !defined(TEXTUREMANAGER_HPP)

// vim:set sw=4 ts=4 noet:

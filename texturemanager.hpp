#if !defined(TEXTUREMANAGER_HPP)
#define TEXTUREMANAGER_HPP

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "sdl.hpp"

class
TextureManager
{
public:
	static Sdl::TexturePtr
	makeTexture(const char *fileName, Sdl::RendererPtr &renderer)
	{
		Sdl::SurfacePtr surface(IMG_Load(fileName), SDL_FreeSurface);
		if (!surface)
			throw Exception("IMG_Load failed"); // TODO add path info

		// TODO move to Sdl::makeTexture()
		Sdl::TexturePtr texture(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
		if (!texture)
			throw Exception("SDL_CreateTextureFromSurface failed");

		return texture;
	}

};

#endif // !defined(TEXTUREMANAGER_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(TEXTUREMANAGER_HPP)
#define TEXTUREMANAGER_HPP

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "sdl.hpp"

class
TextureManager
{
public:
	static Sdl::TexturePtr
	makeTexture(Sdl::RendererPtr &renderer, const char *path)
	{
		Sdl::SurfacePtr surface(IMG_Load(path), SDL_FreeSurface);
		if (!surface)
			throw Exception("IMG_Load failed"); // TODO add path info

		// TODO move to Sdl::makeTexture()
		Sdl::TexturePtr texture(SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
		if (!texture)
			throw Exception("SDL_CreateTextureFromSurface failed");

		return texture;
	}

	static void
	draw(Sdl::RendererPtr &renderer, const Sdl::TexturePtr &texture, const SDL_Rect &src, const SDL_Rect &dest)
	{
		SDL_RenderCopy(renderer.get(), texture.get(), &src, &dest);
	}

};

#endif // !defined(TEXTUREMANAGER_HPP)

// vim:set sw=4 ts=4 noet:

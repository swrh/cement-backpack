#if !defined(TEXTUREMANAGER_HPP)
#define TEXTUREMANAGER_HPP

#include <memory>

#include <SDL2/SDL.h>

typedef std::shared_ptr<SDL_Surface> SdlSurfacePtr;
typedef std::shared_ptr<SDL_Texture> SdlTexturePtr;

class
TextureManager
{
public:
	static SdlTexturePtr
	makeTexture(const char *fileName, SDL_Renderer *renderer)
	{
		SdlSurfacePtr surface(IMG_Load(fileName), SDL_FreeSurface);
		if (!surface)
			throw Exception("IMG_Load failed"); // TODO add path info

		SdlTexturePtr texture(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);
		if (!texture)
			throw Exception("SDL_CreateTextureFromSurface failed"); // TODO add path info

		return texture;
	}

};

#endif // !defined(TEXTUREMANAGER_HPP)

// vim:set sw=4 ts=4 noet:

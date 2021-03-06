#if !defined(SDLIMAGE_HPP)
#define SDLIMAGE_HPP

#include <SDL_image.h>

#include "sdl.hpp"

namespace sdl {
namespace image {

inline SurfacePtr
load(const char *path)
{
	SDL_Surface *surface = IMG_Load(path);
	if (!surface)
		throw Exception("IMG_Load failed"); // TODO add path info
	return SurfacePtr(surface);
}

}
}

#endif // !defined(SDLIMAGE_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(BOXCOMPONENT_HPP)
#define BOXCOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"
#include "entity.hpp"

class
BoxComponent
: public Component
{
private:
	SDL_Renderer &renderer_;
	SDL_Point size_;

public:
	BoxComponent(Entity *entity, SDL_Renderer &renderer, SDL_Point &&size)
		: Component(entity)
		, renderer_(renderer)
		, size_(size)
	{
	}

	void
	update() override
	{
	}

	void
	draw() override
	{
		SDL_Rect rectangle = {
			0,
			0,
			size_.x,
			size_.y,
		};
		SDL_SetRenderDrawColor(&renderer_, 255, 255, 255, 255);
		SDL_RenderDrawRect(&renderer_, &rectangle);
	}
};

#endif // !defined(BOXCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(RECTANGLECOMPONENT_HPP)
#define RECTANGLECOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"

class
RectangleComponent
: public Component
{
private:
	SDL_Renderer &renderer_;
	const SDL_Rect rectangle_;

public:
	RectangleComponent(Entity *entity, SDL_Renderer &renderer, SDL_Rect &&rectangle)
		: Component(entity)
		, renderer_(renderer)
		, rectangle_(rectangle)
	{
	}

	void
	update() override
	{
	}

	void
	draw() override
	{
		SDL_RenderDrawRect(&renderer_, &rectangle_);
	}
};

#endif // !defined(RECTANGLECOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

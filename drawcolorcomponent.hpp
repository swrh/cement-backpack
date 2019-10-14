#if !defined(DRAWCOLORCOMPONENT_HPP)
#define DRAWCOLORCOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"

class
DrawColorComponent
: public Component
{
private:
	SDL_Renderer &renderer_;
	SDL_Color color_;

public:
	DrawColorComponent(Entity *entity, SDL_Renderer &renderer, SDL_Color &&color)
		: Component(entity)
		, renderer_(renderer)
		, color_(color)
	{
	}

	void
	update() override
	{
	}

	void
	draw() override
	{
		SDL_SetRenderDrawColor(&renderer_, color_.r, color_.g, color_.b, color_.a);
	}
};

#endif // !defined(DRAWCOLORCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

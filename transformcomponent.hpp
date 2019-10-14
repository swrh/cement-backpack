#if !defined(TRANSFORMCOMPONENT_HPP)
#define TRANSFORMCOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"

class
TransformComponent
: public Component
{
private:
	SDL_Point position_ = {}, velocity_ = {};

public:
	TransformComponent(Entity *entity, SDL_Point &&position)
		: Component(entity)
		, position_(position)
	{
	}

	SDL_Point &
	getPosition()
	{
		return position_;
	}

	SDL_Point &
	getVelocity()
	{
		return velocity_;
	}

	void
	update() override
	{
		position_ = SDL_Point {
			position_.x + velocity_.x,
			position_.y + velocity_.y,
		};
	}

	void
	draw() override
	{
	}
};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

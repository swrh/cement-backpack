#if !defined(TRANSFORMCOMPONENT_HPP)
#define TRANSFORMCOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"
#include "point.hpp"
#include "ticks.hpp"

class
TransformComponent
: public Component
{
private:
	const Ticks &ticks_;
	Point<double> position_ = {};
	SDL_Point velocity_ = {};
	double speed_ = 100; // pixels per second

public:
	TransformComponent(Entity *entity, const Ticks &ticks, Point<double> &&position)
		: Component(entity)
		, ticks_(ticks)
		, position_(position)
	{
	}

	Point<double> &
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
		double speed = speed_ * ticks_.diff() / 1000;
		position_.x += speed * velocity_.x;
		position_.y += speed * velocity_.y;
	}

	void
	draw() override
	{
	}
};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

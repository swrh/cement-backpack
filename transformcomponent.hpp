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
	SDL_Point velocity_ = {}, dimensions_ = {};
	unsigned int scale_ = 1;
	double speed_ = 100; // pixels per second
	SDL_Point direction_ { 1, 1 };

public:
	TransformComponent(Entity *entity, const Ticks &ticks, Point<double> &&position, SDL_Point &&dimensions, unsigned int scale)
		: Component(entity)
		, ticks_(ticks)
		, position_(position)
		, dimensions_(dimensions)
		, scale_(scale)
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

	SDL_Point &
	getDimensions()
	{
		return dimensions_;
	}

	unsigned int
	getScale() const
	{
		return scale_;
	}

	SDL_Point &
	getDirection()
	{
		return direction_;
	}

	Point<double>
	predictPosition() const
	{
		// FIXME
		double speed = speed_ * ticks_.delta() / 1000;
		return {
			position_.x + (speed * velocity_.x),
			position_.y + (speed * velocity_.y),
		};
	}

	void
	update() override
	{
		// FIXME
		double speed = speed_ * ticks_.delta() / 1000;
		position_.x += speed * velocity_.x * direction_.x;
		position_.y += speed * velocity_.y * direction_.y;
	}

	void
	draw() override
	{
	}

};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

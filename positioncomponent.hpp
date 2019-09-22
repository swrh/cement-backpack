#if !defined(POSITIONCOMPONENT_HPP)
#define POSITIONCOMPONENT_HPP

#include "components.hpp"

class
PositionComponent
: public Component
{
private:
	Uint32 x = 0, y = 0;

public:
	PositionComponent(Entity *entity_, Uint32 x_, Uint32 y_)
		: Component(entity_)
		, x(x_)
		, y(y_)
	{
	}

	PositionComponent(Entity *entity_)
		: PositionComponent(entity_, 0, 0)
	{
	}

	Uint32
	getX() const
	{
		return x;
	}

	Uint32
	getY() const
	{
		return y;
	}

	void
	update() override
	{
		++x;
		++y;
	}

	void
	setPosition(Uint32 x_, Uint32 y_)
	{
		x = x_;
		y = y_;
	}

};

#endif // !defined(POSITIONCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

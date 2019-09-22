#if !defined(POSITIONCOMPONENT_HPP)
#define POSITIONCOMPONENT_HPP

#include "ecs.hpp"

class
PositionComponent
: public Component
{
private:
	Uint32 x = 0, y = 0;

public:
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
	init() override
	{
		x = y = 0;
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

#if !defined(POSITIONCOMPONENT_HPP)
#define POSITIONCOMPONENT_HPP

#include "components.hpp"
#include "point.hpp"

class
PositionComponent
: public Component
{
private:
	Point point;

public:
	PositionComponent(Entity *entity_, const Point &p)
		: Component(entity_)
		, point(p)
	{
	}

	PositionComponent(Entity *entity_)
		: PositionComponent(entity_, Point(0, 0))
	{
	}

	const Point &
	getPoint() const
	{
		return point;
	}

	Point &
	getPoint()
	{
		return point;
	}

	void
	update() override
	{
		++point;
	}

};

#endif // !defined(POSITIONCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

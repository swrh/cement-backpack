#if !defined(TRANSFORMCOMPONENT_HPP)
#define TRANSFORMCOMPONENT_HPP

#include "components.hpp"
#include "vector2d.hpp"

class
TransformComponent
: public Component
{
private:
	Vector2D position;

public:
	TransformComponent(Entity *entity_, const Vector2D &p)
		: Component(entity_)
		, position(p)
	{
	}

	TransformComponent(Entity *entity_)
		: TransformComponent(entity_, Vector2D(0, 0))
	{
	}

	const Vector2D &
	getPosition() const
	{
		return position;
	}

	Vector2D &
	getPosition()
	{
		return position;
	}

};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

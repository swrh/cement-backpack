#if !defined(TRANSFORMCOMPONENT_HPP)
#define TRANSFORMCOMPONENT_HPP

#include "ecs.hpp"
#include "vector2d.hpp"

class
TransformComponent
: public Component
{
private:
	Vector2D position, velocity;
	unsigned int speed = 1;

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

	const Vector2D &
	getVelocity() const
	{
		return velocity;
	}

	Vector2D &
	getVelocity()
	{
		return velocity;
	}

	void
	update() override
	{
		position += velocity * speed;
	}

};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

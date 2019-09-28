#if !defined(TRANSFORMCOMPONENT_HPP)
#define TRANSFORMCOMPONENT_HPP

#include "ecs.hpp"
#include "vector2d.hpp"

class
TransformComponent
: public Component
{
private:
	Vector2D position, velocity, dimensions = { 32, 32 };
	unsigned int scale = 1, speed = 1;
	Vector2D direction { 1, 1 };

public:
	TransformComponent(Entity *entity_)
		: TransformComponent(entity_, Vector2D(0, 0))
	{
	}

	TransformComponent(Entity *entity_, const Vector2D &pos)
		: Component(entity_)
		, position(pos)
	{
	}

	TransformComponent(Entity *entity_, unsigned int sc)
		: Component(entity_)
		, scale(sc)
	{
	}

	TransformComponent(Entity *entity_, const Vector2D &pos, const Vector2D &dim, unsigned int sc)
		: Component(entity_)
		, position(pos)
		, dimensions(dim)
		, scale(sc)
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

	const Vector2D &
	getDimensions() const
	{
		return dimensions;
	}

	Vector2D &
	getDimensions()
	{
		return dimensions;
	}

	unsigned int
	getScale() const
	{
		return scale;
	}

	Vector2D &
	getDirection()
	{
		return direction;
	}

	Vector2D
	predictPosition() const
	{
		return position + (velocity * speed);
	}

	void
	update() override
	{
		position += velocity * speed * direction;
	}

	void
	draw() override
	{
	}

};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

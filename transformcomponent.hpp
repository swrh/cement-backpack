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
	Point<unsigned int> dimensions = { 32, 32 };
	unsigned int scale = 1, speed = 1;

public:
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

	TransformComponent(Entity *entity_, const Vector2D &pos, const Point<unsigned int> &dim, unsigned int sc)
		: Component(entity_)
		, position(pos)
		, dimensions(dim)
		, scale(sc)
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

	const Point<unsigned int> &
	getDimensions() const
	{
		return dimensions;
	}

	Point<unsigned int> &
	getDimensions()
	{
		return dimensions;
	}

	unsigned int
	getScale() const
	{
		return scale;
	}

	void
	update() override
	{
		position += velocity * speed;
	}

};

#endif // !defined(TRANSFORMCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

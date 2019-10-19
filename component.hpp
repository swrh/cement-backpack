#if !defined(COMPONENT_HPP)
#define COMPONENT_HPP

class Entity;

class
Component
{
public:
	Entity *entity_;

	Component(Entity *entity)
		: entity_(entity)
	{
	}

	virtual
	~Component()
	{
	}

	virtual void update() = 0;
	virtual void draw() = 0;
};

#endif // !defined(COMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(COLLIDERCOMPONENT_HPP)
#define COLLIDERCOMPONENT_HPP

#include <string>

#include "ecs.hpp"
#include "transformcomponent.hpp"

class
ColliderComponent
: public Component
{
private:
	SDL_Rect collider;
	std::string tag;

	TransformComponent *transform = nullptr;

public:
	ColliderComponent(Entity *entity_, const std::string &tag_)
		: Component(entity_)
		, tag(tag_)
	{
		if (!entity->hasComponent<TransformComponent>())
			entity->addComponent<TransformComponent>();
		transform = &entity->getComponent<TransformComponent>();
		update();
	}

	void
	update() override
	{
		collider.x = transform->getPosition().getX();
		collider.y = transform->getPosition().getY();
		collider.w = transform->getDimensions().getX() * transform->getScale();
		collider.h = transform->getDimensions().getY() * transform->getScale();
	}

	const SDL_Rect &
	getCollider() const
	{
		return collider;
	}

};

#endif // !defined(COLLIDERCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

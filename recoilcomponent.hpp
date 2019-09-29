#if !defined(RECOILCOMPONENT_HPP)
#define RECOILCOMPONENT_HPP

#include "collidercomponent.hpp"
#include "ecs.hpp"
#include "transformcomponent.hpp"

class
RecoilComponent
: public Component
{
private:
	TransformComponent *transform = nullptr;
	const std::vector<ColliderComponent *> &colliders;
	ColliderComponent &collider;

	Vector2D lastPosition;

public:
	RecoilComponent(Entity *entity_, const std::vector<ColliderComponent *> &colliders_)
		: Component(entity_)
		, colliders(colliders_)
		, collider(entity->getComponent<ColliderComponent>())
	{
		transform = &entity->getComponent<TransformComponent>();
		update();
	}

	void
	update() override
	{
		transform->getDirection() = Vector2D(1, 1);
		SDL_Rect prediction = collider.predictCollider();
		for (const ColliderComponent *cc : colliders) {
			if (Collision::AABB(prediction, cc->getCollider())) {
				transform->getDirection() *= 0;
				return;
			}
		}
	}

	void
	draw() override
	{
	}

};

#endif // !defined(RECOILCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(RECOILCOMPONENT_HPP)
#define RECOILCOMPONENT_HPP

#include "collidercomponent.hpp"
#include "component.hpp"
#include "transformcomponent.hpp"

class
RecoilComponent
: public Component
{
private:
	const std::vector<ColliderComponent *> &colliders_;
	ColliderComponent &collider_;
	TransformComponent *transform_ = nullptr;

public:
	RecoilComponent(Entity *entity, const std::vector<ColliderComponent *> &colliders)
		: Component(entity)
		, colliders_(colliders)
		, collider_(entity_->getComponent<ColliderComponent>())
		, transform_(&entity_->getComponent<TransformComponent>())
	{
		update();
	}

	void
	update() override
	{
		transform_->getDirection() = SDL_Point { 1, 1 };
		SDL_Rect prediction = collider_.predictCollider();
		for (const ColliderComponent *cc : colliders_) {
			if (Collision::AABB(prediction, cc->getCollider())) {
			transform_->getDirection() = SDL_Point { 0, 0 };
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

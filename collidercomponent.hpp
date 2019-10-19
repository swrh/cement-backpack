#if !defined(COLLIDERCOMPONENT_HPP)
#define COLLIDERCOMPONENT_HPP

#include <string>

#include "component.hpp"
#include "entity.hpp"
#include "transformcomponent.hpp"

class
ColliderComponent
: public Component
{
private:
	SDL_Rect collider_;
	std::string tag_;

	TransformComponent *transform_ = nullptr;

public:
	ColliderComponent(Entity *entity, const std::string &tag)
		: Component(entity)
		, tag_(tag)
	{
		transform_ = &entity_->getComponent<TransformComponent>();
		update();
	}

	const SDL_Rect &
	getCollider() const
	{
		return collider_;
	}

	SDL_Rect
	predictCollider() const
	{
		SDL_Rect collider;
		collider.x = transform_->predictPosition().x;
		collider.y = transform_->predictPosition().y;
		collider.w = transform_->getDimensions().x * transform_->getScale();
		collider.h = transform_->getDimensions().y * transform_->getScale();
		return collider;
	}

	const std::string &
	getTag() const
	{
		return tag_;
	}

	void
	update() override
	{
		collider_.x = transform_->getPosition().x;
		collider_.y = transform_->getPosition().y;
		collider_.w = transform_->getDimensions().x * transform_->getScale();
		collider_.h = transform_->getDimensions().y * transform_->getScale();
	}

	void
	draw() override
	{
	}

};

#endif // !defined(COLLIDERCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

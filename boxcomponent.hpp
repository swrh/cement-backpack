#if !defined(BOXCOMPONENT_HPP)
#define BOXCOMPONENT_HPP

#include <SDL.h>

#include "component.hpp"
#include "entity.hpp"
#include "transformcomponent.hpp"

class
BoxComponent
: public Component
{
private:
	SDL_Point &position_;
	SDL_Renderer &renderer_;
	SDL_Point size_;

public:
	BoxComponent(Entity *entity, SDL_Renderer &renderer, SDL_Point &&size)
		: Component(entity)
		, position_(entity_->getComponent<TransformComponent>().getPosition())
		, renderer_(renderer)
		, size_(size)
	{
	}

	void
	update() override
	{
	}

	void
	draw() override
	{
		SDL_Rect rectangle = {
			position_.x,
			position_.y,
			size_.x,
			size_.y,
		};
		SDL_RenderDrawRect(&renderer_, &rectangle);
	}
};

#endif // !defined(BOXCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(KEYBOARDCOMPONENT_HPP)
#define KEYBOARDCOMPONENT_HPP

#include <SDL.h>

#include "point.hpp"
#include "transformcomponent.hpp"

class
KeyboardComponent
: public Component
{
private:
	SDL_Event &event_;
	SDL_Point &velocity_;

public:
	KeyboardComponent(Entity *entity, SDL_Event &event)
		: Component(entity)
		, event_(event)
		, velocity_(entity_->getComponent<TransformComponent>().getVelocity())
	{
	}

	void
	update() override
	{
		if (event_.type == SDL_KEYDOWN) {
			switch (event_.key.keysym.sym) {
			case SDLK_w:
				--velocity_.y;
				break;
			case SDLK_s:
				++velocity_.y;
				break;
			case SDLK_a:
				--velocity_.x;
				break;
			case SDLK_d:
				++velocity_.x;
				break;
			}
		} else if (event_.type == SDL_KEYUP) {
			switch (event_.key.keysym.sym) {
			case SDLK_w:
				++velocity_.y;
				break;
			case SDLK_s:
				--velocity_.y;
				break;
			case SDLK_a:
				++velocity_.x;
				break;
			case SDLK_d:
				--velocity_.x;
				break;
			}
		}
	}

	void
	draw() override
	{
	}

};

#endif // !defined(KEYBOARDCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

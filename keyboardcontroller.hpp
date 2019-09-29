#if !defined(KEYBOARCONTROLLER_HPP)
#define KEYBOARCONTROLLER_HPP

#include "transformcomponent.hpp"

class
KeyboardController
: public Component
{
private:
	SDL_Event &event;
	TransformComponent *transform;

public:
	KeyboardController(Entity *entity_, SDL_Event &event_)
		: Component(entity_), event(event_)
	{
		transform = &entity->getComponent<TransformComponent>();
	}

	void
	update() override
	{
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				transform->getVelocity() += Vector2D(0, -1);
				break;
			case SDLK_s:
				transform->getVelocity() += Vector2D(0, +1);
				break;
			case SDLK_a:
				transform->getVelocity() += Vector2D(-1, 0);
				break;
			case SDLK_d:
				transform->getVelocity() += Vector2D(+1, 0);
				break;
			}
		} else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				transform->getVelocity() += Vector2D(0, +1);
				break;
			case SDLK_s:
				transform->getVelocity() += Vector2D(0, -1);
				break;
			case SDLK_a:
				transform->getVelocity() += Vector2D(+1, 0);
				break;
			case SDLK_d:
				transform->getVelocity() += Vector2D(-1, 0);
				break;
			}
		}
	}

	void
	draw() override
	{
	}

};

#endif // !defined(KEYBOARCONTROLLER_HPP)

// vim:set sw=4 ts=4 noet:

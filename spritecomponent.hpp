#if !defined(SPRITECOMPONENT_HPP)
#define SPRITECOMPONENT_HPP

#include "components.hpp"
#include "sdl.hpp"
#include "texturemanager.hpp"

class
SpriteComponent
: public Component
{
private:
	SDL_Renderer &renderer;
	Sdl::TexturePtr texture;

	TransformComponent *transform = nullptr;

	SDL_Rect source, destination;

public:
	SpriteComponent(Entity *entity_, SDL_Renderer &renderer_, const char *path)
		: Component(entity_)
		, renderer(renderer_)
	{
		transform = &entity->getComponent<TransformComponent>();

		texture = TextureManager::makeTexture(renderer, path);

		source.x = source.y = 0;
		source.w = transform->getDimensions().getX();
		source.h = transform->getDimensions().getY();
	}

	void
	update() override
	{
		destination.x = transform->getPosition().getX();
		destination.y = transform->getPosition().getY();
		destination.w = transform->getDimensions().getX() * transform->getScale();
		destination.h = transform->getDimensions().getY() * transform->getScale();
	}

	void
	draw() override
	{
		TextureManager::render(renderer, *texture, source, destination);
	}

};

#endif // !defined(SPRITECOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

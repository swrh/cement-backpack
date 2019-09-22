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
	Sdl::RendererPtr &renderer;
	Sdl::TexturePtr texture;

	PositionComponent *position = nullptr;

	SDL_Rect sourceRectangle, destinationRectangle;

public:
	SpriteComponent(Entity *entity_, Sdl::RendererPtr &renderer_)
		: Component(entity_)
		, renderer(renderer_)
	{
		position = &entity->getComponent<PositionComponent>();

		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = sourceRectangle.h = 32;
		destinationRectangle.w = destinationRectangle.h = 32 * 2;
	}

	SpriteComponent(Entity *entity_, Sdl::RendererPtr &renderer_, const char *path)
		: SpriteComponent(entity_, renderer_)
	{
		texture = TextureManager::makeTexture(renderer, path);
	}

	void
	update() override
	{
		destinationRectangle.x = position->getX();
		destinationRectangle.y = position->getY();
	}

	void
	draw() override
	{
		TextureManager::draw(renderer, texture, sourceRectangle, destinationRectangle);
	}

};

#endif // !defined(SPRITECOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

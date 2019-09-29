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

	unsigned int frames = 1;

public:
	SpriteComponent(Entity *entity_, SDL_Renderer &renderer_, const char *path, unsigned int frames_ = 1)
		: Component(entity_)
		, renderer(renderer_)
		, frames(frames_)
	{
		frames = frames_;

		transform = &entity->getComponent<TransformComponent>();

		if (path) {
			texture = TextureManager::makeTexture(renderer, path);

			int w, h;
			if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, &h) != 0)
				throw Exception("SDL_QueryTexture failed");

			transform->getDimensions() = Vector2D(w / frames, h);
		}

		source.x = source.y = 0;
		source.w = transform->getDimensions().getX();
		source.h = transform->getDimensions().getY();
	}

	void
	update() override
	{
		if (frames > 1)
			source.x = source.w * (static_cast<unsigned int>(SDL_GetTicks() / 100) % frames);

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

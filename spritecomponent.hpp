#if !defined(SPRITECOMPONENT_HPP)
#define SPRITECOMPONENT_HPP

#include "component.hpp"
#include "sdl.hpp"
#include "texturemanager.hpp"

class
SpriteComponent
: public Component
{
private:
	SDL_Renderer &renderer_;
	sdl::TexturePtr texture_;

	TransformComponent *transform_ = nullptr;

	SDL_Rect source_, destination_;

public:
	SpriteComponent(Entity *entity, SDL_Renderer &renderer, const char *path)
		: Component(entity)
		, renderer_(renderer)
	{
		transform_ = &entity->getComponent<TransformComponent>();

		texture_ = TextureManager::makeTexture(renderer_, path);

		source_.x = source_.y = 0;
		source_.w = transform_->getDimensions().x;
		source_.h = transform_->getDimensions().y;
	}

	void
	update() override
	{
		destination_.x = transform_->getPosition().x;
		destination_.y = transform_->getPosition().y;
		destination_.w = transform_->getDimensions().x * transform_->getScale();
		destination_.h = transform_->getDimensions().y * transform_->getScale();
	}

	void
	draw() override
	{
		TextureManager::render(renderer_, *texture_, source_, destination_);
	}

};

#endif // !defined(SPRITECOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

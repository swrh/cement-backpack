#if !defined(SPRITESHEETCOMPONENT_HPP)
#define SPRITESHEETCOMPONENT_HPP

#include "transformcomponent.hpp"
#include "spritesheet.hpp"

class
SpriteSheetComponent
: public Component
{
private:
	SDL_Renderer &renderer_;
	SpriteSheet &sheet_;
	const std::vector<std::size_t> *selectedSprites_ = nullptr;
	std::size_t currentSprite_ = 0, baseTick_ = 0, ticksInterval_ = 0;

	TransformComponent *transform_ = nullptr;

	SDL_Rect destination_ = {};

public:
	SpriteSheetComponent(Entity *entity, SDL_Renderer &renderer, SpriteSheet &sheet)
		: Component(entity)
		, renderer_(renderer)
		, sheet_(sheet)
		, transform_(&entity_->getComponent<TransformComponent>())
	{
	}

	void
	selectSprites(const std::vector<std::size_t> &selectedSprites, Uint32 ticksInterval)
	{
		selectedSprites_ = &selectedSprites;
		baseTick_ = static_cast<std::size_t>(SDL_GetTicks());
		ticksInterval_ = ticksInterval;
	}

	void
	update() override
	{
		if (!selectedSprites_)
			throw Exception("SpriteSheetComponent::update: null selectedSprites_");

		currentSprite_ = ((static_cast<std::size_t>(SDL_GetTicks()) - baseTick_) / ticksInterval_) % selectedSprites_->size();
		currentSprite_ = selectedSprites_->operator[](currentSprite_);

		const SDL_Rect &rectangle = sheet_.getRectangle(currentSprite_);

		transform_->getDimensions() = SDL_Point { rectangle.w, rectangle.h };

		destination_ = {
			static_cast<int>(transform_->getPosition().x),
			static_cast<int>(transform_->getPosition().y),
			static_cast<int>(transform_->getDimensions().x * transform_->getScale()),
			static_cast<int>(transform_->getDimensions().y * transform_->getScale()),
		};
	}

	void
	draw() override
	{
		if (!selectedSprites_)
			throw Exception("SpriteSheetComponent::update: null selectedSprites_");

		sheet_.draw(currentSprite_, destination_);
	}

};

#endif // !defined(SPRITESHEETCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

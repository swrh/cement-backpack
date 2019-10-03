#if !defined(SPRITESHEETCOMPONENT_HPP)
#define SPRITESHEETCOMPONENT_HPP

#include "components.hpp"
#include "spritesheet.hpp"

class
SpriteSheetComponent
: public Component
{
private:
	SDL_Renderer &renderer;
	SpriteSheet &sheet;
	const std::vector<std::size_t> *selectedSprites = nullptr;
	std::size_t currentSprite = 0, baseTick = 0, ticksInterval = 0;

	TransformComponent *transform = nullptr;

	SDL_Rect destination = {};

public:
	SpriteSheetComponent(Entity *entity_, SDL_Renderer &renderer_, SpriteSheet &sheet_)
		: Component(entity_)
		, renderer(renderer_)
		, sheet(sheet_)
		, transform(&entity->getComponent<TransformComponent>())
	{
	}

	void
	selectSprites(const std::vector<std::size_t> &selectedSprites_, Uint32 ticksInterval_)
	{
		selectedSprites = &selectedSprites_;
		baseTick = static_cast<std::size_t>(SDL_GetTicks());
		ticksInterval = ticksInterval_;
	}

	void
	update() override
	{
		if (!selectedSprites)
			throw Exception("SpriteSheetComponent::update: null selectedSprites");

		currentSprite = ((static_cast<std::size_t>(SDL_GetTicks()) - baseTick) / ticksInterval) % selectedSprites->size();
		currentSprite = selectedSprites->operator[](currentSprite);

		const SDL_Rect &rectangle = sheet.getRectangle(currentSprite);

		transform->getDimensions() = Vector2D(rectangle.w, rectangle.h);

		destination = {
			static_cast<int>(transform->getPosition().getX()),
			static_cast<int>(transform->getPosition().getY()),
			static_cast<int>(transform->getDimensions().getX() * transform->getScale()),
			static_cast<int>(transform->getDimensions().getY() * transform->getScale()),
		};
	}

	void
	draw() override
	{
		if (!selectedSprites)
			throw Exception("SpriteSheetComponent::update: null selectedSprites");

		sheet.draw(currentSprite, destination);
	}

};

#endif // !defined(SPRITESHEETCOMPONENT_HPP)

// vim:set sw=4 ts=4 noet:

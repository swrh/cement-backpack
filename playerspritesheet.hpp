#if !defined(PLAYERSPRITESHEET_HPP)
#define PLAYERSPRITESHEET_HPP

#include "spritesheet.hpp"

class
PlayerSpriteSheet
: public SpriteSheet
{
private:
	static std::vector<SDL_Rect> &
	getCoordinates()
	{
		static std::vector<SDL_Rect> coordinates = {
			{ (252 / 12) *  0, 0, 252 / 12, 35 },
			{ (252 / 12) *  1, 0, 252 / 12, 35 },
			{ (252 / 12) *  2, 0, 252 / 12, 35 },
			{ (252 / 12) *  3, 0, 252 / 12, 35 },
			{ (252 / 12) *  3, 0, 252 / 12, 35 },
			{ (252 / 12) *  5, 0, 252 / 12, 35 },
			{ (252 / 12) *  6, 0, 252 / 12, 35 },
			{ (252 / 12) *  7, 0, 252 / 12, 35 },
			{ (252 / 12) *  8, 0, 252 / 12, 35 },
			{ (252 / 12) *  9, 0, 252 / 12, 35 },
			{ (252 / 12) * 10, 0, 252 / 12, 35 },
			{ (252 / 12) * 11, 0, 252 / 12, 35 },
		};
		return coordinates;
	}

public:
	PlayerSpriteSheet(SDL_Renderer &renderer)
		: SpriteSheet(renderer, "assets/player/idle.png", getCoordinates())
	{
	}

	static const std::vector<std::size_t> &
	getIdleSprites()
	{
		static const std::vector<std::size_t> v = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
		};
		return v;
	}

};

#endif // !defined(PLAYERSPRITESHEET_HPP)

// vim:set sw=4 ts=4 noet:

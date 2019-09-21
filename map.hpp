#if !defined(MAP_HPP)
#define MAP_HPP

#include <fstream>
#include <vector>

#include "sdl.hpp"

class
Map
{
private:
	Sdl::RendererPtr renderer;
	Sdl::TexturePtr grass, stone, water, wood;
	std::vector<char> data;
	std::size_t width, height;
	SDL_Rect sourceRectangle, destinationRectangle;

public:
	Map(const char *fileName, Sdl::RendererPtr &renderer_)
		: renderer(renderer_)
		, grass(TextureManager::makeTexture("assets/grass.png", renderer))
		, stone(TextureManager::makeTexture("assets/stone.png", renderer))
		, water(TextureManager::makeTexture("assets/water.png", renderer))
		, wood(TextureManager::makeTexture("assets/wood.png", renderer))
	{
		load(fileName);

		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = destinationRectangle.w = 32;
		sourceRectangle.h = destinationRectangle.h = 32;

		destinationRectangle.x = destinationRectangle.y = 0;
	}

	~Map()
	{
	}

	void
	load(const char *fileName)
	{
		height = width = 0;

		std::ifstream infile(fileName);

		std::string line;
		while (infile && std::getline(infile, line)) {
			if (width == 0)
				width = line.size();
			if (width <= 0 || line.size() != width)
				throw Exception("Map::load: line in map file with invalid width");

			++height;
			data.resize(width * height);
			std::copy(line.begin(), line.end(), data.begin() + width * (height - 1));
		}

		if (data.size() <= 0)
			throw Exception("Map::load: empty map");
	}

	void
	draw()
	{
		for (Uint32 x = 0; x < width; ++x) {
			for (Uint32 y = 0; y < height; ++y) {
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;

				char c = data[y * width + x];
				switch (c) {
				case ' ':
					TextureManager::draw(renderer, grass, sourceRectangle, destinationRectangle);
					break;
				case '~':
					TextureManager::draw(renderer, water, sourceRectangle, destinationRectangle);
					break;
				case '@':
					TextureManager::draw(renderer, stone, sourceRectangle, destinationRectangle);
					break;
				case '#':
					TextureManager::draw(renderer, wood, sourceRectangle, destinationRectangle);
					break;
				}
			}
		}
	}

};

#endif // !defined(MAP_HPP)

// vim:set sw=4 ts=4 noet:

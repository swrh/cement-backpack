#if !defined(MAP_HPP)
#define MAP_HPP

#include <fstream>
#include <vector>

#include "matrix.hpp"
#include "sdl.hpp"

class
Map
{
private:
	Sdl::RendererPtr renderer;
	Sdl::TexturePtr grass, stone, water, wood;
	Matrix<char> data;
	SDL_Rect sourceRectangle, destinationRectangle;

public:
	Map(const char *path, Sdl::RendererPtr &renderer_)
		: renderer(renderer_)
		, grass(TextureManager::makeTexture(renderer, "assets/grass.png"))
		, stone(TextureManager::makeTexture(renderer, "assets/stone.png"))
		, water(TextureManager::makeTexture(renderer, "assets/water.png"))
		, wood(TextureManager::makeTexture(renderer, "assets/wood.png"))
	{
		load(path);

		sourceRectangle.x = sourceRectangle.y = 0;
		sourceRectangle.w = destinationRectangle.w = 32;
		sourceRectangle.h = destinationRectangle.h = 32;

		destinationRectangle.x = destinationRectangle.y = 0;
	}

	~Map()
	{
	}

	void
	load(const char *path)
	{
		std::vector<char> vec;
		std::size_t width = 0, height = 0;

		std::ifstream infile(path);

		std::string line;
		while (infile && std::getline(infile, line)) {
			if (width == 0)
				width = line.size();
			if (width <= 0 || line.size() != width)
				throw Exception("Map::load: line in map file with invalid width");

			++height;
			vec.resize(width * height);
			std::copy(line.begin(), line.end(), vec.begin() + width * (height - 1));
		}

		if (vec.size() <= 0)
			throw Exception("Map::load: empty map");

		data = Matrix<char>(width, height, std::move(vec));
	}

	void
	draw()
	{
		for (Uint32 x = 0; x < data.getWidth(); ++x) {
			for (Uint32 y = 0; y < data.getHeight(); ++y) {
				destinationRectangle.x = x * 32;
				destinationRectangle.y = y * 32;

				char c = data(x, y);
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

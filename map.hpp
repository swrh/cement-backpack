#if !defined(MAP_HPP)
#define MAP_HPP

#include <fstream>
#include <vector>

#include "matrix.hpp"
#include "sdl.hpp"
#include "texturemanager.hpp"

class
Map
{
private:
	SDL_Renderer &renderer_;
	sdl::TexturePtr grass_, stone_, water_, wood_;
	Matrix<char> data;
	SDL_Rect source_, destination_;

public:
	Map(const char *path, SDL_Renderer &renderer)
		: renderer_(renderer)
		, grass_(TextureManager::makeTexture(renderer_, "assets/grass.png"))
		, stone_(TextureManager::makeTexture(renderer_, "assets/stone.png"))
		, water_(TextureManager::makeTexture(renderer_, "assets/water.png"))
		, wood_(TextureManager::makeTexture(renderer_, "assets/wood.png"))
	{
		load(path);

		source_.x = source_.y = 0;
		source_.w = destination_.w = 32;
		source_.h = destination_.h = 32;

		destination_.x = destination_.y = 0;
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
				destination_.x = x * 32;
				destination_.y = y * 32;

				char c = data(x, y);
				switch (c) {
				case ' ':
					TextureManager::render(renderer_, *grass_, source_, destination_);
					break;
				case '~':
					TextureManager::render(renderer_, *water_, source_, destination_);
					break;
				case '@':
					TextureManager::render(renderer_, *stone_, source_, destination_);
					break;
				case '#':
					TextureManager::render(renderer_, *wood_, source_, destination_);
					break;
				}
			}
		}
	}

};

#endif // !defined(MAP_HPP)

// vim:set sw=4 ts=4 noet:

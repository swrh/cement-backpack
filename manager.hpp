#if !defined(MANAGER_HPP)
#define MANAGER_HPP

#include <algorithm>
#include <memory>
#include <vector>

#include "entity.hpp"

class
Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void
	update()
	{
		for (auto &e : entities)
			e->update();
	}

	void
	draw()
	{
		for (auto &e : entities)
			e->draw();
	}

	void
	refresh()
	{
		entities.erase(std::remove_if(entities.begin(), entities.end(),
			[](const std::unique_ptr<Entity> &entity) {
				return !entity->isActive();
			}), entities.end());
	}

	Entity &
	addEntity()
	{
		std::unique_ptr<Entity> ptr(new Entity());
		Entity *e = ptr.get();
		entities.emplace_back(std::move(ptr));
		return *e;
	}
};

#endif // !defined(MANAGER_HPP)

// vim:set sw=4 ts=4 noet:

#if !defined(ECS_HPP)
#define ECS_HPP

#include <algorithm>
#include <array>
#include <bitset>
#include <memory>
#include <vector>

#include "exception.hpp"

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId
getComponentTypeId()
{
	static ComponentId lastId = 0;
	return lastId++;
}

template <typename T>
inline ComponentId
getComponentTypeId() noexcept
{
	static ComponentId typeId = getComponentTypeId();
	return typeId;
}

constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component *, MAX_COMPONENTS>;

class
Component
{
public:
	Entity *entity;

	Component(Entity *entity_)
		: entity(entity_)
	{
	}

	virtual
	~Component()
	{
	}

	virtual void update() = 0;
	virtual void draw() = 0;

};

class
Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void
	update()
	{
		for (auto &c : components)
			c->update();
	}

	void
	draw()
	{
		for (auto &c : components)
			c->draw();
	}

	bool
	isActive() const
	{
		return active;
	}

	void
	destroy()
	{
		active = false;
	}

	template <typename T>
	bool
	hasComponent() const
	{
		return componentBitSet[getComponentTypeId<T>()];
	}

	template <typename T, typename... Args>
	T &addComponent(Args &&... args)
	{
		ComponentId id = getComponentTypeId<T>();
		if (componentBitSet[id])
			throw Exception("Entity::addComponent: tried to add already existing component");

		std::unique_ptr<T> ptr(new T(this, std::forward<Args>(args)...));
		T *c = ptr.get();
		components.push_back(std::move(ptr));

		componentArray[id] = c;
		componentBitSet[id] = true;

		return *c;
	}

	template <typename T>
	T &getComponent() const
	{
		ComponentId id = getComponentTypeId<T>();
		if (!componentBitSet[id])
			throw Exception("Entity::getComponent: tried to get nonexistent component");
		return *static_cast<T *>(componentArray[id]);
	}
};

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

#endif // !defined(ECS_HPP)

// vim:set sw=4 ts=4 noet:

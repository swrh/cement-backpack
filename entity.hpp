#if !defined(ENTITY_HPP)
#define ENTITY_HPP

#include <array>
#include <memory>
#include <vector>

#include "component.hpp"
#include "exception.hpp"

class
Entity
{
private:
	using ComponentId = unsigned int;

	static ComponentId
	getComponentTypeId()
	{
		static ComponentId lastId = 0;
		return lastId++;
	}

	template <typename T>
	static ComponentId
	getComponentTypeId() noexcept
	{
		static ComponentId typeId = getComponentTypeId();
		return typeId;
	}

private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	// 32 components max
	std::array<Component *, 32> componentArray = {};

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
		return componentArray[getComponentTypeId<T>()];
	}

	template <typename T, typename... Args>
	T &
	addComponent(Args &&... args)
	{
		ComponentId id = getComponentTypeId<T>();
		if (componentArray[id])
			throw Exception("Entity::addComponent: tried to add already existing component");
		std::unique_ptr<T> ptr(new T(this, std::forward<Args>(args)...));
		T *component = ptr.get();
		components.push_back(std::move(ptr));
		componentArray[id] = component;
		return *component;
	}

	template <typename T>
	T &
	getComponent() const
	{
		Component *component = componentArray[getComponentTypeId<T>()];
		if (!component)
			throw Exception("Entity::getComponent: tried to get nonexistent component");
		return *static_cast<T *>(component);
	}
};

#endif // !defined(ENTITY_HPP)

// vim:set sw=4 ts=4 noet:

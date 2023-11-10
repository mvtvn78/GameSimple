#pragma once
#include<array>
#include<bitset>
#include<vector>
#include<memory>
using ComponnetID = std::size_t;

inline ComponnetID getUniqueComponnet()
{
	static ComponnetID lastID{ 0u };
	return lastID++;
}
template<typename T>
inline ComponnetID getComponnentTypeID()
{
	static ComponnetID typeID{ getUniqueComponnet() };
	return typeID;
}
class Component;
class Manager;
class Entity;
// DECLARE CLASS COMPONNET
class Component
{
public:
	Entity* entity;
	virtual void init() {}
	virtual void updateComponnet() {}
	virtual void drawComponnet() {}
	virtual ~Component() {}
};
constexpr std::size_t MAXCOMPONNET{ 32 };
constexpr std::size_t MAXGROUPS{ 32 };
using ComponnentArray = std::array<Component*, MAXCOMPONNET>;
using ComponentBitSet = std::bitset<MAXCOMPONNET>;
using TypeGroup = std::size_t;
using GroupBitSet = std::bitset<MAXGROUPS>;
//DECLARE CLASS Entity
class Entity
{
private:
	Manager& manager;
	std::vector<std::unique_ptr<Component>> components;
	ComponnentArray componentsArray;
	ComponentBitSet componentsBitset;
	GroupBitSet groupBITSET;
	bool alive = true;
	bool dead = false;
public:
	void setDeadTrue()
	{
		dead = true;
	}
	void setDeadFalse()
	{
		dead = false;
	}
	bool isDead()
	{
		return dead == false;
	}
	Entity(Manager& man) : manager(man) {}
	bool isAlive() const { return alive; }
	void destroy() { alive = false; }
	void update()
	{
		for (auto& c : components)
		{
			c->updateComponnet();
		}
	}
	void draw()
	{
		for (auto& c : components)
		{
			c->drawComponnet();
		}
	}
	bool hasGroup(TypeGroup group)
	{
		return groupBITSET[group];
	}
	void addGroup(TypeGroup group) noexcept;
	void delGroup(TypeGroup group)noexcept
	{
		groupBITSET[group] = false;
	}
	template<typename T> bool hasComponent() noexcept
	{
		return componentsBitset[getComponnentTypeID<T>()];
	}
	template<typename T, typename ...Targs>
	T& addComponent(Targs&& ...mArgs)
	{
		T* c{ new T(std::forward<Targs>(mArgs)...) };
		c->entity = this;
		std::unique_ptr<Component> Uptr{ c };
		components.emplace_back(std::move(Uptr));
		componentsArray[getComponnentTypeID<T>()] = c;
		componentsBitset[getComponnentTypeID<T>()] = true;
		c->init();
		return *c;
	}
	template<typename T>
	T& getComponet() const
	{
		auto ptr{ componentsArray[getComponnentTypeID<T>()] };
		return *static_cast<T*> (ptr);
	}
};
// DECLARE CLASS MANAGER
class Manager
{
private:
	std::vector<std::unique_ptr<Entity> > entities;
	std::array<std::vector<Entity*>, MAXGROUPS> groupentites;
public:
	void managerUPDATE()
	{
		for (auto& e : entities)
		{
			e->update();
		}
	}
	void managerDRAW()
	{
		for (auto& e : entities)
		{
			e->draw();
		}
	}
	void addToGroup(Entity* entity, TypeGroup group)
	{
		groupentites[group].emplace_back(entity);
	}
	void refresh()
	{
		for (auto i{ 0u }; i < MAXGROUPS; i++)
		{
			auto& v{ groupentites[i] };
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* entity)
					{
						return !entity->isAlive() || !entity->hasGroup(i);
					}), std::end(v));
		}
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isAlive();
			})
			, std::end(entities));
	}
	Entity& addEntity()
	{
		Entity* e{ new Entity(*this) };
		std::unique_ptr<Entity> Uptr{ e };
		entities.emplace_back(std::move(Uptr));
		return *e;
	}
	std::vector<Entity*>& getEntityByGroup(TypeGroup group)
	{
		return groupentites[group];
	}
};

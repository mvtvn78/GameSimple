#include"ECS.h"
void Entity::addGroup(TypeGroup group) noexcept
{
	groupBITSET[group] = true;
	manager.addToGroup(this, group);
}
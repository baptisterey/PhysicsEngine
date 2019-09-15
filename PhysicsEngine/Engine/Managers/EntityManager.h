#pragma once
#include <string>
#include <map>
#include <list>

#include "../Base/Entity.h"
#include "../Base/BaseComponent.h"

class EntityManager
{

public:

	static Entity* CreateEntity(std::string name, std::list<BaseComponent*> components);
	static void DestroyEntity(std::string id);

	static const std::map<std::string, Entity*> GetEntities();

	static Entity* GetEntity(std::string entityName);

private:
	static std::map<std::string, Entity*> entities;
};


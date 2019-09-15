#include "EntityManager.h"

std::map<std::string, Entity*> EntityManager::entities = {};

Entity * EntityManager::CreateEntity(std::string name, std::list<BaseComponent*> components)
{
	Entity* entity = new Entity(name);
	for (BaseComponent* component : components) {
		entity->AddComponent(component);
	}
	EntityManager::entities[entity->GetId()] = entity;

	return entity;
}

void EntityManager::DestroyEntity(std::string id)
{
	Entity* entity = EntityManager::entities.at(id);
	if (entity != nullptr) {
		EntityManager::entities.erase(id);

		delete entity;
	}
}

const std::map<std::string, Entity*> EntityManager::GetEntities()
{
	return EntityManager::entities;
}

Entity * EntityManager::GetEntity(std::string entityName)
{
	for (const auto entity : entities) {
		if (entity.second->name == entityName) {
			return entity.second;
		}
	}

	return nullptr;
}

#include "Entity.h"
#include "BaseComponent.h"

Entity::Entity(std::string name) : name(name)
{
	id = Utils::GenerateHex(8);
}


Entity::~Entity()
{
	for (const auto& kv : components) {
		RemoveComponent(kv.first);
	}
}

std::string Entity::GetId()
{
	return id;
}

void Entity::AddComponent(BaseComponent * component)
{
	if (component == nullptr) {
		return;
	}

	components[component->GetId()] = component;
	component->SetOwner(this);
}

void Entity::RemoveComponent(std::string name)
{
	BaseComponent* baseComponent;
	baseComponent = components.at(name);

	if (baseComponent != nullptr) {
		components.erase(name);

		delete baseComponent;
	}
}

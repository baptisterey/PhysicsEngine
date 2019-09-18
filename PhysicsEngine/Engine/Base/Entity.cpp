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

void Entity::RemoveComponent(std::string id)
{
	BaseComponent* baseComponent;
	baseComponent = components.at(id);

	if (baseComponent != nullptr) {
		components.erase(id);

		delete baseComponent;
	}
}

Vector3 Entity::GetPosition()
{
	return position;
}

void Entity::SetPosition(Vector3 & const value)
{
	this->position = value;
}

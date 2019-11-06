#include "Entity.h"
#include "BaseComponent.h"

Entity::Entity(std::string name) : name(name)
{
	id = Utils::GenerateHex(8);

	transform = new Transform();
}

Entity::~Entity()
{
	for (const auto& kv : components) {
		RemoveComponent(kv.first);
	}

	delete transform;
}

std::string Entity::GetId()
{
	return id;
}

void Entity::AddComponent(BaseComponent* component)
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

Transform * Entity::GetTransform()
{
	return transform;
}

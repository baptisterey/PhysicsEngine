#pragma once
#include <string>
#include <map>

#include "../Math/Vector3.h"
class BaseComponent;

class Entity
{
public:
	Entity(std::string name);
	~Entity();

	std::string GetId();

	std::string name;

	void AddComponent(BaseComponent* component);
	void RemoveComponent(std::string id);

	template< class ComponentType >
	ComponentType* GetComponent(std::string id) {
		return components[id];
	}

	template< class ComponentType >
	ComponentType* GetComponentByType() {
		for (auto && component : components) {

			if (ComponentType* t = dynamic_cast<ComponentType*>(component.second)) {
				return t;
			}
		}

		return nullptr;
	}


	Vector3 GetPosition();
	void SetPosition(Vector3& const value);

private:
	std::map<std::string, BaseComponent*> components;
	std::string id;

	Vector3 position;
};


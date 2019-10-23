#include "BaseComponent.h"

BaseComponent::BaseComponent()
{
	id = Utils::GenerateHex(8);
}


BaseComponent::~BaseComponent()
{

}

std::string BaseComponent::GetId()
{
	return id;
}

Entity * BaseComponent::GetOwner()
{
	return owner;
}

void BaseComponent::SetOwner(Entity * ow)
{
	this->owner = ow;
}

bool BaseComponent::IsActive()
{
	return isActive;
}

void BaseComponent::SetActive(bool value)
{
	isActive = value;
}

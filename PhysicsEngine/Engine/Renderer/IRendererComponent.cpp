#include "IRendererComponent.h"

#include "RendererSystem.h"
#include "../Managers/SystemManager.h"

IRendererComponent::IRendererComponent()
{
	RendererSystem* rendererSystem = SystemManager::GetSystemByType<RendererSystem>();
	if (rendererSystem != nullptr) {
		rendererSystem->AddRendererComponent(this);
	}
}


IRendererComponent::~IRendererComponent()
{
	RendererSystem* rendererSystem = SystemManager::GetSystemByType<RendererSystem>();
	if (rendererSystem != nullptr) {
		rendererSystem->RemoveRendererComponent(this);
	}
}

#pragma once
class IPhysicComponent
{
public:
	IPhysicComponent();
	virtual ~IPhysicComponent();

	virtual void Update(float deltaTime) {};
};


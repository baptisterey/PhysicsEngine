#pragma once
class IPhysicComponent
{
public:
	IPhysicComponent();
	~IPhysicComponent();

	virtual void Update(float deltaTime) {};
};


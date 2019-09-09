#pragma once

class ILogicComponent
{
public:

	ILogicComponent();
	~ILogicComponent();

	virtual void Update(float deltaTime) {};
};


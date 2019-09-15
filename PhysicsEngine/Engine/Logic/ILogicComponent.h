#pragma once

class ILogicComponent
{
public:

	ILogicComponent();
	virtual ~ILogicComponent();

	virtual void Update(float deltaTime) {};
};


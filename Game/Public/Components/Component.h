#pragma once
#include "Game/Public/Gamecore/GameCore.h"

class Actor;

class Component
{

friend Actor; //so actor can call component protected functions

public:

	Component() = delete;
	//you need at least one virtual function in order to use dynamic casting
	virtual ~Component();

	//game functions
	


protected:

	//can only create component with owner
	Component(std::weak_ptr<Actor> owner);
	virtual void InitializeComponent();
	virtual void DeinitializeComponent();
	virtual void TickComponent(float dletaSeconds);
	virtual bool CanAddComponent() const; //const - not allwoed to change member variables

	std::weak_ptr<Actor> mOwner;
};

using ComponentList = std::list<std::shared_ptr<Component>>;


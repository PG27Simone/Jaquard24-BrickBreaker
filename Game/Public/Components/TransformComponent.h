#pragma once
#include "Game/Public/Components/Component.h"
#include "Engine/Public/EngineTypes.h"

class TransformComponent : public Component
{
	friend class Actor;

public:

	TransformComponent() = delete;
	

	exVector2 GetLocation() const;
	void SetLocation(const exVector2 inValue);

	virtual bool CanAddComponent() const;

protected:
	TransformComponent(std::weak_ptr<Actor> owner, exVector2 location);
private:

	exVector2 mLocation;

};


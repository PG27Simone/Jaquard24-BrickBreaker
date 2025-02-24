#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

TransformComponent::TransformComponent(std::weak_ptr<Actor> owner, exVector2 location)
	: Component(owner),
	mLocation(location)
{
}

exVector2 TransformComponent::GetLocation() const
{
	return mLocation;
}

void TransformComponent::SetLocation(const exVector2 inValue)
{
	mLocation = inValue;
}

bool TransformComponent::CanAddComponent() const
{
	//check if owner is expried or not
	if (!mOwner.expired())
	{
		//lock makes it shared pointer for iteration - checking if you have a transform component already
		return !mOwner.lock()->FindComponentOfType<TransformComponent>(); //if you have a transform component do not add one so return false
	}
	//else true and add transform component
	return true;
}

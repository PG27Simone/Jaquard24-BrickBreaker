#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

BoxColliderComponent::BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
	PhysicsComponent(owner, velocity, isStatic, isGravityEnabled)
	, mWidth(width)
	, mHeight(height)
{
}

bool BoxColliderComponent::CanAddComponent() const
{
	return true;
}

bool BoxColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent)
{
	if (!otherComponent.expired())
	{

		return otherComponent.lock()->IsCollisionDetectedWithBox(std::dynamic_pointer_cast<BoxColliderComponent>(shared_from_this()));
	}
}

bool BoxColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
{
	exVector2 SelfCenterPos;
	exVector2 OtherCenterPos;


	//get corners of self
	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		//get others corners
		if (!otherComponent.lock()->mOwner.expired())
		{													//transform component of the other component //mowner of other component
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				float otherWidth = otherComponent.lock()->mWidth;
				float otherHeight = otherComponent.lock()->mHeight;

				OtherCenterPos = TransformComp->GetLocation();

				if (SelfCenterPos.x + mWidth >= OtherCenterPos.x &&
					SelfCenterPos.x <= OtherCenterPos.x + otherWidth &&
					SelfCenterPos.y + mHeight >= OtherCenterPos.y &&
					SelfCenterPos.y <= OtherCenterPos.y + otherHeight) {
					return true;
				}

			}
		}
	}
	//you are not colliding

	return false;
}

bool BoxColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
{

	exVector2 SelfCenterPos;
	exVector2 OtherCenterPos;

	//get corners of self
	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransformComp->GetLocation();

		}
	}
	if (!otherComponent.expired())
	{
		//get others corners
		if (!otherComponent.lock()->mOwner.expired())
		{													//transform component of the other component //mowner of other component
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				OtherCenterPos = TransformComp->GetLocation();

				float testX = OtherCenterPos.x;
				float testY = OtherCenterPos.y;

				//convert middle to bottom left
				float cornerX = SelfCenterPos.x - (mWidth / 2);
				float cornerY = SelfCenterPos.y - (mHeight / 2);

				if (OtherCenterPos.x < cornerX)					testX = cornerX;      // test left edge
				else if (OtherCenterPos.x > cornerX + mWidth)	testX = cornerX + mWidth;   // right edge
				if (OtherCenterPos.y < cornerY)					testY = cornerY;      // top edge
				else if (OtherCenterPos.y > cornerY + mHeight)  testY = cornerY + mHeight;   // bottom edge

				// get distance from closest edges
				float distX = OtherCenterPos.x - testX;
				float distY = OtherCenterPos.y - testY;
				float distance = sqrt((distX * distX) + (distY * distY));

				// if the distance is less than the radius, collision!
				if (distance <= otherComponent.lock()->mRadius) {
					mLastHitLocation = OtherCenterPos;
					return true;
				}
			}
		}
	}

	return false;
}

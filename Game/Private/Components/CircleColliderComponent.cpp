#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
	PhysicsComponent(owner, velocity, isStatic, isGravityEnabled)
	, mRadius(radius)
{
}

bool CircleColliderComponent::CanAddComponent() const
{
	//ya and you can add multiple so true
	return true;
}

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent)
{
	if (!otherComponent.expired())
	{
		return otherComponent.lock()->IsCollisionDetectedWithCircle(std::dynamic_pointer_cast<CircleColliderComponent>(shared_from_this()));
	}
}

bool CircleColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
{

	exVector2 SelfCenterPos;
	exVector2 OtherCenterPos;

	if (!mOwner.expired()) 
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		//finding transform components of both to find center point 
		//you do otherComponent.lock() to get other component since u cant access it since its a weak ptr
		//get weak ptrs owner
		if (!otherComponent.lock()->mOwner.expired())
		{													//transform component of the other component //mowner of other component
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				OtherCenterPos = TransformComp->GetLocation();

				//vector between two center positions
				exVector2 Length = SelfCenterPos - OtherCenterPos;
				float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y);
				//sum of two radius
				float RadiusSum = mRadius + otherComponent.lock()->mRadius;
				//this means you are colliding
				return DistanceSquared < (RadiusSum * RadiusSum);
			}
		}
	}
	//you are not colliding
	return false;
}

bool CircleColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
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
				float width = otherComponent.lock()->mWidth;
				float height = otherComponent.lock()->mHeight;

				//convert middle to bottom left
				float boxX = OtherCenterPos.x - (width / 2);
				float boxY = OtherCenterPos.y - (height / 2);

				float testX = SelfCenterPos.x;
				float testY = SelfCenterPos.y;

				if (SelfCenterPos.x < boxX)					testX = boxX;      // test left edge
				else if (SelfCenterPos.x > boxX + width)	testX = boxX + width;   // right edge
				if (SelfCenterPos.y < boxY)					testY = boxY;      // top edge
				else if (SelfCenterPos.y > boxY + height)   testY = boxY + height;   // bottom edge

				// get distance from closest edges
				float distX = SelfCenterPos.x - testX;
				float distY = SelfCenterPos.y - testY;
				float distance = sqrt((distX * distX) + (distY * distY));

				// if the distance is less than the radius, collision!
				if (distance <= mRadius) {
					// store the hit location
					mLastHitLocation = OtherCenterPos;  
					if (const std::shared_ptr<BoxRenderComponent> RenderComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<BoxRenderComponent>())
					{

						if (RenderComp->GetColliderID() == 1) {
							isPlayer = true;
						}
						else {
							isPlayer = false;
						}
				
					
	
						return true;
					}
					
				}
			}
		}
	}

	return false;
}

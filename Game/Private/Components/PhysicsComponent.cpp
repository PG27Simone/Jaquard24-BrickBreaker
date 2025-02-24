#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Singletons/PhysicsEngine.h"

void PhysicsComponent::doPhysics()
{
	if (!mOwner.expired())
	{
		if (mIsStatic)
		{
			return;
		}
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			exVector2 NewPosition = TransformComp->GetLocation() + mVelocity;
			//add extra logic if you have gravity system @TODO
			TransformComp->SetLocation(NewPosition);
		}
	}
}

//optional parameters means even if u dont pass them they will be set to smth
PhysicsComponent::PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity, bool isStatic, bool isGravityEnabled) : Component(owner)
,mVelocity(velocity)
,mIsStatic(isStatic)
,mIsGravityEnabled(isGravityEnabled)
{

}

void PhysicsComponent::InitializeComponent()
{
	PHYSICS_ENGINE.AddPhysicsComponent(weak_from_this());
}

bool PhysicsComponent::CanAddComponent() const
{
	return false;
}

void PhysicsComponent::ListenForCollision(CollisionEventSignature& delegateToAdd)
{
	mCollisionEvents.emplace_back(delegateToAdd);
}

void PhysicsComponent::StopListeningForCollision(CollisionEventSignature& delegateToRemove)
{
	mCollisionEvents.erase(std::remove_if(mCollisionEvents.begin(), mCollisionEvents.end(),
		[delegateToRemove](const CollisionEventSignature& collisionEventIterator)->bool
		{
			return delegateToRemove.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>() ==
				collisionEventIterator.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>();
		}), mCollisionEvents.end());
}

void PhysicsComponent::BroadcastCollisionEvents(std::weak_ptr<Actor>& otherActor, const exVector2 hitLocation)
{

	for (CollisionEventSignature& event : mCollisionEvents)
	{
		event(otherActor, hitLocation);
	}
	actor = otherActor;
}

void PhysicsComponent::CollisionResolution()
{
	
	if (!mOwner.expired())
	{
		auto owner = mOwner.lock();
		auto squareComp = owner->FindComponentOfType<BoxRenderComponent>();

		//if it has a box collider it should not move
		if(squareComp)
		{
			return; // not the ball, don't apply collision resolution to player
		}
		else if (const std::shared_ptr<TransformComponent> TransformComp = owner->FindComponentOfType<TransformComponent>())
		{
			const std::shared_ptr<TransformComponent> actorTransform = actor.lock()->FindComponentOfType<TransformComponent>();
			// get player's center position
			exVector2 playerCenter = TransformComp->GetLocation();
			//get box location
			exVector2 boxCenter = actorTransform->GetLocation();
			// calculate how far from center the ball hit using the stored hit location
			float distanceFromCenter = mLastHitLocation.x - playerCenter.x;

			// Normalize the distance to create a factor between -1 and 1
			float normalizedDistance = distanceFromCenter / 50.0f;

			// calculate new velocities
			// Use a mix of the current direction and the hit position to determine new direction
			float newX = normalizedDistance * 0.8f; // 80% of speed for horizontal movement
			float newY = (mVelocity.y > 0.0f ? -mVelocity.y : (mVelocity.y*-1)); //opposite direction but same speed for vertical

			// Set the new velocity
			//angle if player
			if (isPlayer) {
				mVelocity.x = -newX;
				mVelocity.y = newY;
				isPlayer = false;
			}
			else {
				//bounce normally if not player

				//left border of box collision
				if ((playerCenter.x > boxCenter.x && playerCenter.y < boxCenter.y))
				{
					mVelocity.x = -mVelocity.x;
				}
				//right border box collision
				else if ((playerCenter.x < boxCenter.x && playerCenter.y < boxCenter.y))
				{
					mVelocity.x = -mVelocity.x;
				}
				//top border collision
				else if ((playerCenter.x < boxCenter.x && playerCenter.y > boxCenter.y) || (playerCenter.x > boxCenter.x && playerCenter.y > boxCenter.y))
				{
					mVelocity.y = -mVelocity.y;
				}
				else {

					mVelocity.x = -mVelocity.x;
					mVelocity.y = -mVelocity.y;
				}

			}
			
		}
	}

}

void PhysicsComponent::SetVelocity(const exVector2 inVelocity)
{
	mVelocity = inVelocity;
}

exVector2 PhysicsComponent::GetVelocity() const
{
	return mVelocity;
}

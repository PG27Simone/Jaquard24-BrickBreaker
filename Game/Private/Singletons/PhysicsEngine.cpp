#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sPhysicsEngineInstance = nullptr;

PhysicsEngine::~PhysicsEngine()
{
	ClearInvalidPhysicsComponents();
}

void PhysicsEngine::PhysicsUpdate(const float& deltaSeconds)
{
	ClearInvalidPhysicsComponents();

	//size t is unsigned int since we dont need negative numbers
	for (size_t index1 = 0; index1 < mPhysicsComponents.size(); ++index1)
	{
		auto firstPhysicsCompIter = mPhysicsComponents.begin();
		std::advance(firstPhysicsCompIter, index1);

		if (!firstPhysicsCompIter->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsCompToCheck = firstPhysicsCompIter->lock();

			for (size_t index2 = index1 + 1; index2 < mPhysicsComponents.size(); ++index2)
			{
				auto secondtPhysicsCompIter = mPhysicsComponents.begin();
				std::advance(secondtPhysicsCompIter, index2);

				if (!secondtPhysicsCompIter->expired())
				{
					const std::shared_ptr<PhysicsComponent> secondPhysicsCompToCheck = secondtPhysicsCompIter->lock();

					if (firstPhysicsCompToCheck->IsCollisionDetected(*secondtPhysicsCompIter))
					{
						// The second component will have the hit location set during collision detection
						exVector2 hitLocation = secondtPhysicsCompIter->lock()->mLastHitLocation;

						firstPhysicsCompToCheck->BroadcastCollisionEvents(secondPhysicsCompToCheck->mOwner, hitLocation);
						secondPhysicsCompToCheck->BroadcastCollisionEvents(firstPhysicsCompToCheck->mOwner, hitLocation);
						
						firstPhysicsCompToCheck->CollisionResolution();
						secondPhysicsCompToCheck->CollisionResolution();
					}
				}
			}

			firstPhysicsCompToCheck->doPhysics();
		}
	}

	//for (std::weak_ptr<PhysicsComponent>& currentPhysicsComponentIterator : mPhysicsComponents)
	//{
	//	if (!currentPhysicsComponentIterator.expired())
	//	{

	//	}
	//}
}

void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponents.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicsComponents()
{
}

PhysicsEngine::PhysicsEngine()
{
	if (mPhysicsComponents.empty()) {
		return;
	}

	mPhysicsComponents.erase(std::remove_if(mPhysicsComponents.begin(), mPhysicsComponents.end(),
		//lamda - true or false
		[](const std::weak_ptr<PhysicsComponent>& componentToCheck)->bool //(dont need to write ->bool but can write it to see what its returning
		{
			//if weak ptr is expired that means remove it if not do not remove it
			return componentToCheck.expired();
		}), mPhysicsComponents.end());
}

#pragma once
#include "Game/Public/Gamecore/GameCore.h"
#define PHYSICS_ENGINE PhysicsEngine::GetInstance()

class PhysicsComponent;

class PhysicsEngine
{

public:

	static PhysicsEngine& GetInstance()
	{
		if (!sPhysicsEngineInstance)
		{
			sPhysicsEngineInstance.reset(new PhysicsEngine());
		}
		return *sPhysicsEngineInstance;
	}

	~PhysicsEngine();

	void PhysicsUpdate(const float& deltaSeconds);

#pragma region Listeners

	void AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd);
	void ClearInvalidPhysicsComponents();

#pragma endregion


private:
	PhysicsEngine();

	PhysicsEngine(const PhysicsEngine& otherEngine) = delete;
	PhysicsEngine& operator=(const PhysicsEngine& otherEngine) = delete;

	std::list < std::weak_ptr<PhysicsComponent>> mPhysicsComponents;

	static std::unique_ptr<PhysicsEngine> sPhysicsEngineInstance;

};


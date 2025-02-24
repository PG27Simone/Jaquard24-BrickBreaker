#pragma once
#include "Component.h"
#include "Engine/Public/EngineTypes.h"

class Actor;
class PhysicsEngine;
class CircleColliderComponent;
class BoxColliderComponent;



//this is the signature for collision events {change it per your requirments}
//can add parameters like velocity, angle, etc
//exVector2 parameter is where collision happened  
using CollisionEventSignature = std::function<void(std::weak_ptr<Actor>, const exVector2&)>;

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{

	friend Actor;
	friend PhysicsEngine;

public:

	PhysicsComponent() = delete;
	virtual void doPhysics();



	virtual void CollisionResolution();

	virtual bool IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent) = 0;
	virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) = 0;



protected:

	//bool for static and grav is fine cause it will convert to 0 or 1
	PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity = {0.0f, 0.0f}, bool isStatic = false, bool isGravityEnabled = false);

	virtual void InitializeComponent() override;
	virtual bool CanAddComponent() const override;

#pragma region Collision

	//const will ensure u dont change anything internally
	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent) = 0;
	//if u have box
	//virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) const = 0;
	void BroadcastCollisionEvents(std::weak_ptr<Actor>& otherActor, const exVector2 hitLocation);

	exVector2 mLastHitLocation;  // Add this to store the hit 

	//for different collision with different boxes
	bool isPlayer; //collider id = 1

	std::weak_ptr<Actor> actor;

public:
	void ListenForCollision(CollisionEventSignature& delegateToAdd);
	void StopListeningForCollision(CollisionEventSignature& delegateToRemove);

#pragma endregion

	void SetVelocity(const exVector2 inVelocity);
	exVector2 GetVelocity() const;

private:

	unsigned int mIsStatic : 1;
	unsigned int mIsGravityEnabled : 1;
	exVector2 mVelocity;



	std::list<CollisionEventSignature> mCollisionEvents;

};


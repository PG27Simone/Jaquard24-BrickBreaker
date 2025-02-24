#pragma once
#include "PhysicsComponent.h"

class CircleColliderComponent : public PhysicsComponent
{

	friend class Actor;
	friend class BoxColliderComponent;

public:

	CircleColliderComponent() = delete;

protected:


	CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity, bool isStatic = false, bool isGravityEnabled = false);

	virtual bool CanAddComponent() const override;
	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent) override;
	virtual bool IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent) override;
	virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) override;



private:

	float mRadius;

};


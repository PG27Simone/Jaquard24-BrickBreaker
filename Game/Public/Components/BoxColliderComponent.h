#pragma once
#include "PhysicsComponent.h"

class BoxColliderComponent : public PhysicsComponent
{

friend class Actor;
friend class CircleColliderComponent;

public:

	BoxColliderComponent() = delete;
	bool IsPointInside(int x, int y) const;


protected:


	BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic = false, bool isGravityEnabled = false);

	virtual bool CanAddComponent() const override;
	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent> otherComponent) override;
	virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) override;
	virtual bool IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent) override;



private:

	float mHeight;
	float mWidth;

};


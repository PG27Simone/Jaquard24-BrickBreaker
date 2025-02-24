#pragma once
#include "RenderComponent.h"

class BoxRenderComponent : public RenderComponent
{

	friend class  Actor;

public:

	BoxRenderComponent() = delete;
	virtual void Render(exEngineInterface* renderInterface) override;

	int GetColliderID()
	{
		return mColliderID;
	}

protected:

	BoxRenderComponent(std::weak_ptr<Actor> owner, float width, float height, exColor color = { 255,0,0,255 }, int colliderID = 0, exVector2 positionOffset = { 0.0f,0.0f }, int layerID = 1);

	virtual bool CanAddComponent() const override;

private:
	float mHeight;
	float mWidth;
	int mColliderID;


};


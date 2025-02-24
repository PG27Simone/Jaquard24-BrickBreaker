#pragma once
#include "RenderComponent.h"
class CircleRenderComponent : public RenderComponent
{

	friend class  Actor;

public:

	CircleRenderComponent() = delete;
	virtual void Render(exEngineInterface* renderInterface) override;

protected:

	CircleRenderComponent(std::weak_ptr<Actor> owner, float radius, exColor color = { 255,0,0,255 }, exVector2 positionOffset = { 0.0f,0.0f }, int layerID = 1);

	virtual bool CanAddComponent() const override;

private :

	float mRadius; //TODO: write getter and setter for mRadius

};


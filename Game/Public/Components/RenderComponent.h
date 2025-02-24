#pragma once
#include "Component.h"
#include "Engine/Public/EngineTypes.h"


class exEngineInterface;

class RenderComponent : public Component, public std::enable_shared_from_this<RenderComponent>
{
	friend class Actor;

public:

	RenderComponent() = delete;
	virtual void Render(exEngineInterface* renderInterface) = 0;
	void SetColor(const exColor newColor);
	exColor GetColor() const;

protected:

	RenderComponent(std::weak_ptr<Actor> owner, exColor color = { 125,125,125,255 }, exVector2 renderOffset = {0.0f, 0.0f}, int layerID = 0); //= makes it optional parameter so if you dont put one in it'll input this color

	virtual void InitializeComponent() override;
	virtual bool CanAddComponent() const override;

	exColor mColor;
	exVector2 mRenderOffset;
	int mLayerId;

private:

};


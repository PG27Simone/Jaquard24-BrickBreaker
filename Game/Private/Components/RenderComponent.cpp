#include "Game/Public/Components/RenderComponent.h"
#include "Game/Public/Singletons/RenderEngine.h"

void RenderComponent::InitializeComponent()
{
	//weak from this is a function that allows you to creat weak ptr from myself
	RENDER_ENGINE.AddRenderComponent(weak_from_this());
}

void RenderComponent::SetColor(const exColor newColor)
{
	mColor = newColor;
}

exColor RenderComponent::GetColor() const
{
	return mColor;
}

RenderComponent::RenderComponent(std::weak_ptr<Actor> owner, exColor color, exVector2 renderOffset, int layerID) : Component(owner)
, mColor(color)
, mRenderOffset(renderOffset)
, mLayerId(layerID)
{

}

bool RenderComponent::CanAddComponent() const
{
	return false;
}

#include "Game/Public/Components/CircleRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

CircleRenderComponent::CircleRenderComponent(std::weak_ptr<Actor> owner, float radius, exColor color, exVector2 positionOffset, int layerID) :
	RenderComponent(owner, color, positionOffset, layerID)
	, mRadius(radius)
{
}

void CircleRenderComponent::Render(exEngineInterface* renderInterface)
{
	if (renderInterface) //checking for validity
	{
		exVector2 CenterPos = { 0.0f,0.0f };
		if (!mOwner.expired())
		{
			if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				CenterPos = OwningTransformComp->GetLocation();
			}
		}
		CenterPos += mRenderOffset;
		renderInterface->DrawCircle(CenterPos, mRadius, mColor, mLayerId);
	}
}

bool CircleRenderComponent::CanAddComponent() const
{
	return true;
}

#include "Game/Public/Components/BoxRenderComponent.h"
#include "Engine/Public/EngineInterface.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

BoxRenderComponent::BoxRenderComponent(std::weak_ptr<Actor> owner, float width, float height, exColor color, int colliderID, exVector2 positionOffset, int layerID) :
	RenderComponent(owner, color, positionOffset, layerID)
	, mWidth(width)
	, mHeight(height)
	, mColliderID(colliderID)
{
}


void BoxRenderComponent::Render(exEngineInterface* renderInterface)
{
	if (renderInterface) //checking for validity
	{
		exVector2 Corner1 = { 0.0f,0.0f };
		exVector2 Corner2 = { 0.0f,0.0f };
		if (!mOwner.expired())
		{
			if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				Corner1 = OwningTransformComp->GetLocation() - exVector2{mWidth/2, mHeight/2};
				Corner2 = OwningTransformComp->GetLocation() + exVector2{mWidth/2, mHeight/2};
			}
		}

		
		renderInterface->DrawBox(Corner1, Corner2, mColor, mLayerId);
	}
}


bool BoxRenderComponent::CanAddComponent() const
{
	return true;
}

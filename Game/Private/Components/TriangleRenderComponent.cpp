#include "Game/Public/Components/TriangleRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Engine/Public/EngineInterface.h"

TriangleRenderComponent::TriangleRenderComponent(std::weak_ptr<Actor> owner, float base, float height, exColor color, exVector2 positionOffset, int layerID)
    : RenderComponent(owner, color, positionOffset, layerID)
    , mBase(base)
    , mHeight(height)
{
}

bool TriangleRenderComponent::CanAddComponent() const
{
    return true;
}

void TriangleRenderComponent::Render(exEngineInterface* renderInterface)
{
    if (renderInterface)
    {
        exVector2 CenterPos = { 0.0f, 0.0f };

        if (!mOwner.expired())
        {
            if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
            {
                CenterPos = OwningTransformComp->GetLocation();
            }
        }

        CenterPos += mRenderOffset;

        // Define the three vertices of the triangle
        exVector2 PointA = { CenterPos.x, CenterPos.y - mHeight * 0.5f };  // Top vertex
        exVector2 PointB = { CenterPos.x - mBase * 0.5f, CenterPos.y + mHeight * 0.5f }; // Bottom left vertex
        exVector2 PointC = { CenterPos.x + mBase * 0.5f, CenterPos.y + mHeight * 0.5f }; // Bottom right vertex

        renderInterface->DrawLine(PointA, PointB, mColor, mLayerId);
        renderInterface->DrawLine(PointB, PointC, mColor, mLayerId);
        renderInterface->DrawLine(PointC, PointA, mColor, mLayerId);
    }
}

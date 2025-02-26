#include "Game/Public/Components/StarRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Engine/Public/EngineInterface.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846

StarRenderComponent::StarRenderComponent(std::weak_ptr<Actor> owner, float size, exColor color, exVector2 positionOffset, int layerID) :
    RenderComponent(owner, color, positionOffset, layerID)
    , mSize(size)
    , mBaseSize(size)
{
    mRotationAngle = 0.0f;
}

bool StarRenderComponent::CanAddComponent() const
{
	return true;
}

void StarRenderComponent::Render(exEngineInterface* renderInterface)
{
    if (!renderInterface) return;

    exVector2 center = { 0.0f, 0.0f };
    if (!mOwner.expired()) {
        if (auto owningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>()) {
            center = owningTransformComp->GetLocation();
        }
    }
    center += mRenderOffset;

    std::vector<exVector2> points = CalculateStarPoints(center, mSize);

    for (size_t i = 0; i < points.size(); i++) {
        size_t nextIndex = (i + 2) % points.size(); // Draw every second point to form a star
        renderInterface->DrawLine(points[i], points[nextIndex], mColor, mLayerId);
    }

    mRotationAngle += M_PI / 180.0f;

    mSize = mBaseSize + mBaseSize * 0.2f * sin(mRotationAngle);
}

std::vector<exVector2> StarRenderComponent::CalculateStarPoints(const exVector2& center, float size) const
{
    std::vector<exVector2> points;
    const float angleIncrement = M_PI / 5.0f; // 36 degrees per step
    for (int i = 0; i < 10; i++) {
        float angle = i * angleIncrement * 2;
        float radius = (i % 2 == 0) ? size : size * 0.4f; // Alternate inner and outer points
        exVector2 point = { center.x + radius * cos(angle), center.y + radius * sin(angle) };
        points.push_back(RotatePoint(point, center, mRotationAngle)); // Rotate each point
    }

    return points;
    
}

exVector2 StarRenderComponent::RotatePoint(const exVector2& point, const exVector2& center, float angle) const
{
    float s = sin(angle);
    float c = cos(angle);

    // Translate point back to origin
    exVector2 temp = { point.x - center.x, point.y - center.y };

    // Rotate point
    float xnew = temp.x * c - temp.y * s;
    float ynew = temp.x * s + temp.y * c;

    // Translate point back
    return { xnew + center.x, ynew + center.y };
}

#endif
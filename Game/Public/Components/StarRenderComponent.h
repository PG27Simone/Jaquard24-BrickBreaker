#pragma once
#include "RenderComponent.h"

#include <vector>
#include <cmath>

class StarRenderComponent : public RenderComponent
{
    friend class Actor;

public:
    StarRenderComponent() = delete;
    virtual void Render(exEngineInterface* renderInterface) override;

protected:

    StarRenderComponent(std::weak_ptr<Actor> owner, float size, exColor color = { 255,255,0,255 }, exVector2 positionOffset = { 0.0f,0.0f }, int layerID = 1);

    virtual bool CanAddComponent() const override;

private:
    float mSize;
    float mBaseSize;
    float mRotationAngle;
    std::vector<exVector2> CalculateStarPoints(const exVector2& center, float size) const;
    exVector2 RotatePoint(const exVector2& point, const exVector2& center, float angle) const;
};

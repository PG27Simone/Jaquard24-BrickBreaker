#pragma once
#include "RenderComponent.h"

class TriangleRenderComponent : public RenderComponent
{
    friend class Actor;

public:
    TriangleRenderComponent() = delete;
    virtual void Render(exEngineInterface* renderInterface) override;

protected:
    TriangleRenderComponent(std::weak_ptr<Actor> owner, float base, float height, exColor color = { 255, 255, 0, 255 },
        exVector2 positionOffset = { 0.0f, 0.0f }, int layerID = 1);

    virtual bool CanAddComponent() const override;

private:
    float mBase;
    float mHeight;
};

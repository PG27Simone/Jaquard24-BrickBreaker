#pragma once

#include "Game/Public/Components/RenderComponent.h"
#include "Engine/Public/EngineTypes.h"
#include <string>

class exEngineInterface;

class TextRenderComponent : public RenderComponent
{
public:

    TextRenderComponent(std::weak_ptr<Actor> owner, const std::string& text, exColor color = { 255, 255, 255, 255 }, exVector2 renderOffset = { 0.0f, 0.0f }, int layerID = 0);

    void Render(exEngineInterface* renderInterface) override;

    void SetText(const std::string& text);
    std::string GetText() const;

    virtual bool CanAddComponent() const override;

private:
    std::string mText;
};
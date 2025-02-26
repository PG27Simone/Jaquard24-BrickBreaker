#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Engine/Public/EngineInterface.h"

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner, const std::string& text, exColor color, exVector2 renderOffset, int layerID)
    : RenderComponent(owner, color, renderOffset, layerID), mText(text)
{
}

bool TextRenderComponent::CanAddComponent() const
{
    return true;
}


void TextRenderComponent::Render(exEngineInterface* renderInterface)
{
    if (auto owner = mOwner.lock())
    {
        auto transform = owner->FindComponentOfType<TransformComponent>();
        if (transform && renderInterface)
        {
            exVector2 position = transform->GetLocation() + mRenderOffset;
            renderInterface->DrawText(0, position, mText.c_str(), mColor, mLayerId);  // Font ID = 0 for now
        }
    }
}

void TextRenderComponent::SetText(const std::string& text)
{
    mText = text;
}

std::string TextRenderComponent::GetText() const
{
    return mText;
}


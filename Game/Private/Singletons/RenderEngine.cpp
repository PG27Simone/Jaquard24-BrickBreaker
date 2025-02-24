#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr<RenderEngine> RenderEngine::sRenderEngineInstance = nullptr;

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
	ClearInvalidRenderComponents();
}

void RenderEngine::Render(exEngineInterface* engineInterface)
{
	//do not want to render anything that is invalid
	ClearInvalidRenderComponents();

	for (std::weak_ptr<RenderComponent>& currentRenderComponentIterator : mRenderComponents)
	{
		if (!currentRenderComponentIterator.expired())
		{
			//lock cinverts to shared ptr for this specific instance since we cant call a function on a weak ptr since it doesnt have ownership
			currentRenderComponentIterator.lock()->Render(engineInterface);
		}
	}
}

void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponents()
{
	//u are not owning it so you can check if owner is valid or not
	//remove if returns a list of everything that needs to be erased
	//erase function takes in iterators you waant to remove and filter out with remove if function
	mRenderComponents.erase(std::remove_if(mRenderComponents.begin(), mRenderComponents.end(),
		//lamda - true or false
		[](const std::weak_ptr<RenderComponent>& componentToCheck)->bool //(dont need to write ->bool but can write it to see what its returning
		{
			//if weak ptr is expired that means remove it if not do not remove it
			return componentToCheck.expired();
		}), mRenderComponents.end());
}


#pragma once
#include "Game/Public/Gamecore/GameCore.h"
//#include "/Public/EngineTypes.h"

#define RENDER_ENGINE RenderEngine::GetInstance()

class RenderComponent;
class exEngineInterface;

class RenderEngine
{

public:

	//adding static in getter to make sure we only have one instance of this object
	static RenderEngine& GetInstance()
	{
		//s for static
		if (!sRenderEngineInstance)
		{
			//.reset reallocates memory block to this new pointer
			//new RenderEngine() creates new memory block
			sRenderEngineInstance.reset(new RenderEngine());
		}
		//return alias of pointer
		return *sRenderEngineInstance;
	}

	~RenderEngine();

	void Render(exEngineInterface* engineInterface);

#pragma region Listeners

	//weak ptr cause you dont want ownership
	void AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd);
	void ClearInvalidRenderComponents();


#pragma endregion


private:

	RenderEngine();

	//making this is singleton
	RenderEngine(const RenderEngine& otherEngine) = delete;
	RenderEngine& operator=(const RenderEngine& otherEngine) = delete;

	std::list<std::weak_ptr<RenderComponent>> mRenderComponents;

	static std::unique_ptr<RenderEngine> sRenderEngineInstance;

};


#pragma once
#include "Game/Public/Components/ComponentTypes.h"


class Actor : public std::enable_shared_from_this<Actor> // allows you to make shared pointer for the actor class
{

public:

	Actor();
	~Actor();

protected:

	// parameters lower case, members prefix with m, static prefix with s
	
	// will be called when the Actor is added or the Game Starts
	virtual void BeginPlay();

	// will be called before destruction or at game end
	virtual void EndPlay();

	// will be called every frame
	virtual void Tick(float deltaSeconds);
    

	// unsigned int is 32 bits in total - with this one unsigned int only uses 1 bit so saves lots of space
	unsigned int mCanEverTick : 1;

private:

	// stores all the components
	ComponentList mComponents;


#pragma region TemplateRegion

public:

	// Add component function (T template just calling it componenttype)
	template<std::derived_from<Component> ComponentType, typename ...Args> // can pass other arguments with the weak ptr
	//shared pointer
	//tuple can have mutiple return types
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType(Args... arguments)
	{
		ComponentType* NewComponentRawPtr = new ComponentType(weak_from_this(), arguments...); //... unpacking arguments
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*NewComponentRawPtr); //weak ptr can only be created by a shared ptr
		
		//if i can add new component I do, if not just exit out
		if (NewComponent->CanAddComponent())
		{
			NewComponent->InitializeComponent();
			mComponents.emplace_back(NewComponent);
			return { NewComponent, true, "Component was created successfully" };
		}

		return { nullptr, false,"Failed to add component as it returns false in Component::CamAddComponent" };
	}

	// find component function
	template<std::derived_from<Component> ComponentClassToFind> //can only take classes that are derived from component class
	std::shared_ptr<ComponentClassToFind> FindComponentOfType()
	{
		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			//returns true if dynamic cast works - null ptr = false, valid ptr = true
			//FoundComponent being assigned inside inside if statement
			if (std::shared_ptr<ComponentClassToFind> FoundComponent = 
				std::dynamic_pointer_cast<ComponentClassToFind>(ComponentIterator))
			{
				return FoundComponent;
			}
		}
		//exit condition
		return nullptr;
	}

	//finds all components of type that returns an array instead of a single component
	template<std::derived_from<Component> ComponentClassToFind> //can only take classes that are derived from component class
	std::list<std::shared_ptr<ComponentClassToFind>> FindAllComponentOfType()
	{
		//initialize a list to store return
		std::list<std::shared_ptr<ComponentClassToFind>> FoundComponents;

		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			//returns true if dynamic cast works - null ptr = false, valid ptr = true
			//FoundComponent being assigned inside inside if statement
			if (std::shared_ptr<ComponentClassToFind> FoundComponent =
				std::dynamic_pointer_cast<ComponentClassToFind>(ComponentIterator))
			{
				//add to list and continue
				FoundComponents.emplace_back(FoundComponent);
			}
		}
		//exit condition
		return FoundComponents;
	}


#pragma endregion


};


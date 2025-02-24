#pragma once
#include "Game/Public/Gamecore/GameCore.h"
#include "Game/Public/StateMachine/State.h"
#include <thread>
#include <chrono>

template <class StateDependencyObject>

class StateMachine
{
public:

	void AddState(const String& StateName, std::shared_ptr<State<StateDependencyObject>> StateToAdd) //<State<StateDependencyObject>> double causei ts a templated class
	{
		mStates[StateName] = StateToAdd;
	}

	void SetState(const String& NewState, std::shared_ptr<StateDependencyObject> DependencyObject)
	{
		if (mCurrentState)
		{
			mCurrentState->Exit(DependencyObject);
		}
		//exiting current state and entering next state in dictionary
		//std::pair<String, std::shared_ptr<DependencyObject>> StateIterator = mStates.find(NewState);
		auto StateIterator = mStates.find(NewState);
		if (StateIterator != mStates.end())
		{
			//if new state is found, enter that state
			mCurrentState = StateIterator->second;
			mCurrentState->Enter(DependencyObject);
		}
	}

	void Update(std::shared_ptr<StateDependencyObject> DependencyObject)
	{
		
	}

	std::shared_ptr<State<StateDependencyObject>> GetCurrentState() const
	{
		return mCurrentState;
	}

private:

	std::unordered_map<String, std::shared_ptr<State<StateDependencyObject>>> mStates; 
	std::shared_ptr<State<StateDependencyObject>> mCurrentState;

	int mIterFrames = 0;
};


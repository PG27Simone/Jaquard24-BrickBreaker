#pragma once
#include "Game/Public/Gamecore/GameCore.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Actors/Ship.h"

template <class StateDependencyObject>

class State
{

public:

	State() 
	{
		mNextState = "";
	};

	State(String NextState)
	{
		mNextState = NextState;
	};

	virtual ~State() {};


	//State Methods
	virtual void Enter(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;
	virtual void Update(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;
	virtual void Exit(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;

	//virtual void SetPlayerVelocity(exVector2 v) {};

	//getter and setter
	void SetNextState(const String& NextState)
	{
		mNextState = NextState;
	};

	String GetNextState() const
	{
		return mNextState;
	};

private:

	String mNextState;

};

class MainMenu : public State<Actor>
{
public:

	MainMenu()
	{
		SetNextState("Gameplay");
	}

	void Enter(std::shared_ptr<Actor> DependencyObject) override;
	
	void Update(std::shared_ptr<Actor> DependencyObject) override;
	
	void Exit(std::shared_ptr<Actor> DependencyObject) override;

	void HandleEnterKey();



private:

	std::shared_ptr<Actor> TitleText;
	std::shared_ptr<Actor> PlayButton;
	std::shared_ptr<Actor> QuitButton;

};


class Gameplay : public State<Actor>
{
public:

	Gameplay()
	{
		SetNextState("EndGame");
	}

	void Enter(std::shared_ptr<Actor> DependencyObject) override;

	void Update(std::shared_ptr<Actor> DependencyObject) override;

	void Exit(std::shared_ptr<Actor> DependencyObject) override;


	std::shared_ptr<Actor> GetPlayer()
	{
		return Player;
	}

	std::shared_ptr<Actor> GetBall()
	{
		return Ball;
	}


private:

	std::shared_ptr<Actor> Player;
	std::shared_ptr<Actor> Ball;
	std::shared_ptr<Actor> Border1;
	std::shared_ptr<Actor> Border2;
	std::shared_ptr<Actor> Border3;
	std::shared_ptr<Actor> Border4;

};

class EndGame : public State<Actor>
{
public:

	EndGame()
	{
		SetNextState("MainMenu");
	}

	void Enter(std::shared_ptr<Actor> DependencyObject) override;

	void Update(std::shared_ptr<Actor> DependencyObject) override;

	void Exit(std::shared_ptr<Actor> DependencyObject) override;

	void HandleEnterKey();

private:

	std::shared_ptr<Actor> TitleText;
	std::shared_ptr<Actor> PlayButton;
	std::shared_ptr<Actor> QuitButton;

};

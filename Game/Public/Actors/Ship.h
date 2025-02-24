#pragma once
#include "Actor.h"
#include "Game/Public/Gamecore/GameCore.h"
#include "Engine/Public/EngineTypes.h"

class Ship : public Actor
{

public:
	Ship() = delete;

	Ship(String shipName, exColor shipcolor, exVector2 startingPos, exVector2 velocity);

	virtual void BeginPlay() override;

	void OnShipCollided(std::weak_ptr<Actor> HirActor, const exVector2& HitPoisition);

private:

	String mShipName;
	exColor mShipColor;
	exVector2 mShipStartingPosition;
	exVector2 mShipInitialVelocity;



};


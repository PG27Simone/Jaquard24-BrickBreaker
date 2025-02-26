//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Singletons/PhysicsEngine.h"	
#include "Game/Public/Actors/Ship.h"
#include "Game/Public/StateMachine/State.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------
const char* gWindowName = "Sample EngineX Game";

const float gMinimumLeftdirection = -1.0f;
const float gMinimumRightdirection = 1.0f;
float randomX;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine( nullptr )
	, mFontID( -1 )
	, mRight( false )
	, mLeft( false )
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize( exEngineInterface* pEngine )
{
	
	mEngine = pEngine;


	mFontID = mEngine->LoadFont( "Resources/Jacquard24-Regular.ttf", 32 );

	mStateMachine = std::make_shared<StateMachine<Actor>>();
	mStateMachine->AddState("Gameplay", std::make_shared<Gameplay>());
	mStateMachine->AddState("MainMenu", std::make_shared<MainMenu>());
	mStateMachine->AddState("EndGame", std::make_shared<EndGame>());

	mStateMachine->SetState("MainMenu", nullptr);
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor( exColor& color ) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent(SDL_Event* pEvent)
{
	if (pEvent->type == SDL_KEYDOWN)  // Detect key press
	{
		switch (pEvent->key.keysym.sym)
		{
		case SDLK_RETURN: // Enter key
			if (mStateMachine)
			{
				// Allow Enter only in MainMenu and EndGame
				std::shared_ptr<State<Actor>> currentState = mStateMachine->GetCurrentState();
				if (std::dynamic_pointer_cast<MainMenu>(currentState) ||
					std::dynamic_pointer_cast<EndGame>(currentState))
				{
					mStateMachine->SetState("Gameplay", nullptr);
				}
			}
			break;

		case SDLK_ESCAPE: // Escape key (always active)
			exit(0); // Quit the game
			break;

		default:
			break;
		}
	}
}




//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &nKeys );

	mRight = pState[SDL_SCANCODE_RIGHT];
	mLeft = pState[SDL_SCANCODE_LEFT];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run( float fDeltaT )
{
	//CONTROLS
	auto currentState = std::dynamic_pointer_cast<Gameplay>(mStateMachine->GetCurrentState());

	if (currentState) {
		if (mRight)
		{
			//stay in border
			if(currentState->GetPlayer()->FindComponentOfType<TransformComponent>()->GetLocation().x < 700)
				currentState->GetPlayer()->FindComponentOfType<BoxColliderComponent>()->SetVelocity(exVector2(4.0f, 0.0f));
			else {
				currentState->GetPlayer()->FindComponentOfType<BoxColliderComponent>()->SetVelocity(exVector2(0.0f, 0.0f));
			}
		}
		else if (mLeft)
		{
			//stay in border
			if (currentState->GetPlayer()->FindComponentOfType<TransformComponent>()->GetLocation().x > 100)
				currentState->GetPlayer()->FindComponentOfType<BoxColliderComponent>()->SetVelocity(exVector2(-4.0f, 0.0f));
			else {
				currentState->GetPlayer()->FindComponentOfType<BoxColliderComponent>()->SetVelocity(exVector2(0.0f, 0.0f));
			}
		}
		else {
			currentState->GetPlayer()->FindComponentOfType<BoxColliderComponent>()->SetVelocity(exVector2(0.0f, 0.0f));
		}
	}
	

	//render stuff
	//mStateMachine->Update(Character1);

	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
}


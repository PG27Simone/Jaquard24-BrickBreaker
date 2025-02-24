#include "Game/Public/StateMachine/State.h"
#include "Game/Public/Actors/Ship.h"
#include "Game/Public/Game.h"


#include <random>

void MainMenu::Enter(std::shared_ptr<Actor> DependencyObject)
{
	PlayButton = std::make_shared<Actor>();
	PlayButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
	PlayButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f);	
	
	QuitButton = std::make_shared<Actor>();
	QuitButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 750.0f));
	QuitButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f);
	//TODO: add text to buttons
}

void MainMenu::Update(std::shared_ptr<Actor> DependencyObject)
{
}

void MainMenu::Exit(std::shared_ptr<Actor> DependencyObject)
{
	PlayButton.reset();
	QuitButton.reset();

}

void Gameplay::Enter(std::shared_ptr<Actor> DependencyObject)
{
	//Player = std::make_shared<Ship>("Player Ship", exColor({ 150,20,30,255 }), exVector2(50.0f, 300.0f), exVector2(0.2f, 0.0f));
	//Player->BeginPlay();
	
	
	//random num
	// https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-2.0f, 2.0f);
	const float randomX = dis(gen);

	Player = std::make_shared<Actor>();
	Player->AddComponentOfType<TransformComponent>(exVector2(400.0f, 500.0f));
	Player->AddComponentOfType<BoxRenderComponent>(200.0f, 50.0f, exColor({ 128, 100, 50, 255 }), 1);
	Player->AddComponentOfType<BoxColliderComponent>(200.0f, 50.0f, exVector2(0.0f, 0.0f));

	Ball = std::make_shared<Actor>();
	Ball->AddComponentOfType<TransformComponent>(exVector2(400.0f, 400.0f));
	Ball->AddComponentOfType<CircleRenderComponent>(10.0f);
	Ball->AddComponentOfType<CircleColliderComponent>(10.0f, exVector2(randomX, 2.0f));

	//borders
	//border top
	Border1 = std::make_shared<Actor>();
	Border1->AddComponentOfType<TransformComponent>(exVector2(400.0f, 0.0f));
	Border1->AddComponentOfType<BoxRenderComponent>(10000.0f, 10.0f, exColor({ 100, 100, 100, 0 }), 3); //alpha 0
	Border1->AddComponentOfType<BoxColliderComponent>(10000.0f, 10.0f, exVector2(0.0f, 0.0f));

	//border bottom TODO: make it end the game if ball hits this
	Border2 = std::make_shared<Actor>();
	Border2->AddComponentOfType<TransformComponent>(exVector2(400.0f, 800.0f));
	Border2->AddComponentOfType<BoxRenderComponent>(10000.0f, 10.0f, exColor({ 0, 0, 0, 0 }), 4); //alpha 0
	Border2->AddComponentOfType<BoxColliderComponent>(10000.0f, 10.0f, exVector2(0.0f, 0.0f));

	//border left
	Border3 = std::make_shared<Actor>();
	Border3->AddComponentOfType<TransformComponent>(exVector2(0.0f, 600.0f));
	Border3->AddComponentOfType<BoxRenderComponent>(10.0f, 10000.0f, exColor({ 100, 100, 100, 0 }), 2); //alpha 0
	Border3->AddComponentOfType<BoxColliderComponent>(10.0f, 10000.0f, exVector2(0.0f, 0.0f));

	//border right
	Border4 = std::make_shared<Actor>();
	Border4->AddComponentOfType<TransformComponent>(exVector2(800.0f, 600.0f));
	Border4->AddComponentOfType<BoxRenderComponent>(10.0f, 10000.0f, exColor({ 0, 0, 0, 0 }), 2); //alpha 0
	Border4->AddComponentOfType<BoxColliderComponent>(10.0f, 10000.0f, exVector2(0.0f, 0.0f));
}

void Gameplay::Update(std::shared_ptr<Actor> DependencyObject)
{
	

}

void Gameplay::Exit(std::shared_ptr<Actor> DependencyObject)
{
	Player.reset();
	Ball.reset();
	Border1.reset();
	Border2.reset();
	Border3.reset();
	Border4.reset();
}

void EndGame::Enter(std::shared_ptr<Actor> DependencyObject)
{
	RetryButton = std::make_shared<Actor>();
	RetryButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
	RetryButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f);
}

void EndGame::Update(std::shared_ptr<Actor> DependencyObject)
{
}

void EndGame::Exit(std::shared_ptr<Actor> DependencyObject)
{
	RetryButton.reset();
}

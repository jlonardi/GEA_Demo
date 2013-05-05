#include "Game.h"

Game::Game() : controller(), timer()
{
}

Game::Game(const Game& other)
{
	controller = other.controller;
}

Game& Game::operator=(const Game& other)
{
	if(this == &other) return *this;
	Game temp = Game(other);
	Controller tempController = controller;
	controller = temp.controller;
	temp.controller = tempController;
	return *this;
}

bool Game::setup() 
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return false;
	}
	controller = Controller();
	timer.start();
	return true;
}

void Game::start() 
{

	controller.init();

	while(!controller.gameOver())
	{
		if(timer.timeLeft() == 0)
		{
			controller.check();
		}
	}

}

void Game::quit()
{
	SDL_Quit();
}

Game::~Game()
{
}
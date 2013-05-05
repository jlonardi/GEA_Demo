#ifndef GAME_H
#define GAME_H

#include "Controller.h"
#include "Timer.h"

class Game {
private:
	Controller controller;
	Timer timer;
public:
	Game();
	Game(const Game& other);
	Game& operator= (const Game& other); 
	static Uint32 TimeLeft();
	bool setup();
	void start();
	void quit();
	virtual ~Game();
};

#endif
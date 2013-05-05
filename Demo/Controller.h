#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Logic.h"

class Controller 
{
private:
	Logic logic;
	Uint8* keystate;
	bool quit;
	void handleInputs();
	void resetKeys();

public:
	Controller();
	Controller(const Controller& other);
	Controller& operator=(const Controller& other);
	void init();
	void check();
	bool gameOver();
	virtual ~Controller();
};

#endif
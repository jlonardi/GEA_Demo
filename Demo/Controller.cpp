#include "Controller.h"

Controller::Controller() : logic(), quit(false)
{
}

Controller::Controller(const Controller& other)
{

}

Controller& Controller::operator=(const Controller& other)
{
	return *this;
}

void Controller::init()
{
	keystate = SDL_GetKeyState(NULL);
	logic.init();
}

void Controller::check()
{
	handleInputs();
	logic.update();
}

bool Controller::gameOver()
{
	return quit;
}
void Controller::resetKeys()
{
	keystate[SDLK_LEFT] = false;
	keystate[SDLK_RIGHT] = false;
	keystate[SDLK_UP] = false;
	keystate[SDLK_DOWN] = false;
}

void Controller::handleInputs()
{
	SDL_Event keyevent;    //The SDL event that we will poll to get events.

	while (SDL_PollEvent(&keyevent))   //Poll our SDL key event for any keystrokes.
	{

		switch(keyevent.type) {
		case SDL_KEYDOWN:
			switch(keyevent.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_F1:
				logic.save();
				break;
			case SDLK_F2:
				logic.load();
				break;
			case SDLK_F10:
				logic.fullScreenCommandInvoked();
				break;
			case SDLK_LEFT:
				keystate[SDLK_LEFT] = true;
				break;
			case SDLK_RIGHT:
				keystate[SDLK_RIGHT] = true;
				break;
			case SDLK_UP:
				keystate[SDLK_UP] = true;
				break;
			case SDLK_DOWN:
				keystate[SDLK_DOWN] = true;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch(keyevent.key.keysym.sym) {
			case SDLK_LEFT:
				keystate[SDLK_LEFT] = false;
				break;
			case SDLK_RIGHT:
				keystate[SDLK_RIGHT] = false;
				break;
			case SDLK_UP:
				keystate[SDLK_UP] = false;
				break;
			case SDLK_DOWN:
				keystate[SDLK_DOWN] = false;
				break;
			default:
				break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	//continuous-response keys
	if(keystate[SDLK_LEFT])
	{
		if(keystate[SDLK_UP] || keystate[SDLK_DOWN]) 
		{
			logic.move(-2,0);
		} else {
			logic.move(-3,0);
		}
	} 
	if(keystate[SDLK_RIGHT])
	{
		if(keystate[SDLK_UP] || keystate[SDLK_DOWN]) 
		{
			logic.move(2,0);
		} else {
			logic.move(3,0);
		}
	}
	if(keystate[SDLK_UP])
	{
		if(keystate[SDLK_LEFT] || keystate[SDLK_RIGHT]) 
		{
			logic.move(0,-2);
		} else {
			logic.move(0,-3);
		}
	}
	if(keystate[SDLK_DOWN])
	{
		if(keystate[SDLK_LEFT] || keystate[SDLK_RIGHT]) 
		{
			logic.move(0,2);
		} else {
			logic.move(0,3);
		}
	}
	if(!(keystate[SDLK_LEFT] || keystate[SDLK_RIGHT] || keystate[SDLK_UP] || keystate[SDLK_DOWN])) {
		logic.move(0,0);
	}
}

Controller::~Controller()
{
}
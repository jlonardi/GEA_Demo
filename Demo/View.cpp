#include "View.h"
#include <iostream>
View::View() : screen(NULL), SCREEN_WIDTH(640), SCREEN_HEIGHT(480), SCREEN_BPP(32), FRAMES_PER_SECOND(60), fullScreen(false)
{
}
View::View(const View& other)
{
}
View& View::operator= (const View& other)
{
	return *this;
}

bool View::init()
{
	camera.x = 0;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	//Set up the screen
	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	//If there was an error in setting up the screen
	if( screen == NULL )
	{
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( "Demo", NULL );

	//If everything initialized fine
	return true;
}
void View::render() 
{
	SDL_Flip(screen);
}

SDL_Rect View::getCamera()
{
	return camera;
}

void View::setCamera(SDL_Rect& c)
{
	camera = c;
}

void View::apply(int x, int y, SDL_Surface* source, SDL_Rect* clip )
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit
	SDL_BlitSurface( source, clip, screen, &offset );
}

void View::save(SaveNode& node)
{
	node.add("cameraX", camera.x);
	node.add("cameraY", camera.y);
	node.add("cameraW", camera.w);
	node.add("cameraH", camera.h);
}
void View::load(SaveNode& node)
{
	node.poll("cameraX", camera.x);
	node.poll("cameraY", camera.y);
	node.poll("cameraW", camera.w);
	node.poll("cameraH", camera.h);
}

void View::toggleFullScreen()
{
	if(fullScreen)
	{
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
		SDL_ShowCursor(1);
		fullScreen = false;
	} else
	{
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);
		SDL_ShowCursor(0);
		fullScreen = true;
	}
}
View::~View()
{
}
#include "Logic.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

Logic::Logic() : view(), level("level1.tmx"), message(NULL)
{
}

Logic::Logic(const Logic& other) : view(), level("level1.tmx")
{
}

Logic& Logic::operator=(const Logic& other)
{
	return *this;
}

void Logic::setPlayerDirection(int deltaX, int deltaY)
{
	// Sets the players facing direction and
	// checks if movment is needed or not
	if(deltaX < 0) 
	{
		player.setMoving(true);
		player.setDirection(LEFT);
	} else if(deltaX > 0)
	{
		player.setMoving(true);
		player.setDirection(RIGHT);
	} else if(deltaY < 0)
	{
		player.setMoving(true);
		player.setDirection(UP);
	} else if(deltaY > 0)
	{
		player.setMoving(true);
		player.setDirection(DOWN);
	} else
	{
		player.setMoving(false);
	}
}

void Logic::checkCameraAxisMovements(bool& moveCameraHorizontaly, bool& moveCameraVertically,
									 int deltaX, int deltaY, int& playerX, int& playerY)
{
	SDL_Rect levelSize = level.getSize();
	SDL_Rect camera = view.getCamera();
	SDL_Rect playerPosition = player.getPosition();
	playerPosition.x = playerPosition.x + playerPosition.w/2;
	playerPosition.y = playerPosition.y + playerPosition.h/2;
	int playerVelocity = player.getVelocity();
	playerX = 0;
	playerY = 0;

	// check if moving the camera would make it collide with the level boundaries
	bool cameraCollidesLeftEdge = (camera.x - 3 < 0);
	bool cameraCollidesRightEdge = (camera.x + camera.w + 3 > levelSize.w);
	bool cameraCollidesTopEdge = (camera.y - 3 < 0);
	bool cameraCollidesBottomEdge = (camera.y + camera.h + 3 > levelSize.h);

	// Check if you should move the player related to screen instead of moving the camera.
	// Check for horizontal directions
	if(cameraCollidesLeftEdge)
	{
		if(playerPosition.x <= camera.w/2)
		{
			playerX = deltaX * playerVelocity;
			moveCameraHorizontaly = false;
			if(playerPosition.x + playerX > camera.w/2) 
			{
				playerX = camera.w/2 - playerPosition.x ;
				moveCameraHorizontaly = true;
			}
		}
	} else if(cameraCollidesRightEdge)
	{
		if(playerPosition.x >= camera.w/2)
		{
			playerX = deltaX * playerVelocity;
			moveCameraHorizontaly = false;
			if(playerPosition.x + playerX < camera.w/2)
			{
				playerX = camera.w/2 - playerPosition.x ;
				moveCameraHorizontaly = true;
			}
		}
	}
	// Check for vertical directions
	if(cameraCollidesTopEdge)
	{
		if(playerPosition.y <= camera.h/2)
		{
			playerY = deltaY * playerVelocity;
			moveCameraVertically = false;
			if(playerPosition.y + playerY > camera.h/2) 
			{
				playerY = camera.h/2 - playerPosition.y ;
				moveCameraVertically = true;
			}
		}
	} else if(cameraCollidesBottomEdge)
	{
		if(playerPosition.y >= camera.h/2)
		{
			playerY = deltaY * playerVelocity;
			moveCameraVertically = false;
			if(playerPosition.y + playerY < camera.h/2)
			{
				playerY = camera.h/2 - playerPosition.y ;
				moveCameraVertically = true;
			}
		}
	}
}

void Logic::move(int deltaX, int deltaY)
{
	setPlayerDirection(deltaX, deltaY);
	int playerX = 0;
	int playerY = 0;

	SDL_Rect camera = view.getCamera();
	int cameraVelocity = player.getVelocity();
	int cameraX = deltaX * cameraVelocity;
	int cameraY = deltaY * cameraVelocity;

	SDL_Rect levelSize = level.getSize();

	bool moveCameraHorizontaly = true;
	bool moveCameraVertically = true;

	checkCameraAxisMovements(moveCameraHorizontaly, moveCameraVertically, deltaX, deltaY, playerX, playerY);

	// Move camera in x-axis
	if(moveCameraHorizontaly)
	{	
		if(camera.x + cameraX >= 0 && camera.x + camera.w + cameraX <= levelSize.w)
		{
			camera.x += cameraX;
		} 		
	}
	// Move camera in x-axis
	if(moveCameraVertically)
	{	
		if(camera.y + cameraY >= 0 && camera.y + camera.h+ cameraY <= levelSize.h) 
		{
			camera.y += cameraY;
		} 
	}
	view.setCamera(camera);

	SDL_Rect playerPos = player.getPosition();

	// Move player
	if(playerPos.x + playerX < 0 )
	{
		playerX = 0;
	} else if(playerPos.x + playerPos.w + playerX > camera.w)
	{
		playerX = 0;
	} 

	if(playerPos.y + playerY < 0)
	{
		playerY = 0;
	}
	if(playerPos.y + playerPos.h + playerY > camera.h)
	{
		playerY = 0;
	}

	player.move(playerX, playerY);

}

void Logic::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	font = TTF_OpenFont("resources/mini_pixel-7.ttf", 24);
	if (font == NULL)
	{
		std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << std::endl;
		TTF_Quit();
		SDL_Quit();
		exit(1);
	}
	textColor.b = 255;
	textColor.g = 255;
	textColor.r = 255;

	ss.attach(&player, "player");
	ss.attach(&level, "level");
	ss.attach(&view, "view");

	view.init();
	player = Player(0,0,1);
	level.load();
}

void Logic::update() 
{
	SDL_Rect plr = player.getPosition();
	SDL_Rect fnsh = level.getFinish();
	SDL_Rect cmr = view.getCamera();
	plr.x += cmr.x;
	plr.y += cmr.y;
	if(checkCollision(plr, fnsh))
	{
		std::cout << "level finished" << std::endl;
		level = Level("level2.tmx");
		level.load();
	}
	level.draw(view);
	player.draw(view);
	drawHud();
	view.render();
}

void Logic::drawHud()
{
	std::ostringstream xp, lvl;
	xp << "XP: " << player.getXp() << std::endl;
	lvl << "LVL: " << player.getLvl() << std::endl;

	SDL_Surface* xpMessage = TTF_RenderText_Solid( font, xp.str().c_str() , textColor );
	SDL_Surface* lvlMessage = TTF_RenderText_Solid( font, lvl.str().c_str() , textColor );
	view.apply(550, 10, xpMessage);
	view.apply(550, 30, lvlMessage);
}

SDL_Rect Logic::getLevelDimension()
{
	return level.getSize();
}

bool Logic::checkCollision(SDL_Rect A, SDL_Rect B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = A.x;
	rightA = A.x + A.w;
	topA = A.y;
	bottomA = A.y + A.h;

	//Calculate the sides of rect B
	leftB = B.x;
	rightB = B.x + B.w;
	topB = B.y;
	bottomB = B.y + B.h;

	//If any of the sides from A are outside of B
	if( bottomA <= topB )
	{
		return false;
	}

	if( topA >= bottomB )
	{
		return false;
	}

	if( rightA <= leftB )
	{
		return false;
	}

	if( leftA >= rightB )
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

SDL_Surface* Logic::loadImage( std::string filename )
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized surface that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if( loadedImage != NULL )
	{
		std::cout << "successfully loaded image: " << filename.c_str() << std::endl;
		//Create an optimized surface
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

		//Free the old surface
		SDL_FreeSurface(loadedImage);

		//If the surface was optimized
		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
		}
	}

	//Return the optimized surface
	return optimizedImage;
}

void Logic::fullScreenCommandInvoked()
{
	view.toggleFullScreen();
}

void Logic::save()
{
	ss.save("demo.save");
}

void Logic::load()
{
	ss.load("demo.save");
}

Logic::~Logic()
{
}
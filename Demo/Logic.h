#ifndef LOGIC_H
#define LOGIC_
#include "View.h"
#include "Level.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SaveSystem.h>

class Logic 
{
private:
	View view;
	Level level;
	Player player;
	SDL_Surface* message;
	TTF_Font* font;
	SDL_Color textColor;
	SaveSystem ss;
	void setPlayerDirection(int deltaX, int deltaY);
	void drawHud();
	void checkCameraAxisMovements(bool& moveCameraHorizontaly, 
			bool& moveCameraVertically, int deltaX, int deltaY,
			int& playerX, int& playerY);

public:
	Logic();
	Logic(const Logic& other);
	Logic& operator=(const Logic& other);
	void move(int deltaX, int deltaY);
	void init();
	void update();
	SDL_Rect getLevelDimension();
	static SDL_Surface* loadImage(std::string filename);
	static bool checkCollision(SDL_Rect A, SDL_Rect B);
	void fullScreenCommandInvoked();
	void save();
	void load();
	virtual ~Logic();
};

#endif
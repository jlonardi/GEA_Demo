#ifndef PLAYER_H
#define PLAYER_H

#include "View.h"
#include "Drawable.h"
#include "Timer.h"
#include <Serializable.h>
#include <string>
#include <vector>

enum Direction 
{
	DOWN = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3
};

class Player : public Drawable, public Serializable
{
private:
	int x;
	int y;
	int velocity;
	int SPRITE_ROWS;
	int SPRITE_COLUMNS;
	int SPRITE_WIDTH;
	int SPRITE_HEIGHT;
	int frame;
	bool moving;
	Direction direction;
	SDL_Surface* spriteSheet;
	std::vector<SDL_Rect> clips;
	Timer timer;

	int xp;
	int lvl;

	void animate();

public:
	Player();
	Player(int x, int y, int v);
	Player(Player& other);
	Player& operator=(Player& other);
	void draw(View& view);
	void move(int deltaX, int deltaY);
	void setDirection(enum Direction d);
	void setMoving(bool mov);
	int getVelocity();
	void setVelocity(int v);
	SDL_Rect getPosition();
	int getLvl();
	int getXp();
	void save(SaveNode& node);
	void load(SaveNode& node);
	virtual ~Player();
};

#endif
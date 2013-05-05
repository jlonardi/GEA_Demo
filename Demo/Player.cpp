#include "Player.h"
#include "Logic.h"
#include <iostream>

Player::Player()
{
	spriteSheet = NULL;
}

Player::Player(int x, int y, int v) : x(x), y(y), velocity(v), direction(RIGHT), 
	frame(0), timer(), moving(false), xp(0), lvl(0)
{
	spriteSheet = Logic::loadImage("resources/hero.png");
	if(spriteSheet != NULL) std::cout << "loading hero successfull" << std::endl;
	SPRITE_WIDTH = 48;
	SPRITE_HEIGHT = 72;
	SPRITE_ROWS = 4;
	SPRITE_COLUMNS = 4;
	for(int i = 0; i < SPRITE_ROWS; i++)
	{
		for(int j = 0; j < SPRITE_COLUMNS; j++)
		{
			SDL_Rect clip;
			clip.x = j * SPRITE_WIDTH;
			clip.y = i * SPRITE_HEIGHT;
			clip.w = SPRITE_WIDTH;
			clip.h = SPRITE_HEIGHT;
			clips.push_back(clip);
		}
	}
	timer.start();
}

Player::Player(Player& other)
{
	x = other.x;
	y = other.y;
	velocity = other.velocity;
	SPRITE_ROWS = other.SPRITE_ROWS;
	SPRITE_COLUMNS = other.SPRITE_COLUMNS;
	SPRITE_WIDTH = other.SPRITE_WIDTH;
	SPRITE_HEIGHT = other.SPRITE_HEIGHT;
	frame = other.frame;
	moving = other.moving;
	direction = other.direction;
	spriteSheet = other.spriteSheet;
	clips = other.clips;
	xp = other.xp;
	lvl = other.lvl;
	timer.start();
}

Player& Player::operator=(Player& other)
{
	if(&other == this) return *this;

	Player temp(other);
	int tempX = temp.x;
	int tempY = temp.y;
	int tempVelocity = temp.velocity;
	int tempRows = temp.SPRITE_ROWS;
	int tempColumns = temp.SPRITE_COLUMNS;
	int tempWidth = temp.SPRITE_WIDTH;
	int tempHeight = temp.SPRITE_HEIGHT;
	int tempFrame = temp.frame;
	bool tempMoving = temp.moving;
	Direction tempDirection = temp.direction;
	SDL_Surface* tempSpriteSheet = temp.spriteSheet;
	std::vector<SDL_Rect> tempClips = temp.clips;
	int tempXp = temp.xp;
	int tempLvl = temp.lvl;

	temp.x = x;
	temp.y = y;
	temp.velocity = velocity;
	temp.SPRITE_ROWS = SPRITE_ROWS;
	temp.SPRITE_COLUMNS = SPRITE_COLUMNS;
	temp.SPRITE_WIDTH = SPRITE_WIDTH;
	temp.SPRITE_HEIGHT = SPRITE_HEIGHT;
	temp.frame = frame;
	temp.moving = moving;
	temp.direction = direction;
	temp.spriteSheet = spriteSheet;
	temp.clips = clips;
	temp.xp = xp;
	temp.lvl = lvl;

	x = tempX;
	y = tempY;
	velocity = tempVelocity;
	SPRITE_ROWS = tempRows;
	SPRITE_COLUMNS = tempColumns;
	SPRITE_WIDTH = tempWidth;
	SPRITE_HEIGHT = tempHeight;
	frame = tempFrame;
	moving = tempMoving;
	direction = tempDirection;
	spriteSheet = tempSpriteSheet;
	clips = tempClips;
	xp = tempXp;
	lvl = tempLvl;

	timer.start();
	return *this;
}

void Player::draw(View& view)
{
	view.apply(x, y, spriteSheet, &clips[direction * SPRITE_COLUMNS + frame]);
	animate();
}

void Player::move(int deltaX, int deltaY)
{
	x += deltaX;
	y += deltaY;
	if(moving)
	{
		xp++;
		if(xp % 100 == 0)
		{
			lvl++;
		}
	}
}

void Player::animate()
{
	static int tick = 0;
	int currentTime = SDL_GetTicks();
	int deltaTime = currentTime - tick;
	if(!moving)
	{
		frame = 0;
		return;
	}
	if(deltaTime > 120 ) 
	{
		frame++;
		tick = currentTime;
		deltaTime = 0;
	}
	if(frame == 4) frame = 0;
}

void Player::setDirection(enum Direction d)
{
	direction = d;
}

void Player::setMoving(bool mov)
{
	moving = mov;
}

int Player::getVelocity()
{
	return velocity;
}

void Player::setVelocity(int v)
{
}

SDL_Rect Player::getPosition()
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = SPRITE_WIDTH;
	pos.h = SPRITE_HEIGHT;

	return pos;
}

int Player::getLvl()
{
	return lvl;
}

int Player::getXp()
{
	return xp;
}

void Player::save(SaveNode& node)
{
	node.add("xp", xp);
	node.add("lvl", lvl);
	node.add("x", x);
	node.add("y", y);
}
void Player::load(SaveNode& node)
{
	node.poll("xp", xp);
	node.poll("lvl", lvl);
	node.poll("x", x);
	node.poll("y", y);
}

Player::~Player()
{
	//SDL_FreeSurface(spriteSheet);
}

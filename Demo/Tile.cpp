#include "Tile.h"

Tile::Tile()
{
	box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = 0;

	clipIndex = 0;
}

Tile::Tile(Tile& other)
{
	box.x = other.box.x;
	box.y = other.box.y;
	box.w = other.box.w;
	box.h = other.box.h;

	clipIndex = other.clipIndex;
}

Tile& Tile::operator=(Tile& other)
{
	if(&other == this) return *this;
	Tile temp(other);
	int tempX = other.box.x;
	int tempY = other.box.y;
	int tempW = other.box.w;
	int tempH = other.box.h;
	int tempIndex = other.clipIndex;

	other.box.x = box.x;
	other.box.y = box.y;
	other.box.w = box.w;
	other.box.h = box.h;
	other.clipIndex = clipIndex;

	box.x = tempX;
	box.y = tempY;
	box.w = tempW;
	box.h = tempH;
	clipIndex = tempIndex;

	return *this;
}

Tile::Tile( int x, int y, int w, int h, int clip )
{
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	clipIndex = clip;
}

int Tile::getClipIndex()
{
	return clipIndex;
}

SDL_Rect Tile::getBox()
{
	return box;
}

Tile::~Tile() {}
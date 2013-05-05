#ifndef TILE_H
#define TILE_H

#include <SDL.h>
enum TileType{
	PENETRABLE = 0,
	IMPENETRABLE = 1
};
class Tile
{
private:
	//The attributes of the tile
	SDL_Rect box;
	//The tile type
	int clipIndex;

public:

	Tile();
	Tile(Tile& other);
	Tile& operator=(Tile& other);
	Tile(int x, int y, int w, int h, int clipIndex);
	//Get the tile type
	int getClipIndex();

	//Get the collision box
	SDL_Rect getBox();

	virtual ~Tile();
};

#endif
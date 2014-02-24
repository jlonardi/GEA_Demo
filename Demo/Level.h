#ifndef LEVEL_H
#define LEVEL_H

#include "View.h"
#include "Tile.h"
#include "Drawable.h"
#include <Serializable.h>
#include <rapidxml.hpp>
#include <vector>

class Level : public Drawable, public Serializable
{
private:
	std::vector<Tile> tiles;
	std::vector<SDL_Rect> clips;
	std::string name;
	std::string tileSheetSource;
	SDL_Surface *tileSheet;

	int LEVEL_WIDTH;
	int LEVEL_HEIGHT;
	int TILE_WIDTH;
	int TILE_HEIGHT;

	int TILE_SHEET_WIDTH;
	int TILE_SHEET_HEIGHT;

	SDL_Rect finish;

	Level();
	void setupMapData(rapidxml::xml_node<>* map);
	void getImageData(rapidxml::xml_node<>* image);
	void createTiles(rapidxml::xml_node<>* layer);
	void createClips();
	int xmlAttributeToInt(rapidxml::xml_node<>* node, std::string attr);

public:
	Level(std::string name);
	Level(Level& other);
	Level& operator=(Level& other);
	void load();
	void draw(View& view);
	SDL_Rect getFinish();
	SDL_Rect getSize();
	void save(SaveNode& node);
	void load(SaveNode& node);
	virtual ~Level();
};

#endif
#include "Level.h"
#include "Logic.h"
#include <fstream>
#include <iostream>
#include <sstream>

Level::Level(std::string name) : name(name), tiles(), tileSheet(NULL)
{
}

Level::Level(Level& other)
{
	tiles = other.tiles;
	clips = other.clips;
	name = other.name;
	tileSheetSource = other.tileSheetSource;
	tileSheet = other.tileSheet;

	LEVEL_WIDTH = other.LEVEL_WIDTH;
	LEVEL_HEIGHT = other.LEVEL_HEIGHT;
	TILE_WIDTH = other.TILE_WIDTH;
	TILE_HEIGHT = other.TILE_HEIGHT;

	TILE_SHEET_WIDTH = other.TILE_SHEET_WIDTH;
	TILE_SHEET_HEIGHT = other.TILE_SHEET_HEIGHT;

	finish = other.finish;
}

Level& Level::operator=(Level& other)
{
	if(this == &other) return *this;

	Level temp(other);

	std::swap(tiles, temp.tiles);
	std::swap(clips, temp.clips);
	std::swap(name, temp.name);
	std::swap(tileSheetSource, temp.tileSheetSource);
	std::swap(tileSheet, temp.tileSheet);

	std::swap(LEVEL_WIDTH, temp.LEVEL_WIDTH);
	std::swap(LEVEL_HEIGHT, temp.LEVEL_HEIGHT);
	std::swap(TILE_WIDTH, temp.TILE_WIDTH);
	std::swap(TILE_HEIGHT, temp.TILE_HEIGHT);

	std::swap(TILE_SHEET_WIDTH, temp.TILE_SHEET_WIDTH);
	std::swap(TILE_SHEET_HEIGHT, temp.TILE_SHEET_HEIGHT);

	std::swap(finish, temp.finish);

	return *this;
}

void Level::load()
{
	using namespace rapidxml;

	std::string path = "resources/";
	path.append(name);
	std::ifstream levelFile;
	//std::cout << "filepath : " << path << std::endl;
	levelFile.open(path);
	std::string levelAsString((std::istreambuf_iterator<char>(levelFile)), std::istreambuf_iterator<char>());
	std::vector<char> data(levelAsString.begin(), levelAsString.end());
	xml_document<> doc;
	try {
		doc.parse<0>(&data[0]);
	} catch(...) { }

	// getting the data of the used map/level
	xml_node<> *map = doc.first_node("map");
	setupMapData(map);
	//std::cout << "map width: " << LEVEL_WIDTH << std::endl;
	//std::cout << "map height: " << LEVEL_HEIGHT << std::endl;
	//std::cout << "tile width: " << TILE_WIDTH << std::endl;
	//std::cout << "tile height: " << TILE_HEIGHT << std::endl;

	// getting information of the user spritesheet image
	xml_node<> *tileset = map->first_node("tileset");
	xml_node<> *image = tileset->first_node("image");
	getImageData(image);
	std::cout << "tilesheet path: " << tileSheetSource << std::endl;
	tileSheet = Logic::loadImage(tileSheetSource);
	//std::cout << "image name: " << tileSheetSource << std::endl;
	//std::cout << "image width: " << TILE_SHEET_WIDTH << std::endl;
	//std::cout << "image height: " << TILE_SHEET_HEIGHT << std::endl;

	createClips();

	// getting the tile data from a layer
	xml_node<> *layer = tileset->next_sibling("layer");
	createTiles(layer);


	// getting finish box
	xml_node<> *collisions = map->first_node("objectgroup");
	while(collisions != NULL){
		std::string name(collisions->first_attribute("name")->value());
		if(!name.compare("finish"))
		{
			break;
		}
		collisions = collisions->next_sibling("objectgroup");
	}
	xml_node<> *box = collisions->first_node("object");
	finish.x = xmlAttributeToInt(box, "x");
	finish.y = xmlAttributeToInt(box, "y");
	finish.w = xmlAttributeToInt(box, "width");
	finish.h = xmlAttributeToInt(box, "height");

}

void Level::setupMapData(rapidxml::xml_node<>* map)
{
	LEVEL_WIDTH = xmlAttributeToInt(map, "width");
	LEVEL_HEIGHT = xmlAttributeToInt(map, "height");
	TILE_WIDTH = xmlAttributeToInt(map, "tilewidth");
	TILE_HEIGHT  = xmlAttributeToInt(map, "tileheight");
}

void Level::getImageData(rapidxml::xml_node<>* image)
{
	tileSheetSource = "resources/";
	tileSheetSource.append(image->first_attribute("source")->value());
	TILE_SHEET_WIDTH = xmlAttributeToInt(image, "width");
	TILE_SHEET_HEIGHT = xmlAttributeToInt(image, "height");
}

void Level::createTiles(rapidxml::xml_node<>* layer)
{
	using namespace rapidxml;

	while(layer != NULL)
	{
		//std::cout << layer->first_attribute("name")->value() << std::endl;
		int x = 0;
		int y = 0;
		int i = 0;
		int j = 0;
		xml_node<> *data = layer->first_node("data");
		xml_node<> *tile = data->first_node("tile");
		while(tile != NULL)
		{
			int clipIndex = xmlAttributeToInt(tile, "gid");
			if(clipIndex != 0)
			{
				x = j * TILE_WIDTH;
				y = i * TILE_HEIGHT;
				tiles.push_back(Tile(x, y, TILE_WIDTH, TILE_HEIGHT, clipIndex));
			}
			j++;
			if(j >= LEVEL_WIDTH)
			{
				j = 0;
				i++;
			}
			tile = tile->next_sibling("tile");
		}
		layer = layer->next_sibling("layer");
	}
}

void Level::createClips()
{
	int TILE_COLUMNS = TILE_SHEET_WIDTH / TILE_WIDTH;
	int TILE_ROWS = TILE_SHEET_HEIGHT / TILE_HEIGHT;
	//std::cout << "TILE_COLUMNS: " << TILE_COLUMNS << std::endl;
	//std::cout << "TILE_ROWS: " << TILE_ROWS << std::endl;
	SDL_Rect empty = {0, 0, 0, 0};
	clips.push_back(empty);
	int x = 0;
	int y = 0;
	for(int i = 0; i < TILE_ROWS; i++) 
	{
		for(int j = 0; j < TILE_COLUMNS; j++) 
		{
			SDL_Rect clip;
			clip.x = x;
			clip.y = y;
			clip.w = TILE_WIDTH;
			clip.h = TILE_HEIGHT;
			clips.push_back(clip);
			x += TILE_WIDTH;
		}
		y += TILE_HEIGHT;
		x = 0;
	}
}

int Level::xmlAttributeToInt(rapidxml::xml_node<>* node, std::string attr)
{
	std::string id(node->first_attribute(attr.c_str())->value());
	std::stringstream ss(id);
	int value;
	ss >> value;
	return value;
}

bool Level::touchesWall(SDL_Rect box)
{
	return false;
}

void Level::draw(View& view)
{
	SDL_Rect camera = view.getCamera();
	for(unsigned int i = 0; i < tiles.size(); i++)
	{
		SDL_Rect box = tiles[i].getBox();
		/*		std::cout << "x: " << box.x << std::endl;
		std::cout << "y: " << box.y << std::endl;
		std::cout << "camera x: " << camera.x << std::endl; 
		std::cout << "camera y: " << camera.y << std::endl;*/
		if(Logic::checkCollision(camera, box))
		{
			int clipIdx = tiles[i].getClipIndex();
			if(clipIdx != 738)
			{

			}
			view.apply(box.x - camera.x, box.y - camera.y, tileSheet, &clips[clipIdx]);
		}
	}
}

SDL_Rect Level::getSize()
{
	SDL_Rect size;
	size.x = 0;
	size.y = 0;
	size.w = LEVEL_WIDTH * TILE_WIDTH;
	size.h = LEVEL_HEIGHT * TILE_HEIGHT;
	return size;
}

SDL_Rect Level::getFinish()
{
	return finish;
}

void Level::save(SaveNode& node)
{
	int nameLength = name.size(); // includes null terminator
	node.add("nameLength", nameLength);
	std::vector<char> cname(name.begin(), name.end());
	node.add("name", &cname[0], nameLength);
}
void Level::load(SaveNode& node)
{
	std::string n;
	int nameLength = 0;
	node.poll("nameLength", nameLength);
	std::vector<char> cname;
	cname.resize(nameLength);
	node.poll("name", &cname[0], nameLength);
	n.append(cname.begin(), cname.end());
	name = n;
	load();
	std::cout << n << std::endl;
}

Level::~Level()
{
	//SDL_FreeSurface(tileSheet);
}
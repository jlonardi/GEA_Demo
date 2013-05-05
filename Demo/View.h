#ifndef VIEW_H
#define VIEW_H

#include <Serializable.h>
#include <SDL.h>

class View : public Serializable
{
private:
	SDL_Surface *screen;
	//Screen attributes
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	int SCREEN_BPP;

	//The frames per second
	int FRAMES_PER_SECOND;

	SDL_Rect camera;
	bool fullScreen;

public:
	View();
	View(const View& other);
	View& operator= (const View& other);
	bool init();
	SDL_Rect getCamera();
	void setCamera(SDL_Rect& c);
	void render();
	void apply(int x, int y, SDL_Surface* source, SDL_Rect* clip = NULL );
	void save(SaveNode& node);
	void load(SaveNode& node);
	void toggleFullScreen();
	virtual ~View();
};

#endif
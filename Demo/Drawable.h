#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "View.h"

class Drawable {
public:
	virtual void draw(View& view) = 0;
};

#endif
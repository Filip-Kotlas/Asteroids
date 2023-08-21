#ifndef __LASER_H__
#define __LASER_H__

#include "Object.h"
class Laser : public Object
{
private:
	bool out_of_bound;

public:
	Laser(SDL_Renderer* rend, SDL_Texture* pict, Point position, float angle);
	~Laser();

	void move();
	void setOutOfBound(bool src) { out_of_bound = src; }
	bool isOutOfBound() { return out_of_bound; }
};

#endif //__LASER_H__
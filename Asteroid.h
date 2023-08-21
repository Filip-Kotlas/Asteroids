#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "Object.h"
#include "Spaceship.h"
#include "Laser.h"

class Asteroid :public Object
{
private:	
	ASTEROID_TYPE type;
	float angular_speed;
	Uint32 creation_time;

	void setCreation_time(Uint32 src) { creation_time = src; }

public:
	Asteroid(SDL_Renderer* rend, SDL_Texture* pict, Point spawn, ASTEROID_TYPE type);
	~Asteroid();

	void setType(ASTEROID_TYPE t) { this->type = t; }
	void setAngular_speed(float speed) { this->angular_speed = speed; }
	void setSize(int s) { this->width = s; this->height = s; }
	float getAngular_speed() { return this->angular_speed; }
	ASTEROID_TYPE getType() { return this->type; }

	void render();
	void turn();
	bool checkCollision(Object* other);

};

#endif //__ASTEROID_H__
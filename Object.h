#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Constants.h"

class Object
{
protected:
	SDL_Renderer* renderer;
	SDL_Texture* picture;
	Point position;
	Point velocity;
	int width;
	int height;
	float angle;
	int radius;

public:
	Object(SDL_Renderer* Rend, SDL_Texture* pict);
	~Object();

	void setPosition(Point src) { position = src; }
	void setVelocity(Point src) { velocity = src; }
	void setAngle(float src) { angle = src; }
	void setRadius(int src) { radius = src; }
	Point getPosition() { return position; }
	Point getVelocity() { return velocity; }
	float getAngle() { return angle; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getRadius() { return radius; }
	Point getCenter();

	void render();
	void move();

};

#endif //__OBJECT_H__
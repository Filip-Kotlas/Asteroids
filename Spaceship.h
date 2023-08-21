#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>

#include "Object.h"
#include "Constants.h"

class Spaceship : public Object
{
private:
	bool shooting;
	short num_lives;
	SDL_Texture* heart;

public:
	Spaceship(SDL_Renderer* rend, SDL_Texture* ship_pict, SDL_Texture* heart_pict);
	~Spaceship();

	void handleInput();
	bool isShooting() { return shooting; }
	bool isAlive() { return num_lives; }
	int getLives() { return num_lives; }
	void decrementLives() { num_lives--; }

	void render();
	

};


#endif //__SPACESHIP_H__

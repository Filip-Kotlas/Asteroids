#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <cstdlib>
#include <list>
#include <iterator>
#include <time.h>

#include "Point.h"


const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;
const unsigned int HEART_X_OFFSET = 25;
const unsigned int HEART_Y_OFFSET = 5;

const double DEG_TO_RAD = 0.017453292;
const float PI = 3.14159;

const float ENGINE_POWER = 0.2;
const float MAX_SPACESHIP_SPEED = 5;
const unsigned int SPACE_ROTATION_SPEED = 5;
const unsigned int SHOOTING_FREQENCY = 100;
const unsigned int NUMBER_OF_LIVES = 3;
const float FRICTION = 0.995;
const float BASIC_ASTEROID_SPEED = 2;
const int BASIC_ASTEROID_ANGULAR_SPEED = 2;
const int STARTING_NUMBER_OF_ASTEROIDS = 3;
const int SPACESHIP_RADIUS = 19;
const int LASER_SPEED = 10;
const int ASTEROID_SPAWN_TIME = 500; 

enum ASTEROID_TYPE
{
	TYPE_1,
	TYPE_2,
	TYPE_3,
	NUMBER_OF_ASTEROIDS
};

enum ASTEROID_SIZE
{
	SIZE_1 = 16,
	SIZE_2 = 32,
	SIZE_3 = 48
};

const SDL_Rect CLIPS[NUMBER_OF_ASTEROIDS] =
{
	{0, 0, SIZE_1, SIZE_1},
	{SIZE_1, 0, SIZE_2, SIZE_2},
	{SIZE_1 + SIZE_2, 0, SIZE_3, SIZE_3},
};

enum GAME_RESULT
{
	WIN,
	LOSS,
	EXITED
};

#endif //__CONSTANTS_H__

#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer* rend, SDL_Texture* pict, Point spawn, ASTEROID_TYPE type)
	: Object(rend, pict)
{
	setCreation_time(SDL_GetTicks());

	setType(type);

	setPosition(spawn); 

	float randAngle = (float)rand() / RAND_MAX * 2 * PI;
	float absolute_speed = BASIC_ASTEROID_SPEED;
	setVelocity(Point(cos(randAngle), sin(randAngle)) * absolute_speed);
	
	setAngular_speed((float)(rand() - RAND_MAX / 2) / (RAND_MAX / 2) * BASIC_ASTEROID_ANGULAR_SPEED);

	switch (type)
	{
	case TYPE_1:
		setRadius(SIZE_1/2);
		setSize(SIZE_1);
		break;
	case TYPE_2:
		setRadius(SIZE_2/2);
		setSize(SIZE_2);
		break;
	case TYPE_3:
		setRadius(SIZE_3/2);
		setSize(SIZE_3);
		break;
	}
}

Asteroid::~Asteroid()
{
}

void Asteroid::render()
{
	SDL_Rect destination = { getPosition().x, getPosition().y, CLIPS[type].w, CLIPS[type].h };
	SDL_RenderCopyEx(renderer, picture, &CLIPS[type], &destination, angle, nullptr, SDL_FLIP_NONE);
}

void Asteroid::turn()
{
	setAngle(getAngle() + getAngular_speed());
}

bool Asteroid::checkCollision(Object* other)
{
	Point other_center = other->getPosition() + Point(other->getWidth() / 2, other->getHeight() / 2);
	Point asteroid_center = this->getPosition() + Point(this->getWidth() / 2, this->getHeight() / 2);
	Point diff = other_center - asteroid_center;
	float distance = diff.getLengthSquared();

	if (distance <= (other->getRadius() + this->getRadius())*(other->getRadius() + this->getRadius()))
	{
		if (SDL_GetTicks() - creation_time < ASTEROID_SPAWN_TIME)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}
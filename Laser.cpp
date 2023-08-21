#include "Laser.h"

Laser::Laser(SDL_Renderer* rend, SDL_Texture* pict, Point position, float angle)
	:Object(rend, pict)
{
	setAngle(angle);

	Point absolut_speed;
	absolut_speed.x = sin(angle * DEG_TO_RAD) * LASER_SPEED;
	absolut_speed.y = -cos(angle * DEG_TO_RAD) * LASER_SPEED;
	setVelocity(absolut_speed);

	setPosition(position);
	setOutOfBound(false);
}

Laser::~Laser()
{

}

void Laser::move()
{
	setPosition(getPosition() + getVelocity());

	if (getPosition().x < -getWidth() || getPosition().x > SCREEN_WIDTH || getPosition().y < -getHeight() || getPosition().y > SCREEN_HEIGHT)
	{
		setOutOfBound(true);
	}
}
#include "Object.h"

Object::Object(SDL_Renderer* rend, SDL_Texture* pict)
{
	renderer = rend;
	picture = pict;
	SDL_QueryTexture(picture, nullptr, nullptr, &width, &height);
	setPosition(Point((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2));
	setVelocity(Point(0, 0));
	setAngle(0);
	setRadius(0);
}

Object::~Object()
{
	renderer = nullptr;
	picture = nullptr;
}

Point Object::getCenter()
{
	Point center;
	center.x = getPosition().x + getWidth() / 2;
	center.y = getPosition().y + getHeight() / 2;
	return center;
}

void Object::render()
{
	SDL_Rect destination = { getPosition().x, getPosition().y, getWidth(), getHeight() };
	SDL_RenderCopyEx(renderer, picture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE);
}

void Object::move()
{
	setPosition( getPosition() + getVelocity());

	if (getPosition().x < -getWidth())
	{
		setPosition(Point(SCREEN_WIDTH, getPosition().y));
	}
	if (getPosition().x > SCREEN_WIDTH)
	{
		setPosition(Point(-getWidth(), getPosition().y));
	}

	if (getPosition().y < -getHeight())
	{
		setPosition(Point(getPosition().x, SCREEN_HEIGHT));
	}
	if (getPosition().y > SCREEN_HEIGHT)
	{
		setPosition(Point(getPosition().x, -getHeight()));
	}
}

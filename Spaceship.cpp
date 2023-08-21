#include "Spaceship.h"

Spaceship::Spaceship(SDL_Renderer* rend, SDL_Texture* ship_pict, SDL_Texture* heart_pict)
	: Object(rend, ship_pict)
{
	heart = heart_pict;
	setRadius(SPACESHIP_RADIUS);
	num_lives = NUMBER_OF_LIVES;
	shooting = false;
}

Spaceship::~Spaceship()
{
}

void Spaceship::handleInput()
{
	const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
	
	if (keyStates[SDL_SCANCODE_UP])
	{
		if (this->getVelocity().getLengthSquared() < MAX_SPACESHIP_SPEED * MAX_SPACESHIP_SPEED)
		{
			Point delta;
			delta.x = sin(angle * DEG_TO_RAD) * ENGINE_POWER;
			delta.y = -cos(angle * DEG_TO_RAD) * ENGINE_POWER;
			setVelocity(getVelocity() + delta);
		}
	}
	setVelocity(getVelocity() * FRICTION);

	if (keyStates[SDL_SCANCODE_LEFT])
	{
		setAngle(getAngle() - SPACE_ROTATION_SPEED);
	}

	if (keyStates[SDL_SCANCODE_RIGHT])
	{
		setAngle(getAngle() + SPACE_ROTATION_SPEED);
	}

	if (keyStates[SDL_SCANCODE_SPACE])
	{
		shooting = true;
	}
	else
	{
		shooting = false;
	}

}

void Spaceship::render()
{
	SDL_Rect destination = { getPosition().x, getPosition().y, getWidth(), getHeight() };
	SDL_RenderCopyEx(renderer, picture, nullptr, &destination, angle, nullptr, SDL_FLIP_NONE);

	for (int i = 1; i <= getLives(); i++)
	{
		SDL_QueryTexture(heart, nullptr, nullptr, &destination.w, &destination.h);
		destination.x = SCREEN_WIDTH - i * HEART_X_OFFSET;
		destination.y = HEART_Y_OFFSET;
		SDL_RenderCopy(renderer, heart, nullptr, &destination);
	}
}
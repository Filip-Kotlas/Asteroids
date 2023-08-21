#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "Constants.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Laser.h"

bool init(SDL_Window * &Window, SDL_Renderer * &Renderer);

SDL_Texture* loadFromFile(SDL_Renderer* renderer, std::string path);

SDL_Texture* loadText(SDL_Renderer* renderer, std::string text, int size, SDL_Color color);

void moveObjects(Spaceship* spaceship, std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers);

void handleLaserHits(std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers, SDL_Renderer* renderer, SDL_Texture* asteroid_pict);

void handleAsteroidHits(Spaceship* spaceship, std::list<Asteroid*>& asteroids, SDL_Renderer* renderer, SDL_Texture* asteroid_pict);

void renderObjects(SDL_Renderer* renderer, Spaceship* spaceship, std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers, SDL_Texture* background_pict);

GAME_RESULT gameRun(SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* spaceship, SDL_Texture* asteroid, SDL_Texture* laser, SDL_Texture* heart_pict);

void renderToCentre(SDL_Renderer* renderer, SDL_Texture* picture);

void waitUntillExit();

void cleanUp(SDL_Window*& Window, SDL_Renderer*& Renderer);




#endif __FUNCTIONS_H__

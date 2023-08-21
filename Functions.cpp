#include "Functions.h"

bool init(SDL_Window*& Window, SDL_Renderer*& Renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL2 was not initialized. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		std::cout << "SDL2_image was not initialized. IMG_Error: " << IMG_GetError() << std::endl;
		return false;
	}
	if (TTF_Init())
	{
		std::cout << "SDL2_ttf was not initialized. TTF_Error: " << TTF_GetError() << std::endl;
		return false;
	}

	Window = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
	{
		std::cout << "Window was not created. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (Renderer == nullptr)
	{
		std::cout << "Renderer was not created. SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return true;
}

SDL_Texture* loadFromFile(SDL_Renderer* renderer, std::string path )
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
		return newTexture;
	}

	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == nullptr)
	{
		std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

SDL_Texture* loadText(SDL_Renderer* renderer, std::string text, int size, SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont("fonts/calibri.ttf", size);
	if (font == nullptr)
	{
		std::cout << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (text_surface == nullptr)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (text_texture == nullptr)
	{
		std::cout << "Unable to create texture from renderer text! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	return text_texture;
}

void moveObjects(Spaceship* spaceship, std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers)
{
	std::list<Asteroid*>::iterator asteroid_iterator;
	std::list<Laser*>::iterator laser_iterator;

	spaceship->move();
	for (asteroid_iterator = asteroids.begin(); asteroid_iterator != asteroids.end(); asteroid_iterator++)
	{
		(*asteroid_iterator)->move();
		(*asteroid_iterator)->turn();
	}
	for (laser_iterator = lasers.begin(); laser_iterator != lasers.end(); laser_iterator++)
	{
		(*laser_iterator)->move();
		if ((*laser_iterator)->isOutOfBound())
		{
			bool is_begin = true;
			delete (*laser_iterator);
			std::list<Laser*>::iterator eraser = laser_iterator;
			if (laser_iterator != lasers.begin())
			{
				is_begin = false;
				laser_iterator--;
			}
			lasers.erase(eraser);
			if (is_begin)
			{
				break;
			}
		}
	}
}

void handleLaserHits(std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers, SDL_Renderer* renderer, SDL_Texture* asteroid_pict)
{
	for (std::list<Laser*>::iterator laser_iterator = lasers.begin(); laser_iterator != lasers.end(); laser_iterator++)
	{
		bool is_collision = false;
		for (std::list<Asteroid*>::iterator asteroid_iterator = asteroids.begin(); asteroid_iterator != asteroids.end(); asteroid_iterator++)
		{
			is_collision = (*asteroid_iterator)->checkCollision(*laser_iterator);
			if (is_collision)
			{
				if ((*asteroid_iterator)->getType() > TYPE_1)
				{
					int int_type = static_cast<int>((*asteroid_iterator)->getType());
					ASTEROID_TYPE new_type = static_cast<ASTEROID_TYPE>(--int_type);
					asteroids.push_back(new Asteroid(renderer, asteroid_pict, (*asteroid_iterator)->getPosition(), new_type));
					asteroids.push_back(new Asteroid(renderer, asteroid_pict, (*asteroid_iterator)->getPosition(), new_type));
				}

				delete *asteroid_iterator;
				asteroids.erase(asteroid_iterator);

				delete *laser_iterator;
				lasers.erase(laser_iterator);

				break;
			}
		}
		if (is_collision)
		{
			break;
		}
	}
}

void handleAsteroidHits(Spaceship* spaceship, std::list<Asteroid*>& asteroids, SDL_Renderer* renderer, SDL_Texture* asteroid_pict)
{
	for (std::list<Asteroid*>::iterator asteroid_iterator = asteroids.begin(); asteroid_iterator != asteroids.end(); asteroid_iterator++)
	{
		if ((*asteroid_iterator)->checkCollision(spaceship))
		{
			spaceship->decrementLives();

			if ((*asteroid_iterator)->getType() > TYPE_1)
			{
				int int_type = static_cast<int>((*asteroid_iterator)->getType());
				ASTEROID_TYPE new_type = static_cast<ASTEROID_TYPE>(--int_type);
				asteroids.push_back(new Asteroid(renderer, asteroid_pict, (*asteroid_iterator)->getPosition(), new_type));
				asteroids.push_back(new Asteroid(renderer, asteroid_pict, (*asteroid_iterator)->getPosition(), new_type));
    			}

			bool is_begin = true;
			delete* asteroid_iterator;
			asteroids.erase(asteroid_iterator);
			break;
		}
	}
}

void renderObjects(SDL_Renderer* renderer, Spaceship* spaceship, std::list<Asteroid*>& asteroids, std::list<Laser*>& lasers, SDL_Texture* background_pict)
{
	SDL_RenderCopy(renderer, background_pict, nullptr, nullptr);

	for (std::list<Asteroid*>::iterator asteroid_iterator = asteroids.begin(); asteroid_iterator != asteroids.end(); asteroid_iterator++)
	{
		(*asteroid_iterator)->render();
	}
	for (std::list<Laser*>::iterator laser_iterator = lasers.begin(); laser_iterator != lasers.end(); laser_iterator++)
	{
		(*laser_iterator)->render();
	}
	spaceship->render();
	SDL_RenderPresent(renderer);
}

GAME_RESULT gameRun(SDL_Renderer* renderer, SDL_Texture* background_pict, SDL_Texture* spaceship_pict, SDL_Texture* asteroid_pict, SDL_Texture* laser_pict, SDL_Texture* heart_pict)
{
	GAME_RESULT result;
	Spaceship* spaceship = new Spaceship(renderer, spaceship_pict, heart_pict);
	std::list<Asteroid*> asteroids;
	std::list<Laser*> lasers;
	for (int i = 0; i < STARTING_NUMBER_OF_ASTEROIDS; i++)
	{
		Point spawn = Point(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
		asteroids.push_back(new Asteroid(renderer, asteroid_pict, spawn, TYPE_3));
	}
	
	SDL_Event e;
	int shooting_timer = 0;

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				result = EXITED;
			}
		}

		spaceship->handleInput();
		moveObjects(spaceship, asteroids, lasers);
		handleAsteroidHits(spaceship, asteroids, renderer, asteroid_pict);
		handleLaserHits(asteroids, lasers, renderer, asteroid_pict);
		
		

		// shooting lasers
		if (spaceship->isShooting() && (SDL_GetTicks() - shooting_timer) > SHOOTING_FREQENCY)
		{
			lasers.push_back(new Laser(renderer, laser_pict, spaceship->getCenter(), spaceship->getAngle()));
			shooting_timer = SDL_GetTicks();
		}

		//win
		if (asteroids.empty())
		{
			quit = true;
			result = WIN;
		}

		//lose
		if (spaceship->getLives() < 1)
		{
			quit = true;
			result = LOSS;
		}
		renderObjects(renderer, spaceship, asteroids, lasers, background_pict);
	}
	return result;
}

void renderToCentre(SDL_Renderer* renderer, SDL_Texture* picture)
{
	SDL_Rect centre;
	SDL_QueryTexture(picture, nullptr, nullptr, &centre.w, &centre.h);
	centre.x = (SCREEN_WIDTH - centre.w)/2;
	centre.y = (SCREEN_HEIGHT - centre.h) / 2;
	SDL_RenderCopy(renderer, picture, nullptr, &centre);

}

void waitUntillExit()
{
	SDL_Event e;
	bool exit = false;
	while (!exit)
	{
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
		{
			exit = true;
		}
	}
}

void cleanUp(SDL_Window*& Window, SDL_Renderer*& Renderer)
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = nullptr;
	Renderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
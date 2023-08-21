#include "Functions.h"


int main(int argc, char* args[])
{
	SDL_Window* main_window = nullptr;
	SDL_Renderer* main_renderer = nullptr;

	SDL_Texture* background_picture = nullptr;
	SDL_Texture* spaceship_picture = nullptr;
	SDL_Texture* asteroid_picture = nullptr;
	SDL_Texture* laser_picture = nullptr;
	SDL_Texture* heart_picture = nullptr;
	SDL_Texture* title_picture = nullptr;
	SDL_Texture* game_over_picture = nullptr;
	SDL_Texture* win_picture = nullptr;

	srand(time(nullptr));
	
	if (!init(main_window, main_renderer))
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		SDL_Color black = { 0, 0, 0 };
		SDL_Color red = { 255, 0, 0 };
		background_picture = loadFromFile(main_renderer, "pictures/Background.png");
		spaceship_picture = loadFromFile(main_renderer, "pictures/Spaceship.png");
		asteroid_picture = loadFromFile(main_renderer, "pictures/Asteroid.png");
		laser_picture = loadFromFile(main_renderer, "pictures/Laser.png");
		heart_picture = loadFromFile(main_renderer, "pictures/Heart.png");
		title_picture = loadText(main_renderer, "Asteroids", 80, black);
		game_over_picture = loadText(main_renderer, "Game Over", 60, red);
		win_picture = loadText(main_renderer, "You won", 60, red);


		if (background_picture == nullptr || spaceship_picture == nullptr || asteroid_picture == nullptr || laser_picture == nullptr || heart_picture == nullptr)
		{
			std::cout << "Could not load pictures. SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			/*SDL_SetRenderDrawColor(main_renderer, 255, 255, 255, 0);
			SDL_RenderClear(main_renderer);*/
			SDL_RenderCopy(main_renderer, background_picture, nullptr, nullptr);
			renderToCentre(main_renderer, title_picture);
			SDL_RenderPresent(main_renderer);
			SDL_Delay(2000);
			
			GAME_RESULT result;

			result = gameRun(main_renderer, background_picture, spaceship_picture, asteroid_picture, laser_picture, heart_picture);

			if(result == WIN)
			{
				renderToCentre(main_renderer, win_picture);
				SDL_RenderPresent(main_renderer);
				waitUntillExit();
			}
			else if (result == LOSS)
			{
				renderToCentre(main_renderer, game_over_picture);
				SDL_RenderPresent(main_renderer);
				waitUntillExit();
			}
		}
	}


	SDL_DestroyTexture(background_picture);
	SDL_DestroyTexture(spaceship_picture);
	SDL_DestroyTexture(asteroid_picture);
	SDL_DestroyTexture(laser_picture);
	SDL_DestroyTexture(heart_picture);
	SDL_DestroyTexture(title_picture);
	SDL_DestroyTexture(win_picture);
	SDL_DestroyTexture(game_over_picture);

	cleanUp(main_window, main_renderer);

	return 0;
}
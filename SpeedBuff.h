#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <ctime>


class SpeedBuff
{
public:
	
	const int WIDTH = 16;
	const int HEIGHT = 16;

	SpeedBuff();
	void Render(SDL_Renderer* Renderer, SDL_Texture* Texture);

	bool CollidesWith(SDL_Rect a, SDL_Rect& b);
	void Update();
	void newPos();
	void RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture);

	SDL_Surface* Surface = IMG_Load("./assets/speed_icon.png");
	SDL_Surface* IconSurface = IMG_Load("./assets/power_up.png");
	SDL_Rect Icon{ 0, 400 - 32, 32,32 };
	
	SDL_Rect shipRect{ 0,0,16,16 };

	int SPRITE_FRAME = 0;
	int SPRITE_NUM_FRAMES = 1;
	int alpha;
	bool speedBoosted = false;

	int bVelX, bVelY;
	int VEL = 5;
	SDL_Rect srcRect{ 0, 0, 128,128 };
	SDL_Rect shipSrcRect{ 0, 0, 16,16 };

	SDL_Event e;
};




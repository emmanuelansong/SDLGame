#pragma once

#include <SDL.h>
#include "SDL_image.h"
#include "Vector2D.h"

class ShieldBuff
{
	
public:
	const int WIDTH = 32;
	const int HEIGHT = 32;
	
	SDL_Surface* shieldSurface = IMG_Load("./assets/shield.png");
	SDL_Rect shieldRect{ 4000, 4000, 100,100 };
	
	ShieldBuff();

	Vector2D_Player Player;

	SDL_Rect srcRect{ 0, 0, 128,128 };
	
	SDL_Surface* IconSurface = IMG_Load("./assets/buff_icon.png");
	SDL_Rect Icon{WIDTH, 400 - HEIGHT,32,32 };

	void Input(SDL_Event &e);
	void setPos(int x, int y);
	bool CollidesWith(SDL_Rect& a, SDL_Rect& b);
	
	void Render(SDL_Renderer* Renderer, SDL_Texture* Texture);
	void RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture);

	int alpha;
	

	bool playerShielded;
};


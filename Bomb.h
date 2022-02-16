#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"
#include "ShieldBuff.h"
class Bomb : Vector2D_Player
{
public:
	Bomb();

	Vector2D_Player Player;

	virtual bool CollidesWith(SDL_Rect a, SDL_Rect& b);
	void Update();
	void Render(SDL_Renderer* Renderer, SDL_Texture* Texture);
	SDL_Surface* Surface = IMG_Load("assets/enemy-small.png");
	ShieldBuff SB;
	SDL_Rect rect{ 0,0,32,32};

	int SPRITE_FRAME = 0;
	int SPRITE_NUM_FRAMES = 1;

	int x, y;
	int R, G, B;
	bool inside;
	SDL_Rect srcRect{ 0,0,16,16 };
	
	int bVelX, bVelY;
	SDL_Event e;
	
	
	static const int BOMB_WIDTH = 16;
	static const int BOMB_HEIGHT = 16;

	int BOMB_VEL = 7;


	void newPos();
	
	
	
	
};


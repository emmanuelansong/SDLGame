#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Timer.h"
#include "ShieldBuff.h"
class BiggerBomb
{
public:
	Vector2D_Player Player;

	//bool checkCollision(SDL_Rect A, SDL_Rect B);
	BiggerBomb();

	SDL_Surface* IconSurface = IMG_Load("./assets/meteor_icon.png");
	SDL_Rect Icon{ 64, 400 - 32, 32,32 };
	bool CollidesWith(SDL_Rect a, SDL_Rect& b);
	void Update();
	void Render(SDL_Renderer* Renderer, SDL_Texture* Texture);
	void RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture);
	SDL_Surface* Surface = IMG_Load("./assets/enemy-big.png");
	ShieldBuff SB;
	SDL_Rect rect{ 0,0,64,64 };

	int SPRITE_FRAME = 1;
	int SPRITE_NUM_FRAMES = 1;

	int x, y;
	int R, G, B;
	bool inside;
	SDL_Rect srcRect{ 0,0,32,32 };

	int bVelX, bVelY;
	SDL_Event e;
	int alpha = 255;
	bool slowedDown;
	static const int BOMB_WIDTH = 64;
	static const int BOMB_HEIGHT = 64;

	static const int BOMB_SPRITE_WIDTH = 32;
	static const int BOMB_SPRITE_HEIGHT = 64;

	int BOMB_VEL = 4;


	void newPos();
};


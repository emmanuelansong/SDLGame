#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "Timer.h"
#include "SpeedBuff.h"

class Vector2D_Player : SpeedBuff
{
public:
	Vector2D_Player();
	
	Timer Timer;
	
	SDL_Surface* Surface = IMG_Load("./assets/ship.png");
	SDL_Surface* CrosshairSurface = IMG_Load("./assets/crosshair038.png");
	
	
	static const int PLAYER_WIDTH = 18;
	static const int PLAYER_HEIGHT = 26;

	int PLAYER_VEL = 10;
	
	SDL_Rect srcRect = { 0,0, PLAYER_WIDTH, PLAYER_HEIGHT };
	
	SDL_Rect r = { 200, 300 - PLAYER_HEIGHT, 32,32};

	int SPRITE_FRAME = 0;
	int SPRITE_NUM_FRAMES = 9;

	SDL_Event e;

	SDL_Rect POS;
	
	
	int pVelX, pVelY;
	
	int lives = 3;
	bool keyPressed = false;
	
	
	void Input(SDL_Event& e);
	void setPos(int x, int y);
	bool CollidesWith(SDL_Rect& a, SDL_Rect& b);
	void Update();
	void Render(SDL_Renderer* Renderer, SDL_Texture* Texture);
	
};



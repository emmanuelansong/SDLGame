#pragma once
#include <iostream>
#include "SDL.h"
#include "Timer.h"
#include <SDL_mixer.h>
#include "Vector2D.h"
#include "ShieldBuff.h"
#include "SDL_image.h"


using namespace std;
class Square
{
public:
	Square();
	
	~Square();
	int WIDTH = 16;
	int HEIGHT = 16;
	int score = 0;
	int VEL = 1;
	int sVelX = 0;
	ShieldBuff SB;
	Vector2D_Player Player;
	Timer Timer;
	
	void newPos(SDL_Rect &r);
	
	void Update();
	void Input(SDL_Event &e);
	void Render(SDL_Renderer* Renderer);
	SDL_Rect rect{ 0,0,WIDTH,HEIGHT };
	SDL_Event e;

	int SPRITE_FRAME = 0;
	int SPRITE_NUM_FRAMES = 49;
	SDL_Rect srcRect = { 0,0, 16, 16 };
	int misses = 0;

	bool inside;

	bool update = false;

private:
	int x, y;
	int R, G, B;
	
	
};

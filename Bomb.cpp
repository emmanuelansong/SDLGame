#include "Bomb.h"

Bomb::Bomb()
{
    R = 0;
    G = 0;
    B = 0;
    srand(time(NULL));
    //bVelX = rand() % BOMB_VEL;
    bVelX = rand() % BOMB_VEL;
    newPos();
   
}

bool Bomb::CollidesWith(SDL_Rect a, SDL_Rect& b)
{
    bool collision = true;
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    if (true)
    {

        
    }
    //If none of the sides from A are outside B

    return true;

}

void Bomb::Update()
{
    bVelY += BOMB_VEL;
    rect.y += bVelY;
    
    SPRITE_FRAME++;
    srcRect.x = BOMB_WIDTH * SPRITE_FRAME;

    if (SPRITE_FRAME = SPRITE_NUM_FRAMES)
    {
        SPRITE_FRAME--;
    }
    if (bVelY > BOMB_VEL)
    {
        bVelY = BOMB_VEL;
    }

    if (rect.y + BOMB_HEIGHT + 10 > 400)
    {
        newPos();
    }

}

void Bomb::newPos()
{
    rect.x = rand() % (400 - BOMB_WIDTH);
    rect.y = 0;

}
void Bomb::Render(SDL_Renderer* Renderer, SDL_Texture* Texture)
{

    SDL_RenderCopy(Renderer, Texture, &srcRect, &rect);
}


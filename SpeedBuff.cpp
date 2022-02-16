#include "SpeedBuff.h"
#include "Timer.h"

SpeedBuff::SpeedBuff()
{
    
}

//render ship
void SpeedBuff::Render(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
   
    SDL_RenderCopy(Renderer, Texture, &shipSrcRect, &shipRect);

}
//render speed buff icon
void SpeedBuff::RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    
    if (speedBoosted)
    {
        alpha = 255;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }
    if (!speedBoosted)
    {
        alpha = 63;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }

}
void SpeedBuff::Update()
{
    
    bVelY += VEL;
  
    shipRect.y += bVelY;

    if (bVelY > VEL)
    {
        bVelY = VEL;
    }

    if (shipRect.y + HEIGHT + 10> 400)
    {
        newPos();
    }

}

void SpeedBuff::newPos()
{
    shipRect.x = rand() % (400 - WIDTH) ;
    shipRect.y = 0;

}

bool SpeedBuff::CollidesWith(SDL_Rect a, SDL_Rect& b)
{
   
    
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

    return true;

}



#include "BiggerBomb.h"
#include "Bomb.h"

BiggerBomb::BiggerBomb()
{
    R = 0;
    G = 0;
    B = 0;
    srand(time(NULL));
    
    bVelX = rand() % BOMB_VEL;
    newPos();

}

bool BiggerBomb::CollidesWith(SDL_Rect a, SDL_Rect& b)
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

void BiggerBomb::Update()
{
    bVelY += BOMB_VEL;
    rect.y += bVelY;

    SPRITE_FRAME++;
    srcRect.x = BOMB_SPRITE_WIDTH * SPRITE_FRAME;

    if (bVelY > BOMB_VEL)
    {
        bVelY = BOMB_VEL;
    }

    if (rect.y + BOMB_HEIGHT + 10 > 400)
    {
        newPos();
    }

}

void BiggerBomb::newPos()
{
    rect.x = rand() % (400 - BOMB_WIDTH);
    rect.y = 0;

}
void BiggerBomb::Render(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    if (SPRITE_FRAME >= SPRITE_NUM_FRAMES)
    {
        SPRITE_FRAME = 0;
    }

    if (SPRITE_FRAME < 0)
        SPRITE_FRAME = SPRITE_NUM_FRAMES - 1;

    SDL_RenderCopy(Renderer, Texture, &srcRect, &rect);

}

void BiggerBomb::RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    if (slowedDown)
    {
        alpha = 255;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }
    if (!slowedDown)
    {
        alpha = 63;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }
}
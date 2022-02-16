#include "ShieldBuff.h"

ShieldBuff::ShieldBuff()
{
    playerShielded = true;
}
void ShieldBuff::Input(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        playerShielded = true;
    }
}
void ShieldBuff::setPos(int x, int y)
{
    shieldRect.x = Player.r.x - 32;
    shieldRect.y = Player.r.y - 32;
}

bool ShieldBuff::CollidesWith(SDL_Rect& a, SDL_Rect& b)
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

    return true;
}

void ShieldBuff::Render(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    if (playerShielded)
    {
        alpha = 255;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &shieldRect);

    }
    if (!playerShielded)
    {
        alpha = 0;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &shieldRect);

    }

}

void ShieldBuff::RenderIcon(SDL_Renderer* Renderer, SDL_Texture* Texture)
{

    if (playerShielded)
    {
        alpha = 255;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }
    if (!playerShielded)
    {
        alpha = 63;
        SDL_SetTextureAlphaMod(Texture, alpha);
        SDL_RenderCopy(Renderer, Texture, NULL, &Icon);
    }


}



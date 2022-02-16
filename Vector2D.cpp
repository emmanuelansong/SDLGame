#include "Vector2D.h"

#include <iostream>

Vector2D_Player::Vector2D_Player()
{

    POS.x = 0;
    POS.y = 0;
	
    //cursor
    POS.h = 64;
    POS.w = 64;

    pVelX = pVelY = 0;
 
}

void Vector2D_Player::setPos(int x, int y)
{
    //offset cursor
    POS.x = x - 32; 
    POS.y = y - 32;

    

}
bool Vector2D_Player::CollidesWith(SDL_Rect& a, SDL_Rect& b)
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
void Vector2D_Player::Input(SDL_Event& e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    char timestr[32];
    Timer.getTime(timestr, 32);

    //if cursor inside square...
    if (e.type == SDL_MOUSEMOTION)
        //update cursor pos
        setPos(x, y);
    
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    
    Timer.getTime(Timer.timestr, 32);
    if (keyPressed)
    {
        PLAYER_VEL = 5;
    }

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            SDL_Log("[%s] [KEY DOWN] [A] [%i]", Timer.timestr, e.key.timestamp);
            if (currentKeyStates[SDL_SCANCODE_LSHIFT])
            {
                SDL_Log("[%s] [KEY DOWN] [LSHIFT] [%i]", Timer.timestr, e.key.timestamp);
                pVelX -= (PLAYER_VEL / 2);
                pVelY = 0;
            }
            else
            {
                pVelX -= PLAYER_VEL;
                pVelY = 0;
            }
            //left
            

            break;
            
        case SDLK_d:
            //right
            SDL_Log("[%s] [KEY DOWN] [D] [%i]", Timer.timestr, e.key.timestamp);
            if (currentKeyStates[SDL_SCANCODE_LSHIFT])
            {
                SDL_Log("[%s] [KEY DOWN] [LSHIFT] [%i]", Timer.timestr, e.key.timestamp);
                pVelX += (PLAYER_VEL / 2);
                pVelY = 0;
            }
            else
            {
                pVelX += PLAYER_VEL;
                pVelY = 0;
            }
            break;
            
        }
        
        
    }


    if (e.type == SDL_KEYUP)
    {
        keyPressed = false;
    }
    
    if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
            //left
            SDL_Log("[%s] [KEY UP] [A] [%i]", Timer.timestr, e.key.timestamp);
            pVelY = 0;
            pVelX = 0;
            break;
            
            break;
        case SDLK_d:
            //right
            SDL_Log("[%s] [KEY UP] [A] [%i]", Timer.timestr, e.key.timestamp);
            pVelY  = 0;
            pVelX = 0;
            break;
        case SDLK_LSHIFT:
            SDL_Log("[%s] [KEY up] [LSHIFT] [%i]", Timer.timestr, e.key.timestamp);
            break;
        }
    }

}

void Vector2D_Player::Update()
{
    SPRITE_FRAME++;
    srcRect.x = PLAYER_WIDTH * SPRITE_FRAME;
    //keyPressed = false;
   
    if (!speedBoosted)
    {
        r.x += pVelX;
    }

    if (speedBoosted)
    {
        
        r.x += pVelX;
        
    }
   

    
    if (r.x < 0 || r.x + PLAYER_WIDTH >(400 - (PLAYER_WIDTH / 2)))
    {
        r.x -= pVelX;
    }

    if (pVelX > PLAYER_VEL)
    {
        pVelX -= PLAYER_VEL;                
    }

    if (pVelX < -PLAYER_VEL)
    {
        pVelX = -PLAYER_VEL;
    }
}

void Vector2D_Player::Render(SDL_Renderer* Renderer, SDL_Texture* Texture)
{
    if (SPRITE_FRAME >= SPRITE_NUM_FRAMES)
    {
        SPRITE_FRAME = 0;
    }

    if (SPRITE_FRAME < 0) 
        SPRITE_FRAME = SPRITE_NUM_FRAMES - 1;


    //player sprite
    SDL_RenderCopy(Renderer, Texture, &srcRect, &r);

}

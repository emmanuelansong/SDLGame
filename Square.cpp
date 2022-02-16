#include "Square.h"


Square::Square()
{
    rect.x = rand() % 350;
    rect.y = rand() % 250;
    
    R = 255;
    G = 255;
    B = 0;
    
    
}
Square::~Square()
{
    
}

void Square::Input(SDL_Event &e)
{

    
    if (e.type == SDL_MOUSEMOTION)
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        //Check if mouse is in button
    bool inside = true;
        
    //Mouse is left of the button
    if (x < rect.x)
    {
        inside = false;
    }
    //Mouse is right of the button
    else if (x > rect.x + WIDTH)
    {
        inside = false;
    }
    //Mouse above the button
    else if (y < rect.y)
    {
        inside = false;
    }
    //Mouse below the button
    else if (y > rect.y+ HEIGHT)
    {
        inside = false;
    }

    if (inside)
    {
        
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            update = true;
            score++;

            Timer.getTime(Timer.timestr, 32);
              
            newPos(rect);

            SDL_Log("[%s] SCORE: %i time: %d", Timer.timestr, score, e.key.timestamp);
                
        }
        
    }

    else
    {
        
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            update = false;
            
            misses++;
            SDL_Log("[TARGET MISSED] [MISSES: %i]", misses);
        }
             
    }

}
void Square::Update()
{
    
    sVelX += VEL;
    rect.x += sVelX;

    if (sVelX > VEL)
    {
        sVelX = VEL;
    }

    if (rect.x + rect. w + 1> 400)
    {
        newPos(rect);
    }
    if (rect.x < 0)
    {
        newPos(rect);
    }

    if (sVelX < VEL)
    {
        sVelX = -VEL;
    }
}
void Square::newPos(SDL_Rect &r)
{
    r.x = rand() % 350;
    
    r.y = rand() % 250;

}
void Square::Render(SDL_Renderer* Renderer)
{
    SDL_SetRenderDrawColor(Renderer,  R, G, B, 255);
    SDL_RenderFillRect(Renderer, &rect);

}


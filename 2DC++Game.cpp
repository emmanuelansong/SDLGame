#include <iostream>
#include <ctime>
#include "SDL.h"
#include <SDL_mixer.h>
#include "SDL_Image.h"
#include "Bomb.h"
#include "Timer.h"
#include "Square.h"
#include "Vector2D.h"
#include "ShieldBuff.h"
#include "SpeedBuff.h"
#include "BiggerBomb.h"
#include "SDL_ttf.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
    bool done = false;
    bool gameStart = false;
    Timer Timer;

    SDL_Event _event;
    Vector2D_Player Player;
    Square SQ;
    Bomb Bomb;
    ShieldBuff SB;
    SpeedBuff Speed;
    BiggerBomb BB;

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    if (TTF_Init() == -1)
    {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

    }

    Mix_Music* backgroundMusic = NULL;
    Mix_Chunk* laser = NULL;
    Mix_Chunk* oneUp = NULL;
    Mix_Chunk* shieldGain = NULL;
    Mix_Chunk* shieldGone = NULL;
    Mix_Chunk* Boost = NULL;
    Mix_Chunk* Hit = NULL;

    TTF_Font* Font = TTF_OpenFont("./assets/arial.ttf", 128);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initalise Mixer");

    }

    if (IMG_Init(SDL_INIT_EVERYTHING) == 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load SDL Image Library");
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load initialise");
    }

    SDL_Window* Window = SDL_CreateWindow("Emmanuel Ansong, CGP2015M, 19700916, 2D C++ Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_Renderer* Renderer2 = SDL_CreateRenderer(Window, 1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* MainSurface = IMG_Load("assets/background.png");
    SDL_Texture* MainTexture = SDL_CreateTextureFromSurface(Renderer, MainSurface);

    SDL_Texture* BombTexture = SDL_CreateTextureFromSurface(Renderer, Bomb.Surface);
    SDL_Texture* BBTexture = SDL_CreateTextureFromSurface(Renderer, BB.Surface);
    SDL_Texture* PlayerTexture = SDL_CreateTextureFromSurface(Renderer, Player.Surface);

    SDL_Texture* SpeedTexture = SDL_CreateTextureFromSurface(Renderer, Speed.Surface);
    SDL_Texture* SpeedIcon = SDL_CreateTextureFromSurface(Renderer, Speed.IconSurface);

    SDL_Texture* Shield = SDL_CreateTextureFromSurface(Renderer, SB.shieldSurface);
    SDL_Texture* ShieldIcon = SDL_CreateTextureFromSurface(Renderer, SB.IconSurface);

    SDL_Texture* BiggerBombIcon = SDL_CreateTextureFromSurface(Renderer, BB.IconSurface);

    SDL_Texture* Crosshairs = SDL_CreateTextureFromSurface(Renderer, Player.CrosshairSurface);

    

    SDL_BlendMode blending{ SDL_BLENDMODE_BLEND };

    const char* text = "2D C++ SDL GAME\n\nMOVE LEFT = A\nMOVE RIGHT = D\nLEFT MOUSE = SHOOT\nSHIFT = MOVE SLOWLY\n\nPRESS SPACEBAR TO BEGIN";
    const char* scoreText = "Score:";

    //get score, init 0
    //change from int -> string
    //output to text

    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color scoreTextColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(Font, text, textColor, 1500);
    SDL_Surface* scoreboard = TTF_RenderText_Blended(Font, scoreText, scoreTextColor);

    if (textSurface == NULL)
    {
        SDL_Log("Unable to create texture from rendered text! 2SDL Error: %s\n", SDL_GetError());
    }
    SDL_Texture* FontTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
    SDL_Texture* ScoreTexture = SDL_CreateTextureFromSurface(Renderer, scoreboard);


    SDL_Rect Title{ 0,0,600,400 };

    SDL_Rect scoreRect{ 225,375,100,25 };
    SDL_Rect scoreValRect{ 365,375,25,25 };

    const char* scoreTextVal = "0";
    SDL_Surface* scoreboardVal = TTF_RenderText_Blended_Wrapped(Font, scoreTextVal, scoreTextColor, 1500);
    SDL_Texture* ScoreValTexture = SDL_CreateTextureFromSurface(Renderer, scoreboardVal);
    SDL_GetTextureBlendMode(ShieldIcon, &blending);
    if (FontTexture == NULL)
    {
        SDL_Log("Unable to create texture from rendered text! 1SDL Error: %s\n", SDL_GetError());
    }

    if (Font == NULL)
    {
        SDL_Log("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    SDL_FreeSurface(MainSurface);
    SDL_FreeSurface(Bomb.Surface);
    SDL_FreeSurface(BB.Surface);
    SDL_FreeSurface(Player.Surface);
    SDL_FreeSurface(Player.CrosshairSurface);
    SDL_FreeSurface(SB.shieldSurface);
    SDL_FreeSurface(SB.IconSurface);
    SDL_FreeSurface(Speed.Surface);
    SDL_FreeSurface(Speed.IconSurface);
    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(scoreboard);
    scoreboardVal = TTF_RenderText_Blended(Font, scoreTextVal, scoreTextColor);

    if (SQ.update)
    {
        ScoreValTexture = SDL_CreateTextureFromSurface(Renderer, scoreboardVal);

    }
    SDL_FreeSurface(scoreboardVal);
    SDL_Rect dstRect{ 0,0,400,400 };

    int currentTime = 0;
    int timeElapsed = 0;
    int startTime = currentTime;

    int playbackrate = 50;


    SDL_Log("START TIME: %i", startTime / 100);
    backgroundMusic = Mix_LoadMUS("./assets/battle.wav");
    laser = Mix_LoadWAV("./assets/laser1.wav");
    oneUp = Mix_LoadWAV("./assets/Coin01.wav");
    // shieldGain = Mix_LoadWAV("./assets/FX01.wav");
    shieldGone = Mix_LoadWAV("./assets/Downer01.wav");
    Boost = Mix_LoadWAV("./assets/FX02.wav");
    Hit = Mix_LoadWAV("./assets/hit.wav");

    int FXvolume = 130;
    int backgroundVolume = 50;
    int timestamp = 0;

    Timer.getTime(Timer.timestr, 32);

    while (!gameStart)
    {
        void Init();
        {
            SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

            SDL_RenderClear(Renderer);
            SDL_RenderCopy(Renderer, FontTexture, NULL, &Title);

            SDL_RenderPresent(Renderer);

        }

        if (SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                gameStart = true;
                break;
            }
            if (_event.type == SDL_KEYDOWN)
            {
                switch (_event.key.keysym.sym)
                {
                case SDLK_ESCAPE:

                    gameStart = true;
                    done = true;
                    break;

                case SDLK_SPACE:

                    timestamp = _event.key.timestamp;
                    gameStart = true;
                    done = false;

                    break;
                }
            }
        }

    }

    if (gameStart && !done)
    {
        Mix_Volume(1, FXvolume);
        Mix_VolumeMusic(backgroundVolume);

        Mix_PlayMusic(backgroundMusic, -1);

        SDL_SetWindowSize(Window, 400, 400);
    }

    while (gameStart && !done)
    {

        currentTime = SDL_GetTicks() - timestamp;
        int deltaTime = currentTime - startTime;
        timeElapsed += deltaTime;
        startTime = currentTime;

        if ((currentTime % 1000) == 0)
        {
            SDL_Log("TIME REMAINING: %i", currentTime / 1000);
            //cout << timestamp << endl;
            if (currentTime / 1000 == 60)

                done = true;
        }
        void Input();
        {
            bool fullscreen = false;
            while (SDL_PollEvent(&_event))
            {
                if (_event.type == SDL_QUIT)
                {
                    done = true;
                }
                if (_event.type == SDL_MOUSEBUTTONDOWN && _event.key.repeat == 0)
                {
                    if (_event.button.button == SDL_BUTTON_LEFT)
                    {
                        Mix_VolumeChunk(laser, 20);
                        Mix_PlayChannel(1, laser, 0);
                        break;

                        if (SQ.inside)
                        {
                            
                            Mix_VolumeChunk(oneUp, 128);
                            Mix_PlayChannel(1, oneUp, 0);
                            break;
                        }
                       
                    }
                }
                if (_event.type == SDL_KEYDOWN)
                {
                    switch (_event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:

                        done = true;
                        break;

                    case SDLK_f:
                        if (fullscreen == false)
                        {

                            SDL_Log("[%s] [ENTERED FULLSCREEN]", Timer.timestr);
                            SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            //SDL_SetWindowBordered(Window, SDL_TRUE);
                        }
                        break;



                    case SDLK_m:
                        if (Mix_PlayingMusic() == 0)
                        {
                            Mix_PlayMusic(backgroundMusic, -1);
                        }
                        else
                        {
                            //If the music is paused
                            if (Mix_PausedMusic() == 1)
                            {
                                //set volume
                                //Mix_VolumeMusic(volume);
                                //Resume the music
                                SDL_Log("[%s] [MUSIC RESUMED]", Timer.timestr);
                                Mix_VolumeMusic(backgroundVolume);
                                Mix_Volume(1, FXvolume);
                                Mix_ResumeMusic();
                            }
                            //If the music is playing
                            else
                            {
                                //Mute all sounds + Pause music
                                //
                                SDL_Log("[%s] [MUSIC MUTED]", Timer.timestr);
                                Mix_Volume(-1, 0);
                                Mix_PauseMusic();

                            }
                        }
                        break;
                    case SDLK_RIGHTBRACKET:
                        FXvolume += 10;
                        Mix_Volume(-1, FXvolume);
                        SDL_Log("[INCREASING FX VOLUME: %i]", FXvolume);

                        if (FXvolume > 100)
                        {
                            FXvolume = 100;

                        }
                        break;
                    case SDLK_LEFTBRACKET:

                        FXvolume -= 10;
                        Mix_Volume(1, FXvolume);
                        SDL_Log("[%s][DECREASING FX VOLUME: %i]", Timer.timestr, FXvolume);

                        if (FXvolume < 0)
                        {
                            FXvolume = 0;

                        }
                        break;
                    case SDLK_EQUALS:

                        backgroundVolume += 10;
                        Mix_VolumeMusic(backgroundVolume);
                        SDL_Log("[%s] [INCREASING BACKGROUND VOLUME: %i]", Timer.timestr, backgroundVolume);

                        if (backgroundVolume > 100)
                        {
                            backgroundVolume = 100;

                        }
                        break;
                    case SDLK_MINUS:

                        backgroundVolume -= 10;
                        Mix_VolumeMusic(backgroundVolume);
                        SDL_Log("[%s] [DECREASING BACKGROUND VOLUME: %i]", Timer.timestr, backgroundVolume);
                        if (backgroundVolume < 0)
                        {
                            backgroundVolume = 0;
                        }
                        break;
                    }


                }

                Player.Input(_event);
                SQ.Input(_event);

            }


        }
        void Update();
        {

            if (Player.POS.y > 400 || Player.POS.y + Player.POS.h > 400)
            {
                SDL_WarpMouseInWindow(Window, 200, 200);
            }

            if (timeElapsed > playbackrate)
            {
                timeElapsed = 0;

                if (playbackrate <= 30)
                {
                    playbackrate = 30;
                }

                //no shield, bomb collision
                if (!SB.playerShielded)
                {
                    if (Bomb.CollidesWith(Bomb.rect, Player.r))
                    {
                        Mix_PlayChannel(1, Hit, 0);
                        SB.playerShielded = false;
                        Speed.speedBoosted = false;
                        Player.PLAYER_VEL = 5;
                        Player.lives--;

                        if (currentTime)
                            SDL_Log("[%s] [COLLISION] [BOMB] Lives = %i", Timer.timestr, Player.lives);

                        Bomb.newPos();
                    }
                    //no shield, bigger bomb collision
                    if (BB.CollidesWith(BB.rect, Player.r))
                    {
                       
                        BB.slowedDown = true;
                        Mix_PlayChannel(1, Hit, 0);
                        SB.playerShielded = false;
                        playbackrate -= 10;
                        SDL_Log("Playback is: %i", playbackrate);
                        Player.lives--;

                        if (currentTime)
                            

                        BB.newPos();
                        
                    }
                }
                //with shield, bomb collision
                if (SB.playerShielded)
                {
                    if (Bomb.CollidesWith(Bomb.rect, SB.shieldRect))
                    {

                        //disable shield
                        Mix_PlayChannel(1, shieldGone, 0);
                        SB.playerShielded = false;
                        
                        SDL_Log("[%s] [SHIELD DEACTIVATED]", Timer.timestr);
                        Bomb.newPos();
                    }

                    if (BB.CollidesWith(BB.rect, SB.shieldRect))
                    {

                        //disable shield
                        Mix_PlayChannel(1, shieldGone, 0);
                        SB.playerShielded = false;
                        //Speed.speedBoosted = false;
                        SDL_Log("[%s] [SHIELD DEACTIVATED]", Timer.timestr);
                        BB.newPos();
                    }
                    //with shield, bigger bomb collision
                }

                //if player gained shield
                if (SB.playerShielded)
                {
                    SB.shieldRect.x = Player.r.x - 32;
                    SB.shieldRect.y = Player.r.y - 32;
                }
                if (Player.lives == 0)
                {
                    done = true;
                }
                //
                //if player gained boost
                if (Speed.CollidesWith(Speed.shipRect, Player.r))
                {
                    BB.slowedDown = false;
                    playbackrate = 50;
                    
                    if (!SB.playerShielded)
                    {
                        SDL_Log("[%s] [SHIELD ACTIVATED]", Timer.timestr);
                        SB.playerShielded = true;
                    }
                    //if player didnt already have speed/ shield boost
                    if (!Speed.speedBoosted)
                    {
                        SDL_Log("[%s] [BOOST ACTIVATED]", Timer.timestr);
                        Mix_PlayChannel(1, Boost, 0);
                        Speed.speedBoosted = true;
                        Player.PLAYER_VEL = 20;

                    }

                }

                Player.Update();
                BB.Update();
                Bomb.Update();
                SQ.Update();
                Speed.Update();

            }

        }
        void ShowText();
        {
            int k = SQ.score;

            stringstream ss;
            ss << SQ.score;
            string s;
            ss >> s;

            scoreTextVal = s.c_str();

            scoreboardVal = TTF_RenderText_Blended(Font, scoreTextVal, scoreTextColor);

            if (SQ.update)
            {
                ScoreValTexture = SDL_CreateTextureFromSurface(Renderer, scoreboardVal);
                //SDL_DestroyTexture(ScoreValTexture);
            }
            SDL_FreeSurface(scoreboardVal);

        }

        void Render();
        {
            SDL_ShowCursor(SDL_DISABLE);

            SDL_RenderCopy(Renderer, MainTexture, NULL, &dstRect);
            SQ.Render(Renderer);

            SB.Render(Renderer, Shield);
            SB.RenderIcon(Renderer, ShieldIcon);

            Speed.Render(Renderer, SpeedIcon);
            Speed.RenderIcon(Renderer, SpeedTexture);

            Player.Render(Renderer, PlayerTexture);

            Bomb.Render(Renderer, BombTexture);
            BB.Render(Renderer, BBTexture);
            BB.RenderIcon(Renderer, BiggerBombIcon);
            SDL_RenderCopy(Renderer, ScoreTexture, NULL, &scoreRect);
            SDL_RenderCopy(Renderer, ScoreValTexture, NULL, &scoreValRect);

            SDL_RenderCopy(Renderer, Crosshairs, NULL, &Player.POS);
            //SDL_RenderCopy(Renderer, Texture, &srcRect, &dstRect);
            SDL_RenderPresent(Renderer);
        }
        if (done)
        {
            SDL_Log("[GAME OVER] [SCORE: %i] [MISSES: %i] [TIME REMAINING: %i]", SQ.score, SQ.misses, 60 - (currentTime / 1000));
            SDL_Log("Exiting game...");
            IMG_Quit();
            Mix_CloseAudio();
            SDL_DestroyRenderer(Renderer);
            SDL_DestroyWindow(Window);
            SDL_DestroyTexture(MainTexture);
            SDL_DestroyTexture(ScoreValTexture);
        }

    }



    return 0;
};


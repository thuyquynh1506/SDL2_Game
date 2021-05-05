#pragma once
#include <iostream>
#include <SDL_rect.h>
#include <SDL.h>

using namespace std;

class Animation
{
public:
    string name = "";
    int duration = 0;
    int angleRotate = 0;
    Uint32 tmpTime = NULL;
    Uint32 startTime = NULL;
    Uint32 waitTime = NULL;

    bool ended = false;

    SDL_Point transformVector = {NULL,NULL};
    SDL_Texture* tmpTexture = NULL;
    Animation(string name, int duration);
    Animation(string name, int duration,int waitTime);
    Animation(string name, int duration, double angleRotate, int waitTime);
    Animation(string name, int duration,SDL_Point transformVector, int waitTime);
    Animation(string name, int duration, SDL_Texture* tmpTexture, int waitTime);
    ~Animation();
};

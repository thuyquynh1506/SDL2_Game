#pragma once
#include <iostream>
#include <string>
#include <SDL_mixer.h>
#include "commonFunction.h"
#include "board.h"

class Tetris
{
    public:
        SDL_Renderer* gRenderer;
        SDL_Event event;

        Board board;
        typeBlocks current_Block;
        bool drop = false;
        SDL_Color color[colorElement];
        TTF_Font* font = NULL;

        Mix_Chunk* gMix[chunkElement];
        Mix_Music* backgroundMusic;
        TextDisplay arrayTextDisplay[textElement];
        Button arrayButton[buttonElement];
        Display arrayDisplay[displayElement];

        //GUI
        Button guiButton[guiButtonElement];
        Display guiDisplay[guiDisplayElement];

        int status = gameOnGui;
        //đếm tg cho 5 phím trái, phải, trên, dưới, cách
        int timeHolder[5] = {0,0,0,0,0};

        Uint32 prevFallTime=0;
        Uint32 currentTime = 0;
        int currentHighScore = 0;
        int currentScore = 0;
        int audioStatus = 4;
        int currentLevel = 1;
        bool quitTetris = false;

        Tetris(SDL_Renderer* gRenderer, TTF_Font* font);
        void playIntro();
        void configResource();
        void playMusic(Mix_Chunk* chunk = NULL,Mix_Music* music=NULL);
        void onGUI();
        void onPause();
        void playTetris();
        void handleTetrisStatus();
        void renderCurrentTetris(int argStatus);
        void handleEvent(const Uint8* currentKeyState,Uint32& prevTime);
        void onReplay();
        void onGameOver();
};

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Tetris.h"

using namespace std;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

//Khởi tạo các thư viện
bool Init(){
    bool success = true;
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
    //Khởi tạo ảnh PNG
    int flag = IMG_INIT_PNG;
    if(!(IMG_Init(flag)&flag)){
        cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        success = false;
    };
    //Khởi tạo SDL_mixer
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
        printf("SDL_mixer could not initialize! SDL_mixer Error: ");
        success = false;
    }
    //Khởi tạo SDL_ttf
    if(TTF_Init()==-1){
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    };

    gFont = TTF_OpenFont("Fonts/chewy.ttf",fontSize);
    if(gFont == NULL){
        cerr << "TTF Error: " << TTF_GetError() << endl;
        success = false;
    }
    gWindow = SDL_CreateWindow("TETRIS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,screenWidth,screenHeight,SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        cerr << SDL_GetError();
        success = false;
    }
    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    return success;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
};

void exit(){
    SDL_DestroyRenderer(gRenderer);
    IMG_Quit();
    Mix_Quit();
    SDL_DestroyWindow(gWindow);
};

int main (int agrc, char* argv[]){
    if(Init()){
        Tetris* tetris = new Tetris (gRenderer, gFont);
        while (!(*tetris).quitTetris && (*tetris).status!=gameExit){
            (*tetris).handleTetrisStatus();
        }
    };
    SDL_Delay(200);
    exit();
    return 0;
}

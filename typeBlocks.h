#pragma once
#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include "commonFunction.h"

class typeBlocks{
private:
public:
    int matrix[4][4]={{0}};
    int currentBlock = -1;
    int currentColor = -1;
    SDL_Point matrixOrigin = {0,0};
    typeBlocks();
    ~typeBlocks();
    void rotateBlocks(int matrix[][4]=NULL);
};

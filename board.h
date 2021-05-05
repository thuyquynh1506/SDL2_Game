#pragma once
#include <iostream>
#include "commonFunction.h"
#include "display.h"
#include "typeBlocks.h"
#include "vector"

class Board{
private:
    SDL_Renderer* renderer;
public:
    const int width_board = widthBoard;
    const int height_board = heightBoard;

    SDL_Point originPoint = {boardDisplay.x,boardDisplay.y};
    //mảng xử lý các ô ban đầu
    int board[heightBoard+addy+1][widthBoard+2*addx] = {{0}};
    //mảng xử lý renderer có thể nhìn thấy
    //staticBroad sẽ update tất cả cho đến khi khối rơi xuống đến giới hạn
    int** staticBoard = new int* [heightBoard + addy + 1];
    Display* pieceBoard = new Display[15];
    Display boardSquare[4][4];
    Display square[heightBoard][widthBoard];

    //hiệu ứng
    Display boardEffect[4][4];
    vector <Display*> arrayEffect;

    //lập bảng chơi
    Board();
    Board(SDL_Renderer* renderer);
    ~Board();

    void initBoard();
    void setRenderer (SDL_Renderer* renderer);
    void setMatrix(int matrix[][4],int** board, SDL_Point location, int current_Block);
    void setMatrixToStaticBoard(const typeBlocks& block);
    void renderNet();
    void renderPredict(const typeBlocks& block);
    void renderStaticBoard ();
    void renderBlock(const typeBlocks& block);
    void renderEffect ();
    void renderBoard(typeBlocks block);
    long checkPoint();
    void update();
    bool animationEnd();
    bool available (const int matrix[][4], int** board, SDL_Point location, int curent_Block);
    bool checkGameOver();
    bool clearLine(int line);
    void addDisplayEffect (Display* effect);
    SDL_Point getEndPoint (const typeBlocks& block);
    void dropEffect (const typeBlocks& block);
    void resetall();
};

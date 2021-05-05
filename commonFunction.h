#pragma once
#include <iostream>
#include <SDL_rect.h>
#include <SDL_stdinc.h>
#include <SDL_scancode.h>

using namespace std;

//số block trên mỗi cạnh của bảng
const int widthBoard = 15;
const int heightBoard = 22;

//độ dài cạnh của 1 block
const int lengthBlock = 30;

//chỉ số cùa các phím
const int leftKey = 0;
const int upKey = 1;
const int downKey = 2;
const int rightKey = 3;
const int spaceKey = 4;

//kích thước text
const int fontSize = 36;

//khung nhìn trò chơi
const  SDL_Rect display = {0,0,widthBoard*heightBoard,60};

//kết xuất khung trò chơi
//bảng chơi
const SDL_Rect boardDisplay = {0,30,widthBoard*lengthBlock,heightBoard*lengthBlock};
//bảng điểm
const SDL_Rect scoreDisplay = {boardDisplay.w,0,198,display.h+boardDisplay.h};

//màn hình window
const int screenWidth = boardDisplay.w + scoreDisplay.w;
const int screenHeight = boardDisplay.h + display.h;

//chỉ số của các display trong allDisplay
const int displayNotification = 0;
const int displayBackground = 1;
const int displayHighScore = 2;
const int displayCurrentScore = 3;
const int displayElement = 6;

//chỉ số của textDisplay trong textDisplay
const int textScore = 0;
const int textNumberScore = 1;
const int textHighScore = 2;
const int textNumberHighScore = 3;
const int textCombo = 4;
const int textInGame = 5;
const int textPause = 6;
const int textElementPlaying = 6;
const int textGameOver = 7;
const int textElement = 8;

//chỉ số của button trong allButton
const int buttonPause = 0;
const int buttonElementPlaying = 1;
const int buttonResume = 1;
const int buttonReplay = 2;
const int buttonHome = 3;
const int buttonElement = 4;

//GUI
//Display
const int guiBackground = 0;
const int guiTitle = 1;
const int guiMenuBackground = 2;
const int guiSelectBackground = 3;
const int guiDisplayElement = 4;

//Button
const int guiButtonPlay = 0;
const int level1 = 1;
const int level2 = 2;
const int level3 = 3;
const int guiButtonElementRender = 3;
const int audioOn = 4;
const int audioOff = 5;
const int guiButtonElement = 8;

//Color
const int colorScore = 0;
const int colorHighScore = 1;
const int colorPause = 2;
const int colorElement = 3;

//Mix Chunk
const int chunkElement = 11;
const int chunkMove = 0;
const int chunkDrop = 1;
const int chunkClear = 2;
const int chunkClearGood = 3;
const int chunkClearCool = 4;
const int chunkClearExcellent = 5;
const int chunkGameOver = 6;
const int chunkRotate = 7;
const int chunkHardDrop = 8;
const int chunkMenu = 9;
const int chunkPlay = 10;

//các mốc chạy game
const int gamePlaying = 0;
const int gamePause = 1;
const int gameOnGui = 3;
const int gameExit = 4;
const int gameReplay = 5;
const int gameOver = 6;

/*các kiểu xếp khối
kiểu 1: S,Z,L,_|,T
1 2 3
4 5 6
7 8 9
=> S:(5,6,7,8)
   Z:(4,5,8,9)
   L:(2,5,8,9)
   _|:(2,5,7,8)
   T: (4,5,6,8)
kiểu 2: I,O
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 16
=> I:(2,6,10,14)
   O:(6,7,10,11)
*/
//các loại khối
const int typeofBlocks[7][4]={{5,6,7,8},{4,5,8,9},{2,5,8,9},{2,5,7,8},{4,5,6,8},{2,6,10,14},{6,7,10,11}};
//ma trận tương ứng với các khối
const int lengthEgde[7]={3,3,3,3,3,4,4};

//vì max các khối tạo ra là 4x4 nên chiều dọc nếu lên quá 4 ô thì sẽ xuất hiện khối tiếp theo
//chiều ngang max của các khối là 2 nên khi xét phạm vi di chuyển trái phải của người chơi, ta cần cộng thêm chiều x với 2 và chiều y với 4
const int addx = 2;
const int addy = 4;

//các bước xoay của blocks
void copyMatrix (int src[][4], int des[][4],int k);
void copyBoard (int** src, int des[][widthBoard+2*addx]);
void rotateBlocks (int matrix[][4], int k);



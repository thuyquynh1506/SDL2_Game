#include "tetris.h"

Tetris::Tetris (SDL_Renderer* gRenderer, TTF_Font* gFont){
    this->gRenderer = gRenderer;
    this->font = gFont;
    this->board.setRenderer(gRenderer);
    Tetris::configResource();
}

void Tetris::configResource(){
    SDL_SetRenderDrawBlendMode(gRenderer,SDL_BLENDMODE_BLEND);
    //màu
    color[colorScore]={255,255,255};

    //tải các file wav cho audio
    this->backgroundMusic = Mix_LoadMUS("audio/game.wav");
    this->gMix[chunkDrop]=Mix_LoadWAV("audio/drop.wav");
    this->gMix[chunkMove]=Mix_LoadWAV("audio/move.wav");
    this->gMix[chunkGameOver]=Mix_LoadWAV("audio/gameover.wav");
    this->gMix[chunkRotate]=Mix_LoadWAV("audio/rotate.wav");
    this->gMix[chunkHardDrop]=Mix_LoadWAV("audio/hardDrop.wav");
    this->gMix[chunkClear]=Mix_LoadWAV("audio/clear.wav");
    this->gMix[chunkClearGood]=Mix_LoadWAV("audio/good.wav");
    this->gMix[chunkClearCool]=Mix_LoadWAV("audio/cool.wav");
    this->gMix[chunkClearExcellent]=Mix_LoadWAV("audio/excellent.wav");
    this->gMix[chunkMenu]=Mix_LoadWAV("audio/menu.wav");
    this->gMix[chunkPlay]=Mix_LoadWAV("audio/play.wav");

    //tải render cho các ảnh trong khung trò chơi
    arrayDisplay[displayNotification].setRenderer(this->gRenderer);
    arrayDisplay[displayBackground].setRenderer(this->gRenderer);
    arrayDisplay[displayHighScore].setRenderer(this->gRenderer);
    arrayDisplay[displayCurrentScore].setRenderer(this->gRenderer);

    //load Texture
    arrayDisplay[displayNotification].loadTexture("images/frame.png");
    arrayDisplay[displayBackground].loadTexture("images/backgroundGame.png");
    arrayDisplay[displayHighScore].loadTexture("images/highScoreBoard.png");
    arrayDisplay[displayCurrentScore].loadTexture("images/scoreBoard.png");

    //đặt kích thước và vị trí cho các ảnh
    arrayDisplay[displayNotification].wRender = 620;
    arrayDisplay[displayNotification].hRender = 400;
    arrayDisplay[displayNotification].setCenterPoint({screenWidth/2,screenHeight/2});

    arrayDisplay[displayBackground].wRender = screenWidth;
    arrayDisplay[displayBackground].hRender = screenHeight;
    arrayDisplay[displayBackground].clip = new SDL_Rect({0,0,screenWidth,screenHeight});

    arrayDisplay[displayHighScore].wRender = 180;
    arrayDisplay[displayHighScore].hRender = 180;
    arrayDisplay[displayHighScore].setCenterPoint({100,150});
    arrayDisplay[displayHighScore].originPoint = {scoreDisplay.x,scoreDisplay.y};

    arrayDisplay[displayCurrentScore].wRender = 180;
    arrayDisplay[displayCurrentScore].hRender = 180;
    arrayDisplay[displayCurrentScore].setCenterPoint ({100,360});
    arrayDisplay[displayCurrentScore].originPoint = {scoreDisplay.x,scoreDisplay.y};

    //gán font chữ và kích thước chữ cho các text
    arrayTextDisplay[textScore]=TextDisplay(this->font,fontSize);
    arrayTextDisplay[textNumberScore]=TextDisplay(this->font,fontSize);
    arrayTextDisplay[textHighScore]=TextDisplay(this->font,fontSize);
    arrayTextDisplay[textNumberHighScore]=TextDisplay(this->font,fontSize);
    arrayTextDisplay[textPause]=TextDisplay(this->font,fontSize);
    arrayTextDisplay[textCombo]=TextDisplay(this->font,40);
    arrayTextDisplay[textInGame]=TextDisplay(this->font,40);
    arrayTextDisplay[textGameOver]=TextDisplay(this->font,fontSize);

    //set Renderer
    arrayTextDisplay[textHighScore].setRenderer(this->gRenderer);
    arrayTextDisplay[textNumberHighScore].setRenderer(this->gRenderer);
    arrayTextDisplay[textScore].setRenderer(this->gRenderer);
    arrayTextDisplay[textNumberScore].setRenderer(this->gRenderer);
    arrayTextDisplay[textPause].setRenderer(this->gRenderer);
    arrayTextDisplay[textCombo].setRenderer(this->gRenderer);
    arrayTextDisplay[textInGame].setRenderer(this->gRenderer);
    arrayTextDisplay[textGameOver].setRenderer(this->gRenderer);

    //chèn text lên các texture và đặt vị trí cho chúng
    arrayTextDisplay[textNumberScore].makeTextTexture("0",34,color[colorScore]);
    arrayTextDisplay[textNumberHighScore].makeTextTexture("0",34,color[colorScore]);

    arrayTextDisplay[textPause].makeTextTexture("Game Paused",40,{0,0,0});
    arrayTextDisplay[textGameOver].makeTextTexture("Game Over",40,{0,0,0});

    arrayTextDisplay[textPause].setCenterPoint({arrayDisplay[displayNotification].wRender/2,arrayDisplay[displayNotification].hRender*3/10});
    arrayTextDisplay[textHighScore].setCenterPoint({arrayDisplay[displayHighScore].wRender/2,30});
    arrayTextDisplay[textNumberHighScore].setCenterPoint({arrayDisplay[displayHighScore].wRender/2,126});
    arrayTextDisplay[textScore].setCenterPoint({arrayDisplay[displayCurrentScore].wRender/2,30});
    arrayTextDisplay[textNumberScore].setCenterPoint({arrayDisplay[displayHighScore].wRender/2,126});
    arrayTextDisplay[textCombo].setCenterPoint({200,350});
    arrayTextDisplay[textInGame].setCenterPoint({200,300});
    arrayTextDisplay[textGameOver].setCenterPoint({arrayDisplay[displayNotification].wRender/2,arrayDisplay[displayNotification].hRender*3/10});

    //đặt background của TextDisplay
    arrayTextDisplay[textPause].setDisplayBackGround(arrayDisplay[displayNotification]);
    arrayTextDisplay[textScore].setDisplayBackGround(arrayDisplay[displayCurrentScore]);
    arrayTextDisplay[textNumberScore].setDisplayBackGround(arrayDisplay[displayCurrentScore]);
    arrayTextDisplay[textHighScore].setDisplayBackGround(arrayDisplay[displayHighScore]);
    arrayTextDisplay[textNumberHighScore].setDisplayBackGround(arrayDisplay[displayHighScore]);
    arrayTextDisplay[textGameOver].setDisplayBackGround(arrayDisplay[displayNotification]);

    //config button
    arrayButton[buttonPause]=Button();
    arrayButton[buttonResume]=Button();
    arrayButton[buttonReplay]=Button();
    arrayButton[buttonHome]=Button();

    //render cho các button
    arrayButton[buttonPause].setRenderer(this->gRenderer);
    arrayButton[buttonResume].setRenderer(this->gRenderer);
    arrayButton[buttonReplay].setRenderer(this->gRenderer);
    arrayButton[buttonHome].setRenderer(this->gRenderer);

    //cài các mặc định cho Button
    arrayButton[buttonPause].originPoint = {display.x,display.y};
    arrayButton[buttonPause].wRender = 60;
    arrayButton[buttonPause].hRender = 60;

    arrayButton[buttonResume].wRender = 120;
    arrayButton[buttonResume].hRender = 120;

    arrayButton[buttonReplay].wRender = 120;
    arrayButton[buttonReplay].hRender = 120;

    arrayButton[buttonHome].wRender = 120;
    arrayButton[buttonHome].hRender = 120;

    //đặt vị trí cho các button trong bảng khi game paused hoặc game over
    arrayButton[buttonPause].setCenterPoint({500,30});
    arrayButton[buttonResume].setCenterPoint({arrayDisplay[displayNotification].wRender*2/4,arrayDisplay[displayNotification].hRender*3/5});
    arrayButton[buttonReplay].setCenterPoint({arrayDisplay[displayNotification].wRender*1/4,arrayDisplay[displayNotification].hRender*3/5});
    arrayButton[buttonHome].setCenterPoint({arrayDisplay[displayNotification].wRender*3/4,arrayDisplay[displayNotification].hRender*3/5});

    //tải texture cho các button
    arrayButton[buttonPause].loadTexture("images/pause_1.png","images/pause_2.png");
    arrayButton[buttonResume].loadTexture("images/continue_1.png","images/continue_2.png");
    arrayButton[buttonReplay].loadTexture("images/replay_1.png","images/replay_2.png");
    arrayButton[buttonHome].loadTexture("images/home_1.png","images/home_2.png");

    //tải background của các button
    arrayButton[buttonResume].setDisplayBackGround(arrayDisplay[displayNotification]);
    arrayButton[buttonReplay].setDisplayBackGround(arrayDisplay[displayNotification]);
    arrayButton[buttonHome].setDisplayBackGround(arrayDisplay[displayNotification]);

    //menu
    //tải render cho GUI
    guiDisplay[guiBackground].setRenderer(this->gRenderer);
    guiDisplay[guiTitle].setRenderer(this->gRenderer);
    guiDisplay[guiMenuBackground].setRenderer(this->gRenderer);
    guiDisplay[guiSelectBackground].setRenderer(this->gRenderer);

    //tải texture cho GUI
    guiDisplay[guiBackground].loadTexture("images/backgroundMenu.png");
    guiDisplay[guiTitle].loadTexture("images/title.png");
    guiDisplay[guiMenuBackground].loadTexture("images/background.png");

    //cài mặc định cho GUI Display
    guiDisplay[guiBackground].xRender = 0;
    guiDisplay[guiBackground].yRender = 0;
    guiDisplay[guiBackground].wRender = screenWidth;
    guiDisplay[guiBackground].hRender = screenHeight;

    guiDisplay[guiTitle].wRender = 280;
    guiDisplay[guiTitle].hRender = 150;
    guiDisplay[guiTitle].setCenterPoint({0,100});

    guiDisplay[guiMenuBackground].wRender = 310;
    guiDisplay[guiMenuBackground].hRender = 230;
    guiDisplay[guiMenuBackground].setCenterPoint({-100,300});

    //tải render cho các tùy chọn ở menu
    guiButton[guiButtonPlay].setRenderer(this->gRenderer);
    guiButton[audioOn].setRenderer(this->gRenderer);
    guiButton[audioOff].setRenderer(this->gRenderer);
    guiButton[level1].setRenderer(this->gRenderer);
    guiButton[level2].setRenderer(this->gRenderer);
    guiButton[level3].setRenderer(this->gRenderer);

    //tải ảnh ở menu
    guiButton[guiButtonPlay].loadTexture("images/play_1.png","images/play_2.png");
    guiButton[audioOn].loadTexture("images/audioOn_1.png","images/audioOn_2.png");
    guiButton[audioOff].loadTexture("images/audioOff_1.png","images/audioOff_2.png");
    guiButton[level1].loadTexture("images/level1_1.png","images/level1_2.png");
    guiButton[level2].loadTexture("images/level2_1.png","images/level2_2.png");
    guiButton[level3].loadTexture("images/level3_1.png","images/level3_2.png");

    //cài phạm vi button khi click vào các thanh ở menu
    guiButton[guiButtonPlay].wRender = guiButton[guiButtonPlay].wRender;
    guiButton[guiButtonPlay].hRender = guiButton[guiButtonPlay].hRender;
    guiButton[audioOn].wRender = guiButton[audioOn].wRender;
    guiButton[audioOn].hRender = guiButton[audioOn].hRender;
    guiButton[audioOff].wRender = guiButton[audioOff].wRender;
    guiButton[audioOff].hRender = guiButton[audioOff].hRender;
    guiButton[level1].wRender = guiButton[level1].wRender;
    guiButton[level1].hRender = guiButton[level1].hRender;
    guiButton[level2].wRender = guiButton[level2].wRender;
    guiButton[level2].hRender = guiButton[level2].hRender;
    guiButton[level3].wRender = guiButton[level3].wRender;
    guiButton[level3].hRender = guiButton[level3].hRender;

    //vị trí của các thanh ở menu
    guiButton[guiButtonPlay].setCenterPoint({250,50});
    guiButton[audioOn].setCenterPoint({250,135});
    guiButton[audioOff].setCenterPoint({250,135});
    guiButton[level1].setCenterPoint({250,220});
    guiButton[level2].setCenterPoint({250,220});
    guiButton[level3].setCenterPoint({250,220});

    //GUI background
    guiButton[guiButtonPlay].setDisplayBackGround(guiDisplay[guiMenuBackground]);
    guiButton[audioOn].setDisplayBackGround(guiDisplay[guiMenuBackground]);
    guiButton[audioOff].setDisplayBackGround(guiDisplay[guiMenuBackground]);
    guiButton[level1].setDisplayBackGround(guiDisplay[guiMenuBackground]);
    guiButton[level2].setDisplayBackGround(guiDisplay[guiMenuBackground]);
    guiButton[level3].setDisplayBackGround(guiDisplay[guiMenuBackground]);
}

//tải audio khi chọn trạng thái audio on
void Tetris::playMusic(Mix_Chunk* chunk,Mix_Music* music){
    if(this->audioStatus==4 && chunk!=NULL){
        Mix_PlayChannel(-1,chunk,0);
    };
    if(this->audioStatus==4&&music!=NULL){
        Mix_PlayMusic(music,-1);
    }
}

//vị trí, kích thước của tên game, và ảnh sau background
void Tetris::onGUI(){
    guiDisplay[guiTitle].wRender = 280;
    guiDisplay[guiTitle].hRender = 150;
    guiDisplay[guiTitle].setCenterPoint({0,100});

    guiDisplay[guiMenuBackground].wRender = 310;
    guiDisplay[guiMenuBackground].hRender = 230;
    guiDisplay[guiMenuBackground].setCenterPoint({-100,300});

    guiDisplay[guiTitle].setAnimation("Transform",500,NULL,{200,0});
    guiDisplay[guiMenuBackground].setAnimation("Transform",800,NULL,{200,0});

    Uint32 tmp;
    //khi click quay lại home
    while(!this->quitTetris && this->status == gameOnGui){
        while (SDL_PollEvent(&this->event)!=0){
            if(this->event.type==SDL_QUIT){
                this->quitTetris = true;
                this->status = gameExit;
            }
        };
        this->handleEvent(NULL,tmp);
        SDL_SetRenderDrawColor(this->gRenderer,255,255,255,255);
        SDL_RenderClear(this->gRenderer);

        guiDisplay[guiBackground].render();
        guiDisplay[guiTitle].render();
        guiDisplay[guiMenuBackground].render();

        guiButton[guiButtonPlay].render();
        guiButton[this->audioStatus].render();
        guiButton[this->currentLevel].render();

        SDL_RenderPresent(this->gRenderer);
    };
}

//khi tạm dừng game
void Tetris::onPause(){
    arrayDisplay[displayNotification].setAnimation("Appear",200);
    playMusic(gMix[chunkMenu]);
    Uint32 tmp;
    while(this->status == gamePause){
        while (SDL_PollEvent(&this->event)!=0){
            if(this->event.type==SDL_QUIT){
                this->quitTetris = true;
                this->status = gameExit;
            }
        };
        this->handleEvent(NULL,tmp);
        if(this->quitTetris==true) break;
        SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
        SDL_RenderClear(gRenderer);
        renderCurrentTetris(-1);
        SDL_RenderPresent(gRenderer);
    }
}

//trong quá trình chơi game
void Tetris::playTetris(){
    Uint32 PrevTime = 0;
    bool game_Over = false;
    //quá trình chuyển trạng thái trong game, tính điểm và tạo hiệu ứng khi hàng biến mất
    while (!(this->quitTetris)&&!game_Over&&this->status==gamePlaying){
        std::string score = "";
        while(SDL_PollEvent(&this->event)!=0){
            if(this->event.type==SDL_QUIT){
                this->quitTetris = true;
                this->status = gameExit;
            }
        };
        Tetris::handleEvent(SDL_GetKeyboardState(NULL),PrevTime);
        Tetris::handleTetrisStatus();
        SDL_SetRenderDrawColor(this->gRenderer,255,255,255,255);
        SDL_RenderClear(this->gRenderer);
        this->currentTime = SDL_GetTicks();
        if(this->currentTime-this->prevFallTime>=1000/this->currentLevel||this->drop){
            this->drop = false;
            SDL_Point nextPoint = {this->current_Block.matrixOrigin.x,this->current_Block.matrixOrigin.y+1};
            if(this->board.available(this->current_Block.matrix,this->board.staticBoard, nextPoint,this->current_Block.currentBlock)){
                this->current_Block.matrixOrigin.y++;
            }
            else{
                playMusic(gMix[chunkDrop]);
                board.setMatrixToStaticBoard(this->current_Block);
                game_Over=this->board.checkGameOver();
                if(game_Over){
                    this->status=gameOver;
                }
                long rowsDisappear = board.checkPoint();
                typeBlocks nextBlock;
                this->current_Block = nextBlock;
                string lineText;
                string combo;
                if(rowsDisappear!=0){
                    if(rowsDisappear==1){
                        playMusic(gMix[chunkClear]);
                        this->currentScore +=100;
                        combo = "+100";
                    }
                    else{
                        if(rowsDisappear==2){
                            playMusic(gMix[chunkClearGood]);
                            lineText = "GOOD!";
                            this->currentScore += 230;
                            combo = "+230";
                        }
                        else{
                            if(rowsDisappear==3){
                                playMusic(gMix[chunkClearCool]);
                                lineText = "COOL!";
                                this->currentScore += 345;
                                combo = "+345";
                            }
                            else{
                                playMusic(gMix[chunkClearExcellent]);
                                lineText = "EXCELLENT!";
                                this->currentScore += rowsDisappear*115;
                                combo = "+" + to_string(rowsDisappear*115);
                            }
                        }
                    }

                    this->arrayTextDisplay[textInGame].makeTextTexture(lineText.c_str(),40,{0,0,0});
                    this->arrayTextDisplay[textInGame].setAnimation("Scale Up",200);
                    arrayTextDisplay[textInGame].setAnimation("Disappear",200,1000);

                    score+=to_string(this->currentScore);
                    this->arrayTextDisplay[textCombo].makeTextTexture(combo.c_str(),36,{0,0,0});
                    this->arrayTextDisplay[textCombo].setAnimation("Scale Up",200);
                    arrayTextDisplay[textCombo].setAnimation("Disappear",200,1000);

                    this->arrayTextDisplay[textNumberScore].makeTextTexture(score.c_str(),36,this->color[colorScore]);
                    this->arrayTextDisplay[textNumberScore].setDisplayBackGround(arrayDisplay[displayCurrentScore]);
                    this->arrayTextDisplay[textNumberScore].setAnimation("Scale Up",200);
                }
                if(this->currentHighScore < this->currentScore){
                    this->currentHighScore = this->currentScore;
                    this->arrayTextDisplay[textNumberHighScore].makeTextTexture(to_string(this->currentHighScore).c_str(),36,this->color[colorScore]);
                    this->arrayTextDisplay[textNumberHighScore].setDisplayBackGround(arrayDisplay[displayHighScore]);
                    this->arrayTextDisplay[textNumberHighScore].setAnimation("Scale Up",200);
                }
            }
            prevFallTime = currentTime;
        };
        PrevTime=currentTime;
        Tetris::renderCurrentTetris(-1);
        SDL_RenderPresent(this->gRenderer);
    };
}

//từng trạng thái game chạy
void Tetris::handleTetrisStatus(){
    if(this->status == gamePause){
        if(Mix_PausedMusic()!=1)
            Mix_PauseMusic();
        this->onPause();
    };
    if(this->status == gameOnGui){
        Mix_HaltMusic();
        this->board.resetall();
        this->onGUI();
    };
    if(this->status == gameReplay){
        this->status = gamePlaying;
        Mix_HaltMusic();
        this->playMusic(NULL,this->backgroundMusic);
        this->playTetris();
    };
    if(this->status == gameOver){
        Mix_HaltMusic();
        playMusic(this->gMix[chunkGameOver]);
        this->onGameOver();
    }
}

//tải render hiển thị cho game trong quá trình chơi tại từng trạng thái
void Tetris::renderCurrentTetris(int argStatus){
    if(argStatus == -1) argStatus = this->status;
    if(argStatus == gamePlaying){
        SDL_Rect blurBackground = {boardDisplay.x,boardDisplay.y,boardDisplay.w,boardDisplay.h};
        SDL_Rect boardStroke = {boardDisplay.x,boardDisplay.y,boardDisplay.w,boardDisplay.h};
        this->arrayDisplay[displayBackground].render();
        SDL_SetRenderDrawColor(gRenderer,30,61,79,255);
        SDL_RenderFillRect(this->gRenderer,&blurBackground);
        SDL_SetRenderDrawColor(gRenderer,0,0,0,255);
        SDL_RenderDrawRect(this->gRenderer,&blurBackground);
        this->arrayDisplay[displayHighScore].render(true);
        this->arrayDisplay[displayCurrentScore].render(true);
        this->board.renderBoard(this->current_Block);
        for(int i=0;i<textElementPlaying;i++){
            if(arrayTextDisplay[i].texture!=NULL){
                this->arrayTextDisplay[i].render(true);
            }
        };
        for(int i=0;i<buttonElementPlaying;i++){
            if(arrayButton[i].texture!=NULL){
                this->arrayButton[i].render(true);
            }
        };
    }
    else if(argStatus==gamePause){
        this->renderCurrentTetris(gamePlaying);
        SDL_Rect blurBackground = {0,0,screenWidth,screenHeight};
        SDL_SetRenderDrawColor(gRenderer,0,0,0,60);
        SDL_RenderFillRect(this->gRenderer,&blurBackground);
        arrayDisplay[displayNotification].render(true);
        arrayTextDisplay[textPause].render(true);
        arrayButton[buttonResume].render(true);
        arrayButton[buttonReplay].render(true);
        arrayButton[buttonHome].render(true);
    }
    else if(argStatus==gameOver){
        this->renderCurrentTetris(gamePlaying);
        SDL_Rect blurBackground = {0,0,screenWidth,screenHeight};
        SDL_SetRenderDrawColor(gRenderer,0,0,0,60);
        SDL_RenderFillRect(this->gRenderer,&blurBackground);
        arrayDisplay[displayNotification].render(true);
        arrayTextDisplay[textGameOver].render(true);
        arrayButton[buttonReplay].render(true);
        arrayButton[buttonHome].render(true);
    }
}

//nhận điều khiển từ bàn phím và chuột
void Tetris::handleEvent(const Uint8* currentKeyState,Uint32& prevTime){
    if(this->status==gamePlaying){
        //xử lý bàn phím trong quá trình chơi
        cout << timeHolder[spaceKey]<< "-" << (int) currentKeyState[SDL_SCANCODE_SPACE] << endl;
        int timeOffset = SDL_GetTicks()-prevTime;
        if(currentKeyState[SDL_SCANCODE_LEFT]) this->timeHolder[leftKey]+=timeOffset;
        else this->timeHolder[leftKey]=0;
        if(currentKeyState[SDL_SCANCODE_UP]) this->timeHolder[upKey]+=timeOffset;
        else this->timeHolder[upKey]=0;
        if(currentKeyState[SDL_SCANCODE_DOWN]) this->timeHolder[downKey]+=timeOffset;
        else this->timeHolder[downKey]=0;
        if(currentKeyState[SDL_SCANCODE_RIGHT]) this->timeHolder[rightKey]+=timeOffset;
        else this->timeHolder[rightKey]=0;

        if(!currentKeyState[SDL_SCANCODE_SPACE]&&timeHolder[spaceKey]==-1){
            timeHolder[spaceKey]=0;
        };
        if(currentKeyState[SDL_SCANCODE_SPACE]&&timeHolder[spaceKey]!=-1)
            this->timeHolder[spaceKey]+=timeOffset;

        //xử lý chuột
        for (int i=0;i<1;i++){
            this->arrayButton[i].handleMouseEvent(&this->event);
        };
        //sau khi người chơi hoàn tất menu và bắt đầu trò chơi
        //space:khối bị rơi xuống lập tức
        if(this->timeHolder[spaceKey]>5){
            this->board.dropEffect(this->current_Block);
            SDL_Point nextOriginPoint = board.getEndPoint(this->current_Block);
            this->current_Block.matrixOrigin = nextOriginPoint;
            this->drop=true;
            playMusic(this->gMix[chunkDrop]);
            this->timeHolder[spaceKey] = -1;
        };
        //mũi tên lên: xoay khối theo các góc
        if(this->timeHolder[upKey]>80){
            int tmpMatrix[4][4];
            copyMatrix(this->current_Block.matrix,tmpMatrix,lengthEgde[this->current_Block.currentBlock]);
            this->current_Block.rotateBlocks(tmpMatrix);

            if(this->board.available(tmpMatrix,this->board.staticBoard,this->current_Block.matrixOrigin,this->current_Block.currentBlock)){
                this->current_Block.rotateBlocks();
                this->timeHolder[upKey]=0;
                Mix_PlayChannel(-1,gMix[chunkRotate],0);
            }
        };
        //phím mũi tên trái: khối di chuyển sang trái
        if(this->timeHolder[leftKey]>50){
            SDL_Point nextOriginPoint = {this->current_Block.matrixOrigin.x-1,this->current_Block.matrixOrigin.y};
            if(this->board.available(this->current_Block.matrix,this->board.staticBoard,nextOriginPoint,this->current_Block.currentBlock)){
                this->current_Block.matrixOrigin = nextOriginPoint;
                this->timeHolder[leftKey]=0;
                Mix_PlayChannel(-1,gMix[chunkMove],0);
            };
        };
        //phím mũi tên phải: khối di chuyển sang phải
        if(this->timeHolder[rightKey]>50){
            SDL_Point nextOriginPoint = {this->current_Block.matrixOrigin.x+1,this->current_Block.matrixOrigin.y};
            if(this->board.available(this->current_Block.matrix,this->board.staticBoard,nextOriginPoint,this->current_Block.currentBlock)){
                this->current_Block.matrixOrigin = nextOriginPoint;
                this->timeHolder[rightKey]=0;
                Mix_PlayChannel(-1,gMix[chunkMove],0);
            };
        };
        //phím mũi tên xuống: khối di chuyển xuống
        if(this->timeHolder[downKey]>50){
            SDL_Point nextOriginPoint = {this->current_Block.matrixOrigin.x,this->current_Block.matrixOrigin.y+1};
            if(this->board.available(this->current_Block.matrix,this->board.staticBoard,nextOriginPoint,this->current_Block.currentBlock)){
                this->current_Block.matrixOrigin = nextOriginPoint;
                this->timeHolder[downKey]=0;
                this->prevFallTime = SDL_GetTicks();
                Mix_PlayChannel(-1,gMix[chunkMove],0);
            };
        };
        //xử lý chuột
        if(arrayButton[buttonPause].currentStatus=="Mouse Down"){
            this->status = 1;
        }
    }
    //khi click pause
    else if(this->status==gamePause){
        arrayButton[buttonResume].handleMouseEvent(&this->event);
        arrayButton[buttonReplay].handleMouseEvent(&this->event);
        arrayButton[buttonHome].handleMouseEvent(&this->event);
        if(arrayButton[buttonResume].Click()){
            this->status = gamePlaying;
            if(Mix_PausedMusic()==1){
                Mix_ResumeMusic();
            }
            playMusic(gMix[chunkMenu]);
        };
        if(arrayButton[buttonReplay].Click()){
            this->status = gameReplay;
            this->onReplay();
            playMusic(gMix[chunkMenu]);
        };
        if(arrayButton[buttonHome].Click()){
            this->status = gameOnGui;
            playMusic(gMix[chunkMenu]);
        };
    }
    //tùy chọn ngoài menu
    else if(this->status==gameOnGui){
        guiButton[guiButtonPlay].handleMouseEvent(&this->event);
        guiButton[this->audioStatus].handleMouseEvent(&this->event);
        guiButton[this->currentLevel].handleMouseEvent(&this->event);
        if(guiButton[guiButtonPlay].Click()){
            this->status=gameReplay;
            playMusic(gMix[chunkPlay]);
        }
        if(guiButton[this->audioStatus].Click()){
            this->audioStatus=audioOn+(this->audioStatus+1)%2;
            playMusic(gMix[chunkMenu]);
        };
        if(guiButton[this->currentLevel].Click()){
            this->currentLevel = level1 + (this->currentLevel)%3;
            playMusic(gMix[chunkMenu]);
        };
    }
    //khi game over hiện tùy chọn replay và home
    else if(this->status==gameOver){
        arrayButton[buttonReplay].handleMouseEvent(&this->event);
        arrayButton[buttonHome].handleMouseEvent(&this->event);
        if(arrayButton[buttonReplay].Click()){
            this->status = gameReplay;
            this->onReplay();
            playMusic(gMix[chunkMenu]);
        };
        if(arrayButton[buttonHome].Click()){
            this->board.resetall();
            this->status = gameOnGui;
            playMusic(gMix[chunkMenu]);
        }
    }
}

//game replay
void Tetris::onReplay(){
    this->board.resetall();
    this->current_Block = typeBlocks();
    this->currentScore = 0;
    arrayTextDisplay[textNumberScore].makeTextTexture("0",35,color[colorScore]);
    arrayTextDisplay[textNumberScore].setCenterPoint({arrayDisplay[displayHighScore].wRender/2,125});
    arrayTextDisplay[textNumberScore].setDisplayBackGround(arrayDisplay[displayCurrentScore]);
}

//game over
void Tetris::onGameOver(){
    arrayDisplay[displayNotification].setAnimation("Appear",200);
    Uint32 tmp;
    while(this->status==gameOver){
        while(SDL_PollEvent(&this->event)!=0){
            if(this->event.type==SDL_QUIT){
                this->quitTetris = true;
                this->status = gameExit;
            }
        };
        this->handleEvent(NULL, tmp);
        if(this->quitTetris==true)break;
        SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
        SDL_RenderClear(gRenderer);
        renderCurrentTetris(-1);
        SDL_RenderPresent(gRenderer);
    }
}

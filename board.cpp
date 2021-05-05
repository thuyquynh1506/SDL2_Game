#include "board.h"

//tạo bảng
Board::Board(){
    for (int i=0;i<heightBoard + addy + 1; i++){
        (this->staticBoard)[i] = new int[widthBoard+2*addx];
    };
    for (int i=0;i<heightBoard + addy + 1;i++){
        for (int j=0;j<widthBoard+2*addx;j++){
            (this->staticBoard)[i][j] = 0;
        }
    };
    for (int i=0;i<widthBoard+2*addx;i++){
        this->board[heightBoard+addy][i]=1;
        this->staticBoard[heightBoard+addy][i]=1;
    };
    for (int i=0;i<heightBoard+addy;i++){
        for (int j=0;j<addx;j++){
            this->board[i][j] = 1;
            this->staticBoard[i][j]=1;
            this->board[i][widthBoard+2*addx-j-1]=1;
            this->staticBoard[i][widthBoard+2*addx-j-1]=1;
        }
    };
}

Board::Board(SDL_Renderer* renderer){
    Board::setRenderer(renderer);
};

Board::~Board (){
    this->arrayEffect.clear();
}
//tải các blocks
void Board::initBoard(){
    (this->pieceBoard)[0].loadTexture("images/BlockEmpty.png")!=true ? std::cout << "Couldn't load BlockEmpty in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[1].loadTexture("images/Block1_1.png")!=true ? std::cout << "Couldn't load Block1_1 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[2].loadTexture("images/Block2_1.png")!=true ? std::cout << "Couldn't load Block2_1 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[3].loadTexture("images/Block3_1.png")!=true ? std::cout << "Couldn't load Block3_1 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[4].loadTexture("images/Block4_1.png")!=true ? std::cout << "Couldn't load Block4_1 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[5].loadTexture("images/Block5_1.png")!=true ? std::cout << "Couldn't load Block5_1 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[6].loadTexture("images/Block1_2.png")!=true ? std::cout << "Couldn't load Block1_2 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[7].loadTexture("images/Block2_2.png")!=true ? std::cout << "Couldn't load Block2_2 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[8].loadTexture("images/Block3_2.png")!=true ? std::cout << "Couldn't load Block3_2 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[9].loadTexture("images/Block4_2.png")!=true ? std::cout << "Couldn't load Block4_2 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[10].loadTexture("images/Block5_2.png")!=true ? std::cout << "Couldn't load Block5_2 in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[11].loadTexture("images/BlockLocked.png")!=true ? std::cout << "Couldn't load BlockLocked in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[12].loadTexture("images/BlockDisappear.png")!=true ? std::cout << "Couldn't BlockDisappear the texture in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[13].loadTexture("images/BlockDrop.png")!=true ? std::cout << "Couldn't load BlockDrop in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[13].setAlpha(150);
    (this->pieceBoard)[14].loadTexture("images/star.png")!=true ? std::cout << "Couldn't load star in initBoard" << std::endl:std::cout << "";
    (this->pieceBoard)[14].setAlpha(190);
};

//tải render của các blocks
void Board::setRenderer (SDL_Renderer* renderer){
    this->renderer = renderer;
    (this->pieceBoard)[0].renderer = this->renderer;
    (this->pieceBoard)[1].renderer = this->renderer;
    (this->pieceBoard)[2].renderer = this->renderer;
    (this->pieceBoard)[3].renderer = this->renderer;
    (this->pieceBoard)[4].renderer = this->renderer;
    (this->pieceBoard)[5].renderer = this->renderer;
    (this->pieceBoard)[6].renderer = this->renderer;
    (this->pieceBoard)[7].renderer = this->renderer;
    (this->pieceBoard)[8].renderer = this->renderer;
    (this->pieceBoard)[9].renderer = this->renderer;
    (this->pieceBoard)[10].renderer = this->renderer;
    (this->pieceBoard)[11].renderer = this->renderer;
    (this->pieceBoard)[12].renderer = this->renderer;
    (this->pieceBoard)[13].renderer = this->renderer;
    (this->pieceBoard)[14].renderer = this->renderer;
    for (int i=0;i<heightBoard;i++){
        for (int j=0;j<widthBoard;j++){
            this->square[i][j]=Display(this->renderer);
        }
    };
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            this->boardSquare[i][j]=Display(this->renderer);
        }
    }

    for(int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            this->boardEffect[i][j] = Display (this->renderer);
            this->boardEffect[i][j].textureNull = true;
        }
    }
    Board::initBoard();
};

//thiết lập đưa ma trận chứa block vào bảng
void Board::setMatrix(int matrix[][4], int** board, SDL_Point location, int current_Block){
    for (int i=0;i<lengthEgde[current_Block];i++){
        for (int j=0;j<lengthEgde[current_Block];j++){
            if (matrix[i][j]!=0){
                board[i+location.y][j+location.x]=matrix[i][j];
            }
        }
    }
}

//khối trong quá trình rơi và hiệu ứng khi rơi xuống vị trí tối đa
void Board::setMatrixToStaticBoard(const typeBlocks& block){
    int current_Block = block.currentBlock;
    SDL_Point location = block.matrixOrigin;
    for (int i=0;i<lengthEgde[current_Block];i++){
        for (int j=0;j<lengthEgde[current_Block];j++){
            if (block.matrix[i][j]!=0){
                this->staticBoard[i+location.y][j+location.x] = block.matrix[i][j];
                SDL_Rect desEffect = {this-> originPoint.x+(location.x - addx +j)*lengthBlock-1,this->originPoint.y+(i+location.y-addy)*lengthBlock+1,lengthBlock,lengthBlock};
                Display* newEffect = new Display(this->renderer);
                newEffect->texture = this->pieceBoard[11].texture;
                newEffect->setRect(desEffect);
                newEffect->setAnimation("Scale Up",500);
                this->addDisplayEffect(newEffect);
            }
        }
    };
}

//trả lại ô trống cho những chỗ k có block
void Board::renderNet(){
    for (int j=0;j<widthBoard;j++){
        for (int i=0;i<heightBoard;i++){
            SDL_Rect des = {this->originPoint.x+j*lengthBlock,this->originPoint.y+i*lengthBlock,lengthBlock,lengthBlock};
            this->pieceBoard[0].setRect(des);
            this->pieceBoard[0].render();
        }
    }
}

//cập nhật lại bảng sau mỗi khối di chuyển
void Board::renderBoard(typeBlocks block){
    this->update();
    SDL_Point currentBlockLocation = block.matrixOrigin;
    copyBoard(this->staticBoard, this->board);
    this->renderNet();
    this->renderStaticBoard();
    this->renderPredict(block);
    this->renderBlock(block);
    this->renderEffect();
}

//tính số hàng được lấp đầy và bị biến mất
long Board::checkPoint(){
    long rowPoint = 0;
    for (int i=0;i<heightBoard;i++){
        bool full = true;
        for (int j=0;j<widthBoard;j++){
            if(this->staticBoard[i+addy][j+addx]==0) full = false;
        };
        if (full){
            for (int j=0;j<widthBoard;j++){
                this->square[i][j].setAnimation("Fade Out",500);
                SDL_Rect effectRect = {this->originPoint.x+j*lengthBlock,this->originPoint.y+i*lengthBlock,lengthBlock,lengthBlock};
                Display* newEffect = new Display(this->renderer);
                newEffect->texture = this->pieceBoard[12].texture;
                newEffect->textureNull = true;
                newEffect->setRect(effectRect);
                Animation* animation = new Animation("Rotate",500,double(180),20*j);
                newEffect->setAnimation(animation);
                newEffect->setAnimation("Scale Up",300,20*j);
                newEffect->setAnimation("Disappear",200,300+20*j);
                this->arrayEffect.push_back(newEffect);
            }
            rowPoint+=1;
        }
    };
    return rowPoint;
}

//cập nhật lại bảng sau khi hàng biến mất
void Board::update()
{
    if(this->animationEnd()){
        for (int i=0;i<heightBoard;i++){
            bool full = true;
            for (int j=0;j<widthBoard;j++){
                if(this->staticBoard[i+addy][j+addx]==0){
                    full = false;
                }
            };
            if(full){
                for (int k=i+addy;k>addy;k--){
                    for (int h=0;h<widthBoard+2*addx;h++){
                        this->staticBoard[k][h] = this->staticBoard[k-1][h];
                    }
                }
                for(int h=0;h<widthBoard;h++){
                    this->staticBoard[addy][h+addx]=0;
                }
                i--;
            }
        };
    }
    vector<Display*>::iterator it = this->arrayEffect.begin();
    while (it!=this->arrayEffect.end()){
        if((*it)->animationQueue.size()==0){
            delete(*it);
            this->arrayEffect.erase(it);
            it=this->arrayEffect.begin();
            continue;
        };
        it++;
    }
}

//hiệu ứng khi kết thúc
bool Board::animationEnd(){
    for (int i=0;i<heightBoard;i++){
        for (int j=0;j<widthBoard;j++){
            if(this->square[i][j].animationQueue.size()!=0) return false;
        }
    };
    return true;
}
//kt xem block có thể đi xuống tiếp nữa hay không
bool Board::available(const int matrix[][4],int** board,SDL_Point location,int current_Block){
    for (int i=0;i<lengthEgde[current_Block];i++){
        for (int j=0;j<lengthEgde[current_Block];j++){
            if((matrix[i][j]!=0)&&(board[location.y+i][location.x+j]!=0)) return false;
        }
    }
    return true;
}
//kt game khi thua
bool Board::checkGameOver(){
    for (int i=0;i<widthBoard;i++){
        if(staticBoard[addy-1][addx+i]!=0) return true;
    };
    return false;
}

// hiệu ứng
//hiển thị hiệu ứng
void Board::addDisplayEffect(Display* effect){
    if (effect->renderer == NULL){
        effect->setRenderer(this->renderer);
    }
    arrayEffect.push_back(effect);
}

//check điểm cuối của khối
SDL_Point Board::getEndPoint(const typeBlocks& block){
    SDL_Point checkPoint = {block.matrixOrigin.x,block.matrixOrigin.y};
    while(this->available(block.matrix,this->staticBoard,checkPoint,block.currentBlock)){
        checkPoint.y++;
    };
    checkPoint.y--;
    return checkPoint;
}

//hiệu ứng khi khối rơi
void Board::dropEffect(const typeBlocks& block){
    SDL_Point currentLocation = block.matrixOrigin;
    SDL_Point endPoint = this->getEndPoint(block);
    for (int i=0;i<lengthEgde[block.currentBlock];i++){
        for (int j=0;j<lengthEgde[block.currentBlock];j++){
            if(block.matrix[i][j]){
                Display* newEffect = new Display(this->renderer);
                SDL_Rect rectEffect;
                rectEffect.x = this->originPoint.x+(block.matrixOrigin.x+j-addx)*lengthBlock;
                rectEffect.y = this->originPoint.y+(block.matrixOrigin.y+i-addy)*lengthBlock;
                rectEffect.w = lengthBlock;
                rectEffect.h = (endPoint.y-currentLocation.y)*lengthBlock;
                //khi khối rơi xuống từ từ
                newEffect->texture = this->pieceBoard[13].texture;
                newEffect->setRect(rectEffect);
                newEffect->setAnimation("Cut Down",300);
                this->addDisplayEffect(newEffect);

                //khi khối rơi xuống ngay lập tức
                int rows = rectEffect.h/lengthBlock;
                int stars = rows!=0?rand()%rows/2:0;
                for (int k=0;k<stars;k++){
                    Display* newStar = new Display(this->renderer);
                    SDL_Rect rectStar;
                    rectStar.x = 10+rand()%(lengthBlock-10)+rectEffect.x;
                    rectStar.y = rand()%rectEffect.h+rectEffect.y;
                    rectStar.w = (double(rectStar.y)-double(rectEffect.y))/double(rectEffect.h)*35;
                    if(rectStar.w>=100) rectStar.w = 0;
                    rectStar.h = rectStar.w;
                    newStar->texture = this->pieceBoard[14].texture;
                    newStar->setRect(rectStar);
                    newStar->setAnimation("Disappear",800*(double(rectStar.y)-double(rectEffect.y))/double(rectEffect.h));
                    Animation* tmpani = new Animation("Rotate",900,120,NULL);
                    newStar->setAnimation(tmpani);
                    SDL_Point transformVector={0,-(rand()%10+1)};
                    newStar->setAnimation("Transform",900,NULL,transformVector);
                    this->addDisplayEffect(newStar);
                }
            }
        }
    }
}

//render cho bóng của khối
void Board::renderPredict(const typeBlocks& block){
    SDL_Point checkPoint =getEndPoint(block);
    for(int i=0;i<lengthEgde[block.currentBlock];i++){
        for (int j=0;j<lengthEgde[block.currentBlock];j++){
            if(block.matrix[i][j]!=0){
                SDL_Rect des = {this->originPoint.x+(checkPoint.x+j-addx)*lengthBlock,this->originPoint.y+(checkPoint.y+i-addy)*lengthBlock,lengthBlock,lengthBlock};
                pieceBoard[block.currentColor+5].setRect(des);
                pieceBoard[block.currentColor+5].render();
            }
        }
    }
}

//tạo render cho trạng thái của khối trong bảng
void Board::renderStaticBoard(){
    for (int j=0;j<widthBoard;j++){
        for (int i=0;i<heightBoard;i++){
            SDL_Rect des = {this->originPoint.x+j*lengthBlock,this->originPoint.y+i*lengthBlock,lengthBlock,lengthBlock};
            this->square[i][j].setRect(des);
            this->square[i][j].texture = (this->pieceBoard)[this->staticBoard[i+addy][j+addx]].texture;
            if(this->staticBoard[i+addy][j+addx]) this->square[i][j].render();
        }
    }
}

//render hiển thị khối và quá trình rơi khối
void Board::renderBlock(const typeBlocks& block){
    SDL_Point location = block.matrixOrigin;
    SDL_Point endPoint = this->getEndPoint(block);
    bool effect = false;
    if(endPoint.x==location.x && endPoint.y-1==location.y){
        effect = true;
    }
    for(int i=0;i<lengthEgde[block.currentBlock];i++){
        for (int j=0;j<lengthEgde[block.currentBlock];j++){
            if (block.matrix[i][j]&&location.x+j-addx>=0&&location.y+i-addy>=0){
                SDL_Rect des = {this->originPoint.x+(location.x+j-addx)*lengthBlock,this->originPoint.y+(location.y+i-addy)*lengthBlock,lengthBlock,lengthBlock};
                this->boardSquare[i][j].texture = pieceBoard[block.currentColor].texture;
                this->boardSquare[i][j].setRect(des);
                if(effect) this->boardSquare[i][j].setAnimation("Fade Out",900);
                this->boardSquare[i][j].render();
            };
        }
    }
}

//render hiển thị các hiệu ứng
void Board::renderEffect(){
    vector <Display*>::iterator it= this->arrayEffect.begin();
    while(it!=arrayEffect.end()){
        (*it)->render();
        it++;
    };
}

//reset tất cả và tạo lại bảng ban đầu
void Board::resetall(){
    for (int i=0;i<heightBoard+addy+1;i++){
        (this->staticBoard)[i] = new int[widthBoard+2*addx];
    };
    for (int i=0;i<heightBoard+addy+1;i++){
        for (int j=0;j<widthBoard+2*addx;j++){
            (this->staticBoard)[i][j] = 0;
        }
    };
    for (int i=0;i<widthBoard+2*addx;i++){
        this->board[heightBoard+addy][i]=1;
        this->staticBoard[heightBoard+addy][i]=1;
    };
    for (int i=0;i<heightBoard+addy;i++){
        for(int j=0;j<addx;j++){
            this->board[i][j] = 1;
            this->staticBoard[i][j] = 1;
            this->board[i][widthBoard+2*addx-j-1] = 1;
            this->staticBoard[i][widthBoard+2*addx-j-1]=1;
        }
    };
};



#include "typeBlocks.h"

typeBlocks::typeBlocks()
{
    //vị trí bắt đầu của khối khi xuất hiện
    this->matrixOrigin.x = (widthBoard+2*addx)/2;
    this->matrixOrigin.y = 1;
    //lấy ngẫu nhiên thứ tự loại khối xuất hiện
    int randNumber = rand()%7;
    this->currentBlock = randNumber;
    //lấy ngẫu nhiên các màu của block
    this->currentColor = rand()%5+1;
    int count = 1, mark = 0;
    //quét ma trận bao khối
    for(int i=0;i<lengthEgde[currentBlock];i++){
        for (int j=0;j<lengthEgde[currentBlock];j++){
            //gán khối hình vào ma trận matrix[i][j] bằng màu đã rand
            if(typeofBlocks[currentBlock][mark]==count){
                this->matrix[i][j] = this->currentColor;
                mark++;
            }
            else this->matrix[i][j]=0;
            count++;
        }
    };
}

typeBlocks::~typeBlocks(){};
//xoay blocks theo các góc {0,90,180,270}
void typeBlocks::rotateBlocks(int matrix[][4]){
    int tmpMatrix[4][4];
    if(matrix==NULL) matrix = this->matrix;
    copyMatrix(matrix,tmpMatrix,lengthEgde[this->currentBlock]);
    for (int i=0;i<lengthEgde[this->currentBlock];i++){
        for(int j=0;j<lengthEgde[this->currentBlock];j++){
            matrix[i][j]=tmpMatrix[j][lengthEgde[this->currentBlock]-i-1];
        }
    }
}

#include "commonFunction.h"

using namespace std;

//quá trình xoay blocks
//sao chép ma trận
void copyMatrix(int src[][4], int des[][4], int k)
{
    for (int i=0; i<k; i++){
        for (int j=0; j<k; j++){
            des[i][j]=src[i][j];
        }
    }
}
//sao chép bảng
void copyBoard(int** src, int des[][widthBoard+2*addx])
{
    for (int i=0; i<(heightBoard+addy+1); i++){
        for (int j=0; j<(widthBoard+2*addx); j++){
            des[i][j]=src[i][j];
        }
    }
}
//xoay blocks theo các góc 0 độ, 90 độ, 180 độ, 270 độ
void rotateBlocks(int matrix[][4], int k)
{
    int tmpMatrix[4][4];
    copyMatrix(matrix,tmpMatrix,k);
    for (int i=0; i<k; i++){
        for (int j=0; j<k; j++){
            matrix[i][j] = tmpMatrix[j][k-i-1];
        }
    }
}

//
// Created by Idan Hauser on 11/04/2020.
//

#ifndef FINALPROJECT_FUNCTIONS_H
#define FINALPROJECT_FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"

#define convertRowToLetter(row) (row+64)
#define convertChToInt(x) (x-'0')
#define convertIntToCh(x) (x+'0')
#define convertLetterToRow(letter)(letter-64)

#define N 4
#define M 4

#define ROWS N+1
#define COLS M+1


typedef char boardPos[2];

typedef struct _move {
    char rows, cols;
} Move;


typedef struct _movesArray {
    unsigned int size;
    struct _move *moves;
} movesArray;


typedef struct _boardPosArray {
    unsigned int size;
    boardPos *positions;
} boardPosArray;


boardPosArray **validMoves(movesArray **moves, char **board);

bool deleteillegalMove(movesArray *pArray, int IdxToDel);

void checkMemoryAllocation(void *ptr);

bool CheckifMovesisValid(movesArray *pArray, char **board, int currRow, int CurrCol);

bool isOutOfBorder(int row, int col);

void reComputeMovemntArray(movesArray *pArr);

boardPosArray **BuildingToNewArray(movesArray **moves);

void CopyValidBoardPositions(boardPosArray *newArr, movesArray *validMove, int refRow);

void copyGameBoard(char *pDes, char *pSrc);

//ex5
typedef unsigned char BYTE; //ex5
#define posBitSize 3 // ex5

void saveListToBinFile(char *file_name, boardPosArray *pos_arr);

BYTE *CompressByteArr(BYTE *pArr, short int size, short int *bitsSize);

BYTE *PositionToByteArray(boardPos *pArr, short int size);
//

//ex6
#define OPEN_FAILED -1
#define ILLEAGAL_PATH 1
#define PATH_COVERED_ALL_BOARD 2
#define PATH_DIDNT_COVERED_BOARD 3

#define TREEHIGHBITS 0xE0 // 1110 0000
//
#endif //FINALPROJECT_FUNCTIONS_H

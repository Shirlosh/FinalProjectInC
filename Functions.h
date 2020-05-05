//
// Created by Idan Hauser on 11/04/2020.
//בסדק

#ifndef FINALPROJECT_FUNCTIONS_H
#define FINALPROJECT_FUNCTIONS_H

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"

#define ConvertFomRoWToLettervalidMove(row) (row+65)
#define ConvertChToDec(x) (x-'0')
#define N 4
#define M 4


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

void deleteillegalMove(movesArray *pArray, int IdxToDel);

void checkMemoryAllocation(void *ptr);

bool CheckifMovesisValid(movesArray *pArray, char **board, int currRow, int CurrCol);

bool isOutOfBorder(int row, int col);

void reComputeMovemntArray(movesArray *pArr);

boardPosArray **BuildingToNewArray(movesArray **moves);

void CopyValidBoardPositions(boardPosArray *array, movesArray *array1);


#endif //FINALPROJECT_FUNCTIONS_H

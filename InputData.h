//
// Created by Idan Hauser on 16/04/2020.
//

#ifndef FINALPROJECT_INPUTDATA_H
#define FINALPROJECT_INPUTDATA_H


#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"
#include "ListDisplayFunctions.h"

Move *getMovementArr(int size);

movesArray **getMovesArray();

char **getCharBoard();

movesList *getMoveList();

void freeMoveList(movesList *pList);
void freeGameBord(char **pBoard);
void freeMovmentArray(movesArray **pMoveArr);
void freeBoardPosArr(boardPosArray **board);

#endif //FINALPROJECT_INPUTDATA_H

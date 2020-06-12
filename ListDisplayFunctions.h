//
// Created by Idan Hauser on 05/05/2020.
//

#ifndef FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"


#define StartFlag '#'

///***List Defintions***
typedef struct _moveCell {
    Move move;
    struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
    moveCell *head;
    moveCell *tail;
} movesList;

//ex6
int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board);

movesList *readMoveList(FILE *f);

BYTE *createByteArr(FILE *f, short int size, short int byteSize);

movesList *byteArrtoMovelist(BYTE *byteArr, short int size);


int buildingGamePlay(char **gameBoard, movesList *moves_list, const boardPos start, const char **board);

int display(movesList *moves_list, boardPos start, char **board);

void deleteNodeFromList(movesList *moves_list, moveCell *toDelete);

bool checkBoardCell(const char **board, char **gameBoard, Move pMove);


void printGameBoard(char **pGameBoard);

///***List functions***

void insertNodeToEndList(movesList *pList, moveCell *pNode);

void insertDataToEndList(movesList *pList, Move mov);

moveCell *CreateNode(movesList *pList, Move mov);

void makeEmptyList(movesList *pList);

bool isEmptyList(movesList *pList);

void insertDataToHeadList(movesList *pList, Move move);

#endif //FINALPROJCT_LISTDISPLAYFUNCTIONS_H

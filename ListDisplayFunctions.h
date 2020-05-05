//
// Created by Idan Hauser on 05/05/2020.
//

#ifndef FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define FINALPROJCT_LISTDISPLAYFUNCTIONS_H

#include "Functions.h"

#define convertFromLetterToRow(letter) (letter-'65')
#define StartFlag '#'

typedef struct _moveCell {
    Move move;
    struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
    moveCell *head;
    moveCell *tail;
} movesList;

int buildingGamePlay(char **gameBoard, movesList *moves_list, boardPos *start, const char **board);

int display(movesList *moves_list, boardPos *start, char **board);

void deleteNodeFromList(movesList *moves_list, moveCell *toDelete);

bool checkBoardCell(const char **board, char **gameBoard, Move pMove);

int buildingGamePlay(char **gameBoard, movesList *moves_list, boardPos *start, const char **board);

#endif //FINALPROJCT_LISTDISPLAYFUNCTIONS_H

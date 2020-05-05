//
// Created by Idan Hauser on 05/05/2020.
//

#ifndef FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define FINALPROJCT_LISTDISPLAYFUNCTIONS_H

#include "Functions.h"
#include <curses.h>
#define convertFromLetterToRow(letter) (letter-65)

typedef struct _moveCell {
    Move move;
    struct _moveCell *next, *prev;
} moveCell;
typedef struct _movesList {
    moveCell *head;
    moveCell *tail;
} movesList;

int display(movesList *moves_list, boardPos *start, char **board);
void printOnScreen(boardPos *start);
#endif //FINALPROJCT_LISTDISPLAYFUNCTIONS_H

//
// Created by Idan Hauser on 05/05/2020.
//

#include "ListDisplayFunctions.h"


int display(movesList *moves_list, boardPos *start, char **board) {
    printOnScreen(start);
    return 0;
}

void printOnScreen(boardPos *start) {
    for (int i = 0; i < (int) convertFromLetterToRow(start[0]); ++i) {
        move(3, 4);
    }
}

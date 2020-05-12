
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"
#include "InputData.h"


int main() {
    boardPosArray **arrayWithValidPositions = NULL;
    boardPos start;
    movesArray **pmoves_arr = NULL;
    char **pboard = NULL;
    movesList *pMovesList = NULL;
    pmoves_arr = getMovesArray();
    pboard = getCharBoard();
    arrayWithValidPositions = validMoves(pmoves_arr, pboard);//this is the for Part 1 of the project
    pMovesList = getMoveList();
    display(pMovesList, start, pboard);
}

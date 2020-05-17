////VER 2.0

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
    movesArray **pMoves_arr = NULL;
    char **pboard = NULL;
    movesList *pMovesList = NULL;
    pMoves_arr = getMovesArray();
    pboard = getCharBoard();
    arrayWithValidPositions = validMoves(pMoves_arr, pboard);//this is the for Part 1 of the project
    pMovesList = getMoveList();
    display(pMovesList, start, pboard);

    freeMoveList(pMovesList);
    freeGameBord(pboard);
    freeMovmentArray(pMoves_arr);

}

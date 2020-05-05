
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"
#include "InputData.h"


int main() {
    boardPos start;
    movesArray **pmoves_arr = NULL;
    char **pboard = NULL;
    movesList *pMovesList = NULL;
    pmoves_arr = getMovesArray();
    pboard = getCharBoard();
    validMoves(pmoves_arr, pboard);
    pMovesList = getMoveList();
    display(pMovesList, start, pboard);
}

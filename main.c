////VER 2.5.5

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"
#include "InputData.h"
#include "SaveToFile.h"
#include "FindFullPathList.h"
#include "TreePath.h"


int main() {

    char *file_name = NULL;
    boardPosArray **arrayWithValidPositions = NULL;
    boardPos start="A2";
    movesArray **pMoves_arr = NULL;
    char **pboard = NULL;
    movesList *pMovesList = NULL;
    pMoves_arr = getMovesArray();
    pboard = getCharBoard();
    arrayWithValidPositions = validMoves(pMoves_arr, pboard);///this is the for Part 1 of the project
    pMovesList = getMoveList();
    display(pMovesList, start, pboard);///this is the for Part 2 of the project

    start[0] = 'A';
    start[1] = (char)2;
    findAllPossiblePaths(start, pMoves_arr, pboard);///this is the for Part 3 of the project

      findPathCoveringAllBoard(start,pMoves_arr,pboard);//This is for part 4////

 //   saveListToBinFile(file_name, arrayWithValidPositions[0]);//This is for part 5////todo : need to check why this functions calls only as one dimesntion arr,,,



    freeMoveList(pMovesList);
    freeGameBord(pboard);
    freeMovmentArray(pMoves_arr);

}

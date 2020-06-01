//
// Created by Idan Hauser on 21/05/2020.
//

#include "FindFullPathList.h"
#include "Functions.h"

void findPathCoveringAllBoard_helper(movesList *pList, boardPosArray **pArray);

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
    Move mov;
    movesList *moveLst = NULL;
    boardPosArray **arrayWithValidPositions = NULL;

    arrayWithValidPositions = validMoves(moves, board);


    makeEmptyList(moveLst);
    mov.rows = (char) convertLetterToRow(start[0]);
    mov.cols = (char) convertChToInt(start[1]);
    insertDataToEndList(moveLst, mov);

    findPathCoveringAllBoard_helper(moveLst, arrayWithValidPositions);
}

void findPathCoveringAllBoard_helper(movesList *pList, boardPosArray **pArray) {

}

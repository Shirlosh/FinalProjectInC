//
// Created by Idan Hauser on 21/05/2020.
//

#include "FindFullPathList.h"
#include "Functions.h"

void findPathCoveringAllBoard_helper(movesList *pList, boardPosArray **pArray);

unsigned int countNumberOfValidCells(char **pBoard);


movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
    Move mov;
    pathTree pathTree;
    movesList *moveLst = NULL;
    unsigned int counter = 0;
    boardPosArray **arrayWithValidPositions = NULL;
    counter = countNumberOfValidCells(board);
    pathTree = findAllPossiblePaths(start, moves, board);
    makeEmptyList(moveLst);
    mov.rows = (char) convertLetterToRow(start[0]);
    mov.cols = (char) convertChToInt(start[1]);
    insertDataToEndList(moveLst, mov);
    findPathCoveringAllBoard_helper(moveLst, arrayWithValidPositions);
    insertDataToHeadList(moveLst, mov);
}

void insertDataToHeadList(movesList *pList, Move move) {
    moveCell *pMoveNode = NULL;
    pMoveNode = CreateNode(pList, move);
    pMoveNode->next = pList->head;
    if (pList->tail == NULL)
        pList->tail = pMoveNode;
    pList->head = pMoveNode;
    pList->head->prev = NULL;
}

unsigned int countNumberOfValidCells(char **pBoard) {
    unsigned int counter = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (pBoard[i][j] != '*') {
                counter++;
            }
        }
    }
    return counter;
}

void findPathCoveringAllBoard_helper(movesList *pList, boardPosArray **pArray) {

}

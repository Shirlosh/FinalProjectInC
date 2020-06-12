//
// Created by Idan Hauser on 21/05/2020.
//

#include "FindFullPathList.h"
#include "Functions.h"


unsigned int countNumberOfValidCells(char **pBoard);


bool findPathCoveringAllBoard_helper(treeNode *pArray, unsigned int counter, movesList *pList);

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
    Move mov;
    unsigned int counter = 0;
    pathTree pathTree;
    movesList moveLst;
    bool isValid = false;
    boardPosArray **arrayWithValidPositions = NULL;

    counter = countNumberOfValidCells(board);
    pathTree = findAllPossiblePaths(start, moves, board);
    makeEmptyList(&moveLst);///HERE WE MAY HAVE A BUG

    //insertDataToEndList(moveLst, mov);
    isValid = findPathCoveringAllBoard_helper(pathTree.head, counter - 1, &moveLst);
    if (isValid) {
        //The first one we dont want to insert to the list
        /* mov.rows = (char) convertLetterToRow(start[0]);
         mov.cols = (char) convertChToInt(start[1]);*///
        // insertDataToHeadList(moveLst, mov);
    } else {
        return NULL;
    }
    return &moveLst;
}


void insertDataToHeadList(movesList *pList, Move move) {
    moveCell *pMoveNode = NULL;
    pMoveNode = CreateNode(pList, move);
    pMoveNode->prev = NULL;
    pMoveNode->next = pList->head;

    if (pList->tail == NULL)
        pList->tail = pMoveNode;
    else
        pList->head->prev = pMoveNode;
    pList->head = pMoveNode;

    pList->head->prev = NULL;
}

unsigned int countNumberOfValidCells(char **pBoard) {
    unsigned int counter = 0;
    for (int i = 1; i < ROWS; ++i) {
        for (int j = 1; j < COLS; ++j) {
            if (pBoard[i][j] != '*') {
                counter++;
            }
        }
    }
    return counter;
}

bool findPathCoveringAllBoard_helper(treeNode *pArray, unsigned int counter, movesList *pList) {
    if (counter == 0) {
        return true;
    } else {
        if (pArray == NULL) {
            return false;
        }
        treeNodeListCell *pNodeListCell = NULL;
        Move mov;
        treeNode *pNextNode = NULL;
        bool found = false;
        {
            pNodeListCell = pArray->next_possible_positions;
            pNextNode = pNodeListCell->node;
            /// for some reason this condition doesnt work...necause for somereason pNodeListCell->next != NULL but
            ///the data inside the next is null..and in the next itiration it will die.
            while ((pNextNode != NULL) &&
                   !found) {

                if (findPathCoveringAllBoard_helper(pNextNode, counter - 1, pList)) {
                    found = true;// we found a good position - we need to put it in the list
                }
                if (!found)
                    pNextNode = pNodeListCell->next->node;
            }
        }
        if (found) {///todo: i need to put the move in the list with refernce to prevoius position maybe i should use movesArray **moves
            //notice that the fater in the node position and the one of the list is the son we need to diffrencr between them
            mov.rows = (char) (convertLetterToRow(pNextNode->position[0]) -
                               (char) convertLetterToRow(pArray->position[0]));
            mov.cols = (char) (pNextNode->position[1] - pArray->position[1]);
            insertDataToHeadList(pList, mov);
            return true;
        }


    }
    return false;

}



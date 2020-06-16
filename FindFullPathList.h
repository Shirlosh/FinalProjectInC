//
// Created by Idan Hauser on 21/05/2020.
//

#ifndef FINALPROJCT_FINDFULLPATHLIST_H
#define FINALPROJCT_FINDFULLPATHLIST_H


#include "Functions.h"
#include "ListDisplayFunctions.h"
#include "TreePath.h"

movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);

unsigned int countNumberOfValidCells(char **pBoard);


bool findPathCoveringAllBoard_helper(treeNode *pArray, unsigned int counter, movesList *pList);

#endif //FINALPROJCT_FINDFULLPATHLIST_H


#ifndef FINALPROJCT_TREEPATH_H
#define FINALPROJCT_TREEPATH_H

#include "Functions.h"
#include "ListDisplayFunctions.h"

struct _treeNodeListCell;

typedef struct _treeNode {
	boardPos position;
	struct _treeNodeListCell *next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {

	treeNode *node;
	struct _treeNodeListCell *next;
} treeNodeListCell;


typedef struct _pathTree {
	treeNode *head;
} pathTree;

//prototypes for ex3 - build a tree from all the vaild positions in the board
treeNode *BuildTreeRec(boardPos pos, boardPosArray **posArr, boardPos *branch, unsigned int branchSize);
pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board);
boardPos *branchDuplicate(boardPos *oldBranch, int *branchSize, boardPos pos);
treeNode *CreateNewTreeNode(boardPos pos, unsigned int listCellSize);
bool isLoop(boardPos *branch, unsigned int size);
//

//prototypes for ex4 = checks if the path covers the all board
movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board);
unsigned int countNumberOfValidCells(char **pBoard);
bool findPathCoveringAllBoard_helper(treeNode *pArray, unsigned int counter, movesList **pList);
//


#endif //FINALPROJCT_TREEPATH_H


#include "TreePath.h"

/// This function checks if there is a full valid path in the board
/// The first place we start from to find the path\param start
///Valid moves in the bodard \param moves
///the play board \param board
/// return the full path or null if no found\return
movesList *findPathCoveringAllBoard(boardPos start, movesArray **moves, char **board) {
	Move mov;
	unsigned int counter = 0;
	pathTree pathTree;
	movesList *moveLst;
	bool isValid = false;
	boardPosArray **arrayWithValidPositions = NULL;

	counter = countNumberOfValidCells(board);
	pathTree = findAllPossiblePaths(start, moves, board);
	moveLst = (movesList*)malloc(sizeof(movesList));
	checkMemoryAllocation(moveLst);
	makeEmptyList(moveLst);

	isValid = findPathCoveringAllBoard_helper(pathTree.head, counter - 1, &moveLst);

	if (isValid)
		return moveLst;
	else
		return NULL;

}


/// This function insert data into the head of the list
/// The list\param pList
/// the data we want to insert into\param move
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
/// This function counts how many valid cells we have
///The play board \param pBoard
/// how many valid cells\return
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
/// This is a rec function that build the path with the help of the tree in oreder to find a valid path in the board
/// the object of the tree with all the paths\param pArray
///counts how many position we have to count in oreder to find a full path\param counter
///the list that holds a valid path \param pList
///retunes a valid path in the play board or null if coulndt find \return
bool findPathCoveringAllBoard_helper(treeNode *pArray, unsigned int counter, movesList **pList) {
	if (counter == 0) {
		return true;
	}
	else {
		if (pArray == NULL) {
			return false;
		}
		treeNodeListCell *pNodeListCell = NULL;
		Move mov;
		treeNode *pNextNode = NULL;
		bool found = false;


		if (pArray->next_possible_positions) {
			pNodeListCell = pArray->next_possible_positions;
			pNextNode = pNodeListCell->node;
		}
		while ((pNextNode != NULL) && !found) {

			if (findPathCoveringAllBoard_helper(pNextNode, counter - 1, pList)) {
				found = true;// we found a good position - we need to put it in the list
			}
			if (!found)
				if ((pNodeListCell) && (pNodeListCell->next)) {
					pNextNode = pNodeListCell->next->node;
					pNodeListCell = pNextNode->next_possible_positions;
				}
				else {
					pNextNode = NULL;
				}
		}

		if (found) {
			mov.rows = (char)(convertLetterToRow(pNextNode->position[0]) -
				(char)convertLetterToRow(pArray->position[0]));
			mov.cols = (char)(pNextNode->position[1] - pArray->position[1]);
			insertDataToHeadList(*pList, mov);
			return true;
		}


	}
	return false;

}

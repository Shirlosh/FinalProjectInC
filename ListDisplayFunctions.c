
#include "ListDisplayFunctions.h"
/// This function get a list and checks if the list with apath and we check if its 
/// valid and also print in into the screen, and delete the ilegal ndoes 
/// the list we want to check this list holds path we want to check \param moves_list 
/// The first position we start from the path\param start 
///The game bodard \param board 
/// retunes how much nodes we deleted on the ppath \return 
int display(movesList *moves_list, boardPos start, char **board) {
	char **pGameBoard = NULL;
	int deletedNodes = 0;

	pGameBoard = (char **)calloc(ROWS, sizeof(char *)); 
	checkMemoryAllocation(pGameBoard);
	for (int i = 1; i < ROWS; ++i) {
		pGameBoard[i] = (char *)calloc(COLS, sizeof(char));
		checkMemoryAllocation(pGameBoard[i]);
		copyGameBoard(pGameBoard[i], board[i]);
	}
	deletedNodes = buildingGamePlay(pGameBoard, moves_list, start, (const char **)board);
	printGameBoard(pGameBoard);
	return deletedNodes;
}

/// This function copy the board game and especially the '*' to the board we are
/// going to print to the user
/// This is the arr we are going to copy to\param pDes
///From this arr we are going to copy \param pSrc
void copyGameBoard(char *pDes, char *pSrc) {
	for (int i = 1; i < COLS; ++i) {
		if (pSrc[i] == '*') {
			pDes[i] = pSrc[i];
		}
	}
}

/// Prints the game board
///The game board we want to print \param pGameBoard
void printGameBoard(char **pGameBoard) {
	printf("\n");
	printf("\t");
	for (int j = 1; j <= M; ++j) {
		if (j != 0) {
			printf("%d \t", j);
		}
		else {
			printf("\t");
		}
	}
	printf("\n");
	for (int i = 1; i < ROWS; ++i) {
		printf("%c \t", convertRowToLetter(i));
		for (int j = 1; j < COLS; ++j) {
			printf("%c \t", pGameBoard[i][j]);
		}
		printf("\n");
	}
}

/// This is the main function of part two
///here we check if the nest place in referce to the previous, by the list movments is valid
/// valid is when the cell is empty and not out of border
///if its not valid it will remove this node from to the list else it will put a number of a move in the board
///The board we are going to fill with numbers and going to print to the user \param gameBoard
///The list we get of movments, if a movment is not valid we are updating the list \param moves_list
/// The start position no '*'\param start
/// The board with the '*' we checks that everything is valid\param board
/// tretuns the number of nodes we deleted from the list\return
int buildingGamePlay(char **gameBoard, movesList *moves_list, const boardPos start, const char **board) {
	moveCell *pMove = NULL;
	moveCell *next = NULL;
	Move mov;
	Move pMovRef = { '0', '0' };
	int moveCount = 1;
	int deletedNodes = 0;
	pMove = moves_list->head;


	gameBoard[convertLetterToRow(start[0])][start[1]] = StartFlag;
	pMovRef.rows = (char)convertLetterToRow(start[0]);
	pMovRef.cols = (char)start[1];


	while (pMove != NULL) { 
		next = pMove->next;
		mov = pMove->move;
		mov.cols = (char)((int)mov.cols + pMovRef.cols);
		mov.rows = (char)((int)mov.rows + pMovRef.rows);

		if (checkBoardCell(board, gameBoard, mov)) {
			gameBoard[(int)mov.rows][(int)mov.cols] = (char)convertIntToCh(moveCount);
			moveCount++;
			pMovRef.rows = mov.rows;
			pMovRef.cols = mov.cols;
		}
		else {
			//delete from list
			deleteNodeFromList(moves_list, pMove);
			deletedNodes++;
		}

		pMove = next;

	}
	return deletedNodes;
}

/// we are checks where is the node we want to delete from the list
///and we free it and removes from the list and updating the next and prevs of the rest if the nodes
/// The list we update\param moves_list
/// The node we want to delete\param toDelete
void deleteNodeFromList(movesList *moves_list, moveCell *toDelete) {
	moveCell *prevNode = toDelete->prev;
	if (moves_list->head == moves_list->tail)
		moves_list->head = moves_list->tail = NULL;
	else if (moves_list->head == toDelete) 
	{
		moves_list->head = moves_list->head->next;
		//moves_list->head->prev = NULL;//TODO TO UNCOMMENT
	}
	else if (moves_list->tail == toDelete)
	{
		moves_list->tail = moves_list->tail->prev;
		moves_list->tail->next = NULL;
	}
	else {
		prevNode->next = toDelete->next;
		toDelete->next->prev = prevNode;
	}
	//the list is dynamic (allocated with malloc) we have to free the node
	free(toDelete);
}

/// Check if a position in the board doesnt have a '*' and also
///not outside of the borders
///The board we checks \param board
///Out gameplay board \param gameBoard
/// The new position\param pMove
/// retunes true if everything is valid. else false\return
bool checkBoardCell(const char **board, char **gameBoard, Move pMove) {
	bool isValid = false;
	if (!isOutOfBorder((int)pMove.rows, (int)pMove.cols)) {
		if ((board[(int)pMove.rows][(int)pMove.cols] != '*') &&
			(gameBoard[(int)pMove.rows][(int)pMove.cols] == '\0')) {
			isValid = true;
		}
	}
	return isValid;
}

/// insert a new node to the list
///this function is for building the list
/// The list we build\param pList
///The data we want to put in the end of list \param mov
void insertDataToEndList(movesList *pList, Move mov) {
	moveCell *newNode = NULL;
	newNode = CreateNode(pList, mov);
	insertNodeToEndList(pList, newNode);
}

/// Creates the data in a node and checking mem allocation.
/// The list we update\param pList
/// The data the ndoe is going to hold\param mov
/// retuns new node\return
moveCell *CreateNode(movesList *pList, Move mov) {
	moveCell *item;

	item = (moveCell *)malloc(sizeof(moveCell));
	checkMemoryAllocation(item);

	item->move = mov;
	item->next = NULL;
	item->prev = pList->tail;

	return item;
}

/// We insert the node to the end of the list
/// The list we want to update\param pList
/// new node\param pNode
void insertNodeToEndList(movesList *pList, moveCell *pNode) {

	if (isEmptyList(pList)) {
		pList->tail = pList->head = pNode;
		pList->tail->prev = pNode;
	}
	else {
		pList->tail->next = pNode;
		pList->tail = pNode;
	}
	pNode->next = NULL;
}

/// Checks if list is empty
/// The list we checks\param pList
/// True if list is empty else false\return
bool isEmptyList(movesList *pList) {
	return pList->head == NULL ? true : false;
}

/// Makes a new list by putting NULL
/// The list we want to ini\param pList
void makeEmptyList(movesList *pList) {
	pList->head = pList->tail = NULL;
}

/// Freeing the memory alocation of the list
///Deallocates the space previously allocated by malloc(), calloc(),
/// the list we want to free\param pList
void freeMoveList(movesList *pList) {
	moveCell *pNode = NULL;
	moveCell *pNext = NULL;

	if (!pList)
		return;

	for (pNode = pList->head; pNode != NULL; pNode = pNext) {
		pNext = pNode->next;
		free(pNode);
	}

	free(pList);
}



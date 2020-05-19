//
// Created by Idan Hauser on 16/04/2020.
//

#include "InputData.h"
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"

/// Getting from the user the movesArray and builds it
///return the move array \return
movesArray **getMovesArray() {
    movesArray *pInput = NULL;
    movesArray **pMovesArr = NULL;

	pMovesArr = (movesArray **)calloc(ROWS, sizeof(movesArray *)); // MoveArr Allocation
	checkMemoryAllocation(pMovesArr);

	for (int i = 1; i < ROWS; ++i) {
		pMovesArr[i] = (movesArray *)calloc(COLS, sizeof(movesArray));
		checkMemoryAllocation(pMovesArr[i]);

		for (int j = 1; j < COLS; ++j) {
			pInput = &pMovesArr[i][j];
			scanf("%u", &(pInput->size));
			pInput->moves = getMovementArr(pInput->size);
		}
	}
	return pMovesArr;
}

/// getting from the user the char array
///retuns the game arrat \return
char **getCharBoard() {
	char **pGameBoard = NULL, ch;

	pGameBoard = (char **)calloc(ROWS, sizeof(char *));
	checkMemoryAllocation(pGameBoard);
	getchar(); //add
	for (int i = 1; i < ROWS; ++i) {

		pGameBoard[i] = (char *)calloc(COLS, sizeof(char));
		checkMemoryAllocation(pGameBoard[i]);
		for (int j = 1; j <COLS; ++j) {
			scanf("%c", &ch);
			getchar();// add
			pGameBoard[i][j] = ch;
		}
	}
	return pGameBoard;
}

/// getting from the user the momvesment array amd  builds it
/// size of each arr - this arr start from the 0 index!!!\param size
/// retunes the new arr\return
Move *getMovementArr(int size) {
	int row, col;
	Move *array = (Move *)calloc(size, sizeof(Move));
	checkMemoryAllocation(array);
	array->cols = 0;
	array->rows = 0;
	for (int i = 0; i < size; ++i) {
		fflush(stdin);
		scanf("%d", &row);
		array[i].rows = (char)row;
		fflush(stdin);
		scanf("%d", &col);
		array[i].cols = (char)col;

    }


    return array;
}

/// This function to get the data of the list - movments
///retunes a list \return
movesList *getMoveList() {
	movesList *move_list = NULL;
	move_list = (movesList *)calloc(1, sizeof(movesList));
	checkMemoryAllocation(move_list);

	makeEmptyList(move_list);
	Move mov;
	int howMany;
	printf("How many moves?\n");
	fflush(stdin);

	scanf("%d", &howMany);
	for (int i = 0; i < howMany; i++) {
		fflush(stdin);
		scanf("%d", &mov.rows);
		fflush(stdin);
		scanf("%d", &mov.cols);
		insertDataToEndList(move_list, mov);
	}


    return move_list;
}

/// Freeing the memory alocation of the list
///Deallocates the space previously allocated by malloc(), calloc(),
/// the list we want to free\param pList
void freeMoveList(movesList *pList) {
    moveCell *pNode = NULL;
    moveCell *pNext = NULL;

    for (pNode = pList->head; pNode != NULL; pNode = pNext) {
        pNext = pNode->next;
        free(pNode);
    }
}

///  Freeing the memory alocation of Gameboard chars
///Deallocates the space previously allocated by malloc(), calloc(),
/// The game bord char type\param pBoard
void freeGameBord(char **pBoard) {
	for (int i = 0; i <ROWS; ++i) {
		free(pBoard[i]);
	}
	free(pBoard);
}

///  Freeing the memory alocation of movmentsArray and everything it holds
///Deallocates the space previously allocated by malloc(), calloc(),
/// The movement array\param pBoard
void freeMovmentArray(movesArray **pMoveArr) {
	for (int i = 1; i < ROWS; ++i) {
		for (int j = 1; j < COLS; ++j) {
			free(pMoveArr[i][j].moves);
		}
		free(pMoveArr[i]);
	}
	free(pMoveArr);
}
///  Freeing the memory alocation of boardPosArray and everything it holds
///Deallocates the space previously allocated by malloc(), calloc(),
/// The boardPos Array\param pBoard
void freeBoardPosArr(boardPosArray **board) {
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			free(board[i][j].positions);
		}
		free(board[i]);
	}
	free(board);
}

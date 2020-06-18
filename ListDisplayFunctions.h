
#ifndef FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define FINALPROJCT_LISTDISPLAYFUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include "Functions.h"

//***List Defintions***//
typedef struct _moveCell {
	Move move;
	struct _moveCell *next, *prev;
} moveCell;

typedef struct _movesList {
	moveCell *head;
	moveCell *tail;
} movesList;


//prototypes for ex2 = prints the board with the movelist :
int buildingGamePlay(char **gameBoard, movesList *moves_list, const boardPos start, const char **board);
int display(movesList *moves_list, boardPos start, char **board);
void deleteNodeFromList(movesList *moves_list, moveCell *toDelete);
bool checkBoardCell(const char **board, char **gameBoard, Move pMove);
void printGameBoard(char **pGameBoard);
// 


//***List functions***//
void insertNodeToEndList(movesList *pList, moveCell *pNode);
void insertDataToEndList(movesList *pList, Move mov);
moveCell *CreateNode(movesList *pList, Move mov);
void makeEmptyList(movesList *pList);
bool isEmptyList(movesList *pList);
void insertDataToHeadList(movesList *pList, Move move);
void freeMoveList(movesList *pList);

#endif //FINALPROJCT_LISTDISPLAYFUNCTIONS_H

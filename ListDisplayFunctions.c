//
// Created by Idan Hauser on 05/05/2020.
//

#include "ListDisplayFunctions.h"


int display(movesList *moves_list, boardPos start, char **board) {
    char **pGameBoard = NULL;
    int deletedNodes = 0;
    start[0] = 'A';
    start[1] = '2';
    pGameBoard = (char **) calloc(N, sizeof(char *));
    checkMemoryAllocation(pGameBoard);
    for (int i = 0; i < N; ++i) {
        pGameBoard[i] = (char *) calloc(N, sizeof(char));
        checkMemoryAllocation(pGameBoard[i]);
    }
    deletedNodes = buildingGamePlay(pGameBoard, moves_list, start, (const char **) board);
    printGameBoard(pGameBoard);
    return deletedNodes;
}

/// Prints the game board
///The game board we want to print \param pGameBoard
void printGameBoard(char **pGameBoard) {
    for (int j = 1; j <= M; ++j) {
        if (j != 0) {
            printf("%d \t", j);
        } else {
            printf("\t");
        }
    }
    for (int i = 1; i <=N; ++i) {
        printf("%c \t", ConvertFomRoWToLettervalidMove(i));
        for (int j = 0; j < M; ++j) {
            printf("%c \t", pGameBoard[i][j]);
        }
        printf("\n");
    }
}


int buildingGamePlay(char **gameBoard, movesList *moves_list, const boardPos start, const char **board) {
    moveCell *pMove = NULL;
    Move mov;
    Move pMovRef = {'0', '0'};
    int moveCount = 0;
    int deletedNodes = 0;
    gameBoard[convertFromLetterToRow(start[0])][ConvertChToDec( start[1])] = StartFlag;
    pMovRef.rows = (char) convertFromLetterToRow(start[0]);
    pMovRef.cols = (char) ConvertChToDec( start[1]);
    for (pMove = moves_list->head; pMove != NULL; pMove = pMove->next) {
        mov = pMove->move;
        mov.cols = (char) ((int) mov.cols + pMovRef.cols);
        mov.rows = (char) ((int) mov.rows + pMovRef.rows);

        if (checkBoardCell(board, gameBoard, mov)) {
            gameBoard[(int) mov.rows][(int) mov.cols] = (char) ++moveCount;
        } else {
            //delete from list
            deleteNodeFromList(moves_list, pMove);///TODO : NEED TO CONNECT THE PERV
            deletedNodes++;
        }
    }
    return deletedNodes;
}


void deleteNodeFromList(movesList *moves_list, moveCell *toDelete) {
    moveCell *prevNode = toDelete->prev;
    if (moves_list->head == moves_list->tail) // == node)
        moves_list->head = moves_list->tail = NULL;
    else if (moves_list->head == toDelete) // or node->prev == NULL
    {
        moves_list->head = moves_list->head->next;
    } else if (moves_list->tail == toDelete) // or node->next == NULL
    {
        moves_list->tail->next = NULL;
    } else {
        prevNode->next = toDelete->next;
    }
    //the list is dynamic (allocated with malloc) we have to free the node
    free(toDelete);
}


bool checkBoardCell(const char **board, char **gameBoard, Move pMove) {
    bool isValid = false;
    if (!isOutOfBorder((int) pMove.rows, (int) pMove.cols)) {
        if ((board[(int) pMove.rows][(int) pMove.cols] != '*') &&
            (gameBoard[(int) pMove.rows][(int) pMove.cols] == '0')) {
            isValid = true;
        }
    }
    return isValid;
}

void insertDataToEndList(movesList *pList, Move mov) {
    moveCell *newNode = NULL;
    newNode = CreateNode(pList, mov);
    insertNodeToEndList(pList, newNode);
}

moveCell *CreateNode(movesList *pList, Move mov) {
    moveCell *item;

    item = (moveCell *) malloc(sizeof(moveCell));
    checkMemoryAllocation(item);

    item->move = mov;
    item->next = pList->tail;
    // item->prev = pList->tail->prev;
    return item;
}

void insertNodeToEndList(movesList *pList, moveCell *pNode) {
    moveCell *savePrev = NULL;
    if (isEmptyList(pList)) {
        pList->tail = pList->head = pNode;
        pList->tail->prev = pNode;
        // pList->head->prev = NULL;
    } else {
        savePrev = pList->tail->prev;
        pList->tail->next = pNode;
        pList->tail = pNode;
        pList->tail->prev = savePrev;
    }
    pNode->next = NULL;
}

bool isEmptyList(movesList *pList) {
    return pList->head == NULL ? true : false;
}

void makeEmptyList(movesList *pList) {
    pList->head = pList->tail = NULL;
}



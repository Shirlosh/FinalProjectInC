//
// Created by Idan Hauser on 05/05/2020.
//

#include "ListDisplayFunctions.h"


void printGameBoard(char **pGameBoard);

int display(movesList *moves_list, boardPos *start, char **board) {
    char **pGameBoard = NULL;
    int deletedNodes = 0;
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

void printGameBoard(char **pGameBoard) {
    for (int i = 0; i < N; ++i) {
        printf("\n");
        for (int j = 0; j < M; ++j) {
            printf("%c \t", pGameBoard[i][j]);
        }
    }
}


int buildingGamePlay(char **gameBoard, movesList *moves_list, boardPos *start, const char **board) {
    moveCell *pMove = NULL;
    Move mov;
    int moveCount = 0;
    int deletedNodes = 0;
    gameBoard[(int) convertFromLetterToRow(start[0])][(int) start[1]] = StartFlag;
    for (pMove = moves_list->head; pMove != NULL; pMove = pMove->next) {
        mov = pMove->move;
        if (checkBoardCell(board, gameBoard, mov)) {
            gameBoard[(int) mov.rows][(int) mov.cols] = (char) ++moveCount;
        } else {
            //delete from list
            deleteNodeFromList(moves_list, pMove);
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
    if ((board[(int) pMove.rows][(int) pMove.cols] != '*') &&
        (gameBoard[(int) pMove.rows][(int) pMove.cols] != '0')) {
        isValid = true;
    }
    return isValid;
}



//
// Created by Idan Hauser on 05/05/2020.
//

#include "ListDisplayFunctions.h"


bool CheckBoardCell();

int display(movesList *moves_list, boardPos *start, char **board) {
    char **pGameBoard = NULL;
    pGameBoard = (char **) calloc(N, sizeof(char *));
    checkMemoryAllocation(pGameBoard);
    for (int i = 0; i < N; ++i) {
        pGameBoard[i] = (char *) calloc(N, sizeof(char));
        checkMemoryAllocation(pGameBoard[i]);
    }
    buildingGamePlay(pGameBoard, moves_list, start, board);

    return 0;
}

void buildingGamePlay(char **gameBoard, movesList *moves_list, boardPos *start, const char **board) {
    moveCell *pMove = NULL;
    int Counter = 0;

    gameBoard[(int) convertFromLetterToRow(start[0])][(int) start[1]] = StartFlag;
    for (pMove = moves_list->head; pMove != NULL; pMove = pMove->next) {
        if (CheckBoardCell(board, gameBoard, pMove->move))//TODO
        {

        } else {
            //delete from list
        }
    }
}

bool CheckBoardCell(const char **board, char **gameBoard, Move *pMove) {
    bool isValid = false;
    if ((board[(int) pMove->rows][(int) pMove->cols] != '*') &&
        (gameBoard[(int) pMove->rows][(int) pMove->cols] != '0')) {
        isValid = true;
    }
    return isValid;
}



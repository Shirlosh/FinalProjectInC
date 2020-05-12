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

    pMovesArr = (movesArray **) calloc(N+1, sizeof(movesArray *));
    checkMemoryAllocation(pMovesArr);
    for (int i = 1; i <=N; ++i) {//rows
        pMovesArr[i] = (movesArray *) calloc(M+1, sizeof(movesArray));
        checkMemoryAllocation(pMovesArr[i]);
        for (int j = 1; j <=M; ++j) {//todo:chanded to start from 1 and not from 0//cols
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
    char **pGameBoard = NULL;
    pGameBoard = (char **) calloc(N+1, sizeof(char *));
    checkMemoryAllocation(pGameBoard);
    for (int i = 1; i <=N; ++i) {
        pGameBoard[i] = (char *) calloc(M+1, sizeof(char));
        checkMemoryAllocation(pGameBoard[i]);
        for (int j = 1; j <=M; ++j) {
            fflush(stdin);
            pGameBoard[i][j] = getchar();
        }
    }
    return pGameBoard;
}

/// getting from the user the momvesment array amd  builds it
/// size of each arr\param size
/// retunes the new arr\return
Move *getMovementArr(int size) {
    int row, col;
    Move *array = (Move *) calloc(size, sizeof(Move));
    checkMemoryAllocation(array);
    for (int i = 0; i < size; ++i) {
        fflush(stdin);
        scanf("%d", &row);
        array[i].rows = (char) row;
        fflush(stdin);
        scanf("%d", &col);
        array[i].cols = (char) col;

    }



    return array;
}

movesList *getMoveList() {
    movesList *move_list = NULL;
    move_list = (movesList *) calloc(1, sizeof(movesList));
    makeEmptyList(move_list);
    Move mov;
    int howMany;
    printf("How many moves?");
    scanf("%d", &howMany);
    for (int i = 1; i <= howMany; ++i) {
        fflush(stdin);
        scanf("%d", &mov.rows);
        fflush(stdin);
        scanf("%d", &mov.cols);
        insertDataToEndList(move_list, mov);
    }


    return move_list;
}

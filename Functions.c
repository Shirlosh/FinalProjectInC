//
// Created by Idan Hauser on 11/04/2020.
//


#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"


/// Check if the positions of every cel is leagal and retuens the new Array
///Array that holds all the cells with the positions  \param moves
/// the board with the chars\param board
///new arr with all the valid positions  \return
boardPosArray **validMoves(movesArray **moves, char **board) {

    for (int i = 1; i < ROWS; ++i) {
        for (int j = 1; j < COLS; ++j) {
            CheckifMovesisValid(&moves[i][j], board, i, j);
        }
    }
    return BuildingToNewArray(moves);
}

/// checks if the position the array of each cell in the pArray is legal if its not
/// removes it, checks if the new positions holds "*" or out of borders
/// The array which holds all the posoitions\param pArray
///The board game \param board
///The row of current cell we check \param currRow
/// The current row of the cell we check \param CurrCol
///none \return
bool CheckifMovesisValid(movesArray *pArray, char **board, int currRow, int CurrCol) {
    Move pMove;
    char tav;
    bool checkAgain = false;
    bool isValid = true;
    int row = 0, col = 0;

    for (int i = 0; i < pArray->size; ++i) {
        pMove = pArray->moves[i];
        row = currRow + (int) pMove.rows;
        col = CurrCol + (int) pMove.cols;

        if (!isOutOfBorder(row, col)) {
            tav = (char) board[row][col];
            if (tav == '*') {
                isValid = false;
            }
        } else {
            isValid = false;
        }
        if (!isValid) {
            checkAgain = deleteillegalMove(pArray,
                                           i);////TODO:I need to fix it, because when i move the last one to the ont i want to delete, i dont check it	//HaveTOcheck it
            if (checkAgain == true) {
                i = i - 1;
                checkAgain = false;
            }
        }
    }
    return isValid;
}

///checks if memory allocation is valid
///The object we want to check \param ptr
void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        puts("Terminating the program! A memory allocation error has been detected");
        exit(1);
    }

}

///     This function checks if the position is out of the array's borders
///the row of the new pos\param row
///the col of the new pos \param col
/// returns true if it is out of border -> else False\return
bool isOutOfBorder(int row, int col) {
    bool isOut = false;
    if ((row >= ROWS) || (col >= COLS) || (col < 1) || (row < 1)) {//todo:need to test it,

        isOut = true;

    }
    return isOut;
}

/// Check if the position we have to remove is in the end of the array, if it is send to
///"reComputeMovemntArray" and deletes it from the arr, if the position in not at the end, it switch it to the end and removes it
///The moves object \param pArray
///the index we want to delete in the array \param idxToDel
bool deleteillegalMove(movesArray *pArray, int idxToDel) {
    Move pMove;
    bool lastMoved = false;
    unsigned int currSize = pArray->size;
    if (currSize == 1) {//the array holds only one movement
        if (idxToDel == 0) {//the array holds only the movement we have to delete
            pArray->size = 0;
            free(pArray->moves);
        } else {
            printf("ERROR");
            exit(1);
        }
    } else if (idxToDel == currSize - 1) {//the movement is the last in the array
        reComputeMovemntArray(pArray);
    } else {
        ////TODO:need to add a flag if im here;
        lastMoved = true;
        pMove = pArray->moves[currSize - 1];//pMove holds the last one on the arr
        pArray->moves[idxToDel] = pMove;//Writing the last move on the one we want to delete
        reComputeMovemntArray(pArray);
    }
    return lastMoved;
}

/// realloc array and reduce its size in one.
///this arr hold the illegal value at the end of the arr and removes it  \param pArr
void reComputeMovemntArray(movesArray *pArr) {
    Move *pMoveArr = NULL;
    unsigned int newSize = pArr->size - 1;
    pMoveArr = (Move *) realloc(pArr->moves, sizeof(Move) * newSize);
    checkMemoryAllocation(pMoveArr);


    pArr->moves = pMoveArr;
    pArr->size = newSize;

}

/// This functions build the new arr that we need to return in part one
///the movement array with all the valid moves \param moves
///return the new array as asked in part A \return
boardPosArray **BuildingToNewArray(movesArray **moves) {
    boardPosArray **validMovesArray = NULL;

    validMovesArray = (boardPosArray **) calloc(ROWS, sizeof(boardPosArray *));
    checkMemoryAllocation(validMovesArray);


    for (int i = 1; i < ROWS; ++i) {
        validMovesArray[i] = (boardPosArray *) calloc(COLS, sizeof(boardPosArray));
        validMovesArray[i]->positions = NULL;
        checkMemoryAllocation(validMovesArray[i]);
        for (int j = 1; j < COLS; ++j) {
            validMovesArray[i][j].size = (moves[i][j]).size;
        }
        CopyValidBoardPositions(validMovesArray[i], moves[i], i);

    }
    return validMovesArray;
}


/// this functions put in boardpositions the letters of the
/// legal positions.
///this funcion build a boardposition array to put in every cell, this new arr holds letters and numbpers as positions
///holds the row of the boardPosArray \param newArr
/// validMove arr that holds all the vallid moves of each cell in the movesArray\param validMove
void CopyValidBoardPositions(boardPosArray *newArr, movesArray *validMove, int refRow) {
    unsigned int arrSize;
    boardPos *bpDes = NULL;


    for (int j = 1; j < COLS; ++j) {
        arrSize = newArr[j].size;
        if (arrSize > 0) {
            newArr[j].positions = (boardPos *) calloc(arrSize, sizeof(boardPos));
            checkMemoryAllocation(newArr[j].positions);
            bpDes = newArr[j].positions;
            for (int i = 0; i < arrSize; ++i) {//should start from 0
                bpDes[i ][0] = (char) convertRowToLetter((validMove[j].moves[i].rows + refRow));
                bpDes[i ][1] = j + validMove[j].moves[i].cols;

            }
        }
    }

}



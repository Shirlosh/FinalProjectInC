//
// Created by Idan Hauser on 12/06/2020.
//

#include "ListDisplayFunctions.h"
#include "FindFullPathList.h"

int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board) {
    FILE* f;
    movesList *movelist=NULL,*fullList=NULL;
    boardPos start;
    short int size;

    f = fopen(file_name, "rb");
    if (f == NULL) return OPEN_FAILED;

    fread(&size, sizeof(short int), 1, f); // read the size of the list
    movelist = readMoveList(f,&start, size);// read movelist from bin file
    fclose(f);

    if (display(movelist, start, board) == size) { // all the nodes deleted
        free(movelist);
        return ILLEAGAL_PATH;
    }

    //display(Movelist, start, board);???

    fullList = findPathCoveringAllBoard(start, moves, board); //error

    if (compareMoveList(fullList,movelist,size) ) { //compare list
        free(movelist);
        return PATH_COVERED_ALL_BOARD;
    }

    else {
        free(movelist);
        return PATH_DIDNT_COVERED_BOARD;
    }


}

///read a bin file and create a movelist
/// return the initializing the start by pointer
movesList* readMoveList(FILE *f, boardPos *start, short int size) {

    BYTE *byteArr;
    movesList *movelist;
    short int byteSize;

    byteSize = (size * 2) * 3; // count bits, each pos contain 2 components (letter and number)
    byteSize = (byteSize / 8) + 1; //amount of bytes

    byteArr = createByteArr(f, size, byteSize);

    movelist = byteArrtoMovelist(byteArr,start, size);

    free(byteArr);
    return movelist;
}

/// scan the positions from the file and create a bytearr with the possitions
BYTE *createByteArr(FILE *f, short int size, short int byteSize) {

    BYTE *byteArr, *posArr, Pmask = TREEHIGHBITS, Smask;
    int iB = 0, iA = 0, j = 5;

    byteArr = (BYTE*)calloc(byteSize, sizeof(short int));// an array of compressed 3bits positions
    fread(byteArr, sizeof(BYTE), byteSize, f);

    posArr = (BYTE*)malloc(2 * size * sizeof(BYTE));

    while (iA < 2 * size) {

        posArr[iA] = (byteArr[iB] & Pmask) >> j;
        iA++;
        Pmask = Pmask >> 3;
        j -= 3;

        if (j < 0 && iA < 2 * size) {// the current possition is seperate between 2 cells

            posArr[iA] = (byteArr[iB] & Pmask) << (-j); // j represent the pending bits
            j += 8;
            Pmask = TREEHIGHBITS >> j;
            iB++;

            posArr[iA] = (posArr[iA] | (byteArr[iB] >> j) & Pmask);// initializing the remaining bits.
            Pmask = TREEHIGHBITS >> 8 - j;
            j -= 3;
            iA++;

        }

        if (j == 0) {
            posArr[iA] = (byteArr[iB] & Pmask);
            Pmask = TREEHIGHBITS;
            j = 5; // 8-3;
            iB++;
            iA++;
        }

    }

    free(byteArr);
    return posArr;
}
/// make a movelist from the byte possitions Array
movesList *byteArrtoMovelist(BYTE *byteArr, boardPos *start, short int size) {

    movesList *List;
    Move move;
    boardPos prev, cur;
    int iL, iB = 2, row,col;

    List = (movesList*)malloc(sizeof(movesList));
    makeEmptyList(List);

    **start = convertRowToLetter(byteArr[0] + 1);//initializing the start
    *((char*)start+1) = (byteArr[1] + 1);// mistake in the movement size!?

    prev[0] = **start;
    prev[1] = *((char*)start + 1);

    for (iL = 0; iL < size-1; iL++,iB+=2) { // a path is the amount of cell -1
        cur[0] = convertRowToLetter(byteArr[iB] + 1);
        cur[1] = byteArr[iB + 1] + 1;

        move = createMove(prev,cur);
        insertDataToEndList(List, move);

        prev[0] = cur[0];
        prev[1] = cur[1];
    }

    return List;
}

Move createMove(boardPos prev,boardPos cur) {

    int  prevROW = convertLetterToRow(prev[0]), prevCOL = (int)prev[1];
    int  curROW = convertLetterToRow(cur[0]), curCOL = (int)cur[1];
    Move newMove;

    newMove.rows = curROW - prevROW;
    newMove.cols = curCOL - prevCOL;

    return newMove;
}


int compareMoveList(movesList* List1, movesList* List2,short int size) {
    moveCell *cur1, *cur2;

    cur1 = List1->head;
    cur2 = List2->head;

    while (size--) {
        if (cur1->move.rows != cur2->move.rows || cur1->move.cols != cur2->move.cols)
            return false;
    }

    return true;
}
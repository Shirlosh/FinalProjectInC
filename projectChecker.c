//
// Created by Idan Hauser on 12/06/2020.
//

#include "ListDisplayFunctions.h"


int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board) {
    FILE* f;
    movesList *Movelist;
    boardPos start;
    boardPosArray **validPosArr;

    f = fopen(file_name, "rb");
    if (f == NULL) return OPEN_FAILED;

    //validPosArr = validMoves(moves, board);
    Movelist = readMoveList(f);// read movelist from bin file &start

    fclose(f);

    //if (!isLegal(Movelist, validPosArr)) // use the func in path 2 that delete illegal move return null if no vaild moves
    //return ILLEAGAL_PATH;

//	display(Movelist, start, board);

    //if (findPathCoveringAllBoard(start, moves, **board) == Movelist)
    //return PATH_COVERED_ALL_BOARD;

//	else
    //	return PATH_DIDNT_COVERED_BOARD;
    // free movelist

}



///read a bin file and create a movelist
movesList* readMoveList(FILE *f) {

    BYTE *byteArr;
    movesList *movelist;
    short int size,byteSize;


    fread(&size, sizeof(short int), 1, f);

    byteSize = (size * 2) * 3; // count bits
    byteSize = (byteSize / 8) + 1; //amount of bytes

    byteArr = createByteArr(f,size, byteSize);
    movelist = byteArrtoMovelist(byteArr, size);

    free(byteArr);
    return movelist;
}

/// scan the positions from the file and create a bytearr with the possitions
BYTE *createByteArr(FILE *f, short int size, short int byteSize) {

    BYTE *byteArr,*posArr,Pmask=TREEHIGHBITS,Smask;
    int iB = 0,iA=0,j=5;

    byteArr = (BYTE*)calloc(byteSize, sizeof(short int));// an array of compressed 3bits positions
    fread(byteArr, sizeof(BYTE), byteSize, f);

    posArr = (BYTE*)malloc(2 * size * sizeof(BYTE));

    while (iA < 2*size) {

        posArr[iA] = (byteArr[iB] & Pmask) >> j ;
        iA++;
        Pmask = Pmask >> 3;
        j -= 3;

        if (j<0 && iA < 2*size) {// the current possition is seperate between 2 cells

            posArr[iA] = (byteArr[iB] & Pmask)<<(-j) ; // j represent the pending bits
            j += 8;
            Pmask = TREEHIGHBITS >>j;
            iB++;

            posArr[iA] = (posArr[iA] | (byteArr[iB]>>j) & Pmask );// utilize the remaining bits.
            Pmask = TREEHIGHBITS >> 8-j;
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



movesList *byteArrtoMovelist(BYTE* byteArr,short int size) {

    movesList *List;
    Move move;
    int iL=0, iB=0;

    List = (movesList*)malloc(sizeof(movesList));
    makeEmptyList(List);

    for (iL = 0; iL < size; iL++) {

        move.rows = convertRowToLetter(byteArr[iB]+1);
        iB++;
        move.cols = convertIntToCh(byteArr[iB] + 1);
        insertDataToEndList(List,move);
        iB++;
    }

    return List;
}


void insertNodeToEndList(movesList *pList, moveCell *pNode);
void insertDataToEndList(movesList *pList, Move mov);
moveCell *CreateNode(movesList *pList, Move mov);
void makeEmptyList(movesList *pList);
bool isEmptyList(movesList *pList);

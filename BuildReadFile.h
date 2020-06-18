#ifndef FINALPROJCT_BUILDREADFILE_H
#define FINALPROJCT_BUILDREADFILE_H

#include "Functions.h"
#include "ListDisplayFunctions.h"

typedef unsigned char BYTE;

#define TREEHIGHBITS 0xE0 // 1110 0000
#define posBitSize 3 

//prototypes for ex5 - create a file and save a move:
void saveListToBinFile(char *file_name, boardPosArray *pos_arr);
BYTE *CompressByteArr(BYTE *pArr, short int size, short int *bitsSize);
BYTE *PositionToByteArray(boardPos *pArr, short int size);
//


//prototypes for ex6
int checkAndDisplayPathFromFile(char *file_name, movesArray **moves, char **board);
movesList *readMoveList(FILE *f, boardPos *start, short int size);
BYTE *createByteArr(FILE *f, short int size, short int byteSize);
movesList *byteArrtoMovelist(BYTE *byteArr, boardPos *start, short int size);
Move createMove(boardPos prev, boardPos cur);
int compareMoveList(movesList* List1, movesList* List2, short int size);
//

#endif //FINALPROJECT_BUILDREADFILE_H 
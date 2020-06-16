#include "Functions.h"

void saveListToBinFile(char *file_name, boardPosArray *pos_arr) {

    FILE *f;
    short int size, bitsSize;
    BYTE *byteArr, *pArr;

    f = fopen(file_name, "wb");
    if (f == NULL) printf("flie opening failed");

    size = (short int)pos_arr->size;

    pArr = PositionToByteArray(pos_arr->positions, 2 * size);// each cell contains 2 components (letter,number)
    byteArr = CompressByteArr(pArr, 2 * size, &bitsSize);

    fwrite(&size, sizeof(short int), 1, f); // print the size to the file
    fwrite(byteArr, sizeof(BYTE), bitsSize, f); // print the byte arr to the file

    free(pArr);
    free(byteArr);

    fclose(f);

}

///takes each byte cell (8bits) of the byte array and compress it into 3bits
///first 8 bits contain the amount of the possitions (short int)
///each 3bits represent a position
/// the function changes bitSize value
BYTE* CompressByteArr(BYTE *pArr, short int size, short int *bitsSize) {

    BYTE *byteArr;
    int iB = 0, iA = 0, j = 5;

    *bitsSize = ((size * posBitSize) / 8) + 1; //how many bit we have to allocate
    byteArr = (BYTE*)calloc(*bitsSize, sizeof(BYTE));

    while (iA < size) {

        byteArr[iB] = byteArr[iB] | (pArr[iA] << j);// set the bits in the position
        j -= 3;// move the position 3 steps back
        iA++;

        if (j < 0 && iA < size) {// -2 is the min value of j
            byteArr[iB] = byteArr[iB] | (pArr[iA]) >> (-j);
            iB++;
            j += 8;
        }// use the value in Ai index again

        if (j == 0) {
            j += 5;//8-3
            byteArr[iB] = byteArr[iB] | pArr[iA];
            iB++;
            iA++;
        }
    }

    return byteArr;
}

/// convert board pos arr to byte array
/// each byte cell contain pos num
BYTE *PositionToByteArray(boardPos *pArr, short int size) {
    BYTE *fourBitsArr;
    int iP = 0, iB = 0;

    fourBitsArr = (BYTE*)malloc(sizeof(BYTE)*size);

    for (iP = 0; iP < size / 2; iP++) {

        fourBitsArr[iB] = convertLetterToRow(pArr[iP][0]) - 1;// first position is 0 although in the array we starts from 1
        iB++;

        fourBitsArr[iB] = convertChToInt(pArr[iP][1]) - 1;// first position is 0 although in the array we starts from 1
        iB++;
    }

    return fourBitsArr;
}
//
// Created by Idan Hauser on 21/05/2020.
//

#include "SaveToFile.h"

void saveListToBinFile(char *file_name, boardPosArray *pos_arr) {
    FILE *oFp = fopen(file_name, "wb");
    checkMemoryAllocation(oFp);
}

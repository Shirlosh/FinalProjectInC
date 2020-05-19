//
// Created by Idan Hauser on 20/05/2020.
//

#ifndef FINALPROJCT_TREEPATH_H
#define FINALPROJCT_TREEPATH_H


#include "Functions.h"

struct treeNodeListCell;

typedef struct _treeNode {
    boardPos position;
    struct treeNodeListCell *next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {

    treeNode *node;
    struct _treeNodeListCell *next;
} treeNodeListCell;


typedef struct _pathTree {
    treeNode *head;
} pathTree;


treeNode *BuildTree(boardPos pos, boardPosArray **posArr);
pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board);
bool isloop(boardPos pos);



#endif //FINALPROJCT_TREEPATH_H

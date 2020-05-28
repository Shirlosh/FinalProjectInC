//
// Created by Shirly on 20/05/2020.
//

#include "TreePath.h"

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {


    boardPosArray **arrayWithValidPositions;
    boardPos *branch;
    pathTree Tree;

    arrayWithValidPositions = validMoves(moves, board);

    branch = (boardPos*)malloc(sizeof(boardPos));
    checkMemoryAllocation(branch);

    Tree.head = BuildTree(start, arrayWithValidPositions,branch,1);
    return Tree;

}

treeNode *BuildTree(boardPos pos, boardPosArray **posArr) {

    treeNodeListCell *next;
    treeNode *newNode;
    int size,row, col;

    row = convertRowToLetter(pos[0]);
    col = convertChToInt(pos[1]);  // convert pos to ROW and COL
    size = posArr[row][col].size; // utilize the size

    if (posArr[row][col].size == 0)
        return NULL;


    if (!isloop(pos)) {

        newNode = (treeNode*)malloc(sizeof(treeNode));
        checkMemoryAllocation(newNode);

        newNode->position[0] = pos[0];
        newNode->position[1] = pos[1];

        next = newNode->next_possible_positions;

        for (int i = 0; i < size; i++) {

            next->node = BuildTree((**posArr).positions[i], posArr);
            next = next->next;

        }

        return newNode;
    }

}


bool isloop(boardPos pos) {

    return true;
}

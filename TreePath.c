//
// Created by Shirly on 20/05/2020.
//

#include "TreePath.h"


pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {

    boardPosArray **pArr;
    boardPos *branch = NULL;
    pathTree Tree;

    pArr = validMoves(moves, board);

    Tree.head = BuildTree(start, pArr, branch, 0);
    return Tree;

}


///returns the head of the treepath,
///next possible position is a list of leaf , the last leaf in the leaf point to NULL
treeNode *BuildTree(boardPos pos, boardPosArray **posArr, boardPos *branch, unsigned int branchSize) {

    treeNodeListCell *next;
    treeNode *newNode;
    boardPos *newBranch;
    int size, ROW, COL;
    // convert pos to ROW and COL
    ROW = convertLetterToRow (pos[0]);
    COL = (int) (pos[1]);
    // utilize the size
    size = posArr[ROW][COL].size;
// base case only leaf
    if (size == 0) {
        newNode = CreateNewTreeNode(pos, 0);
        return newNode;
    }

    newBranch = branchDuplicate(branch, &branchSize, pos);
    // if there is no loops, create the root and build the tree
    if (isLoop(newBranch, branchSize) == false) {

        newNode = CreateNewTreeNode(pos, size);
        next = newNode->next_possible_positions;
        // build the list
        for (int i = 0; i < size; i++) {
            //the next position
            pos = posArr[ROW][COL].positions[i];
            next->node = BuildTree(pos, posArr, newBranch, branchSize);
            // if the node is null utilize other node in it else - go to the next list node
            if (newNode->next_possible_positions->node != NULL) {
                next->next = (treeNodeListCell *) malloc(sizeof(treeNodeListCell));
                checkMemoryAllocation(next->next);
                next = next->next;
            }
        }

        free(newBranch);
        return newNode;
    }

    free(newBranch);
}

///dupelicate the branch and insert the next new position
/// returns the new branch
boardPos *branchDuplicate(boardPos *oldBranch, int *branchSize, boardPos pos) {

    boardPos *newBranch;
    int i;

    newBranch = (boardPos *) malloc(((*branchSize) + 1) * sizeof(boardPos));
    checkMemoryAllocation(newBranch);

    for (i = 0; i < *branchSize; i++) { // copy the old position

        newBranch[i][0] = oldBranch[i][0];
        newBranch[i][1] = oldBranch[i][1];

    }

    newBranch[*branchSize][0] = pos[0];//new position
    newBranch[*branchSize][1] = pos[1];
    (*branchSize)++;

    return newBranch;

}


bool isLoop(boardPos *branch, unsigned int size) {

    for (int i = 0; i < size - 1; i++) { // goes through the array

        if ((branch[i][0] == branch[size - 1][0]) && (branch[i][1] == branch[size - 1][1]))
            return true;
    }

    return false;
}

/// create new treenode
/// assign the position list with the inserted size
/// if size is 0 treenodelistCell points to NULL
treeNode *CreateNewTreeNode(boardPos pos, unsigned int listCellSize) {
    treeNode *newNode;

    newNode = (treeNode *) malloc(sizeof(treeNode));
    checkMemoryAllocation(newNode);

    newNode->position[0] = pos[0]; // insert the position
    newNode->position[1] = pos[1];

    if (listCellSize == 0) // if there is no childs , possible positions is an empty list
        newNode->next_possible_positions = NULL;


    else {

        newNode->next_possible_positions = (treeNodeListCell *) malloc(
                sizeof(treeNodeListCell)); // allocate the possible position list
        checkMemoryAllocation(newNode->next_possible_positions);
    }

    return newNode;

}

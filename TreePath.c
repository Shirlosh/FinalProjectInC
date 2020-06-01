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


///returns the head of the treepath,
///next possible position is a list of leaf , the last leaf in the leaf point to NULL
treeNode *BuildTree(boardPos pos, boardPosArray **posArr,boardPos *branch,int branchSize) {

    treeNodeListCell *next,*start;
    treeNode *newNode;
    int size, ROW, COL,logicalSize=0;

    ROW = convertLetterToRow (pos[0]);
    COL = (int)(pos[1]);  // convert pos to ROW and COL
    size =(int) posArr[ROW][COL].size; // utilize the size


    if (size == 0) { // base case only leaf
        newNode = CreateNewTreeNode(pos, 0);
        free(branch);
        return newNode;
    }

    branch = (boardPos*)realloc(branch, branchSize * sizeof(boardPos));// creation of the branch array
    branch[branchSize - 1][0] = pos[0];
    branch[branchSize - 1][1] = pos[1];

    if (!isloop(pos, branch,branchSize)) { // if there is no loops, create the root and build the tree

        newNode = CreateNewTreeNode(pos,size);
        next = (treeNodeListCell *) newNode->next_possible_positions;


        for (int i = 0; i < size; i++) {
            pos = posArr[ROW][COL].positions[i];
            next->node = BuildTree(pos, posArr, branch,branchSize+1);

            if (next->node != NULL) { // if the node is null rebuild it else moveon the list
                next = next->next;
                logicalSize++;
            }

        }
        start = (treeNodeListCell *) newNode->next_possible_positions;
        reSizeTreelist(&newNode, logicalSize);
        return newNode;
    }


    return NULL;

}


///recompute the list size to the phisical size
/// adds null to the end of the list
void reSizeTreelist(treeNode **node, int logicalSize) {
    treeNodeListCell *lastCell;

    if (logicalSize == 0) { // free the empty list and point to null

        free((*node)->next_possible_positions);
        (*node)->next_possible_positions = NULL;
    }

    else {

        (node) = (treeNode **) (treeNode *) realloc((*node), (logicalSize + 1) * sizeof(boardPos)); // addition of one spot to nullptr
        checkMemoryAllocation(node);
        lastCell = (treeNodeListCell *) (*node)->next_possible_positions;

        for (int i = 0; i < logicalSize; i++) lastCell = lastCell->next;

        lastCell = NULL;
    }

}




bool isloop(boardPos pos,boardPos *branch,int size) {
    int i = 0;

    while (i < size - 2) { // goes through the array not without the last cell

        if (branch[i] == pos)
            return true;

        i++;
    }

    return false;
}

/// create new treenode
/// assign the position list with the inserted size
/// if size is 0 treenodelistCell points to NULL
treeNode *CreateNewTreeNode(boardPos pos,int listCellSize) {
    treeNode *newNode;

    newNode = (treeNode*)malloc(sizeof(treeNode));
    checkMemoryAllocation(newNode);

    newNode->position[0] = pos[0];
    newNode->position[1] = pos[1];

    if (listCellSize == 0) // if there is no childs , possible positions is an empty list
        newNode->next_possible_positions = NULL;


    else {

        newNode->next_possible_positions = (struct treeNodeListCell *) (treeNodeListCell *) malloc(
                listCellSize * sizeof(treeNodeListCell));
        checkMemoryAllocation(newNode->next_possible_positions);
    }

    return newNode;

}

/*
void printTree(pathTree tr) {

    if (tr.head=!NULL)
        printTreeRec(tr.head);

}*/
/*
void printTreeRec(treeNode *node) {
    treeNodeListCell *list;
    list = node->next_possible_positions;

    printf("%d ", node->position);

    while (list != NULL) {
        printTreeRec(list->node);
        list = list->next;
    }

}*/

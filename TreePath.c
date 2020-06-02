//
// Created by Shirly on 20/05/2020.
//

#include "TreePath.h"

pathTree findAllPossiblePaths(boardPos start, movesArray **moves, char **board) {

    boardPosArray **pArr;
    boardPos *branch=NULL;
    pathTree Tree;

    pArr = validMoves(moves, board);

    Tree.head = BuildTree(start, pArr,branch,0);
    return Tree;

}


///returns the head of the treepath,
///next possible position is a list of leaf , the last leaf in the leaf point to NULL
treeNode *BuildTree(boardPos pos, boardPosArray **posArr,boardPos *branch, unsigned int branchSize) {

    treeNodeListCell *next;
    treeNode *newNode;
    boardPos *newBranch;
    int size, ROW, COL,logicalSize=0;

    ROW = convertLetterToRow (pos[0]);
    COL = (int)(pos[1]);  // convert pos to ROW and COL
    size = posArr[ROW][COL].size; // utilize the size


    if (size == 0) { // base case only leaf
        newNode = CreateNewTreeNode(pos, 0);
        return newNode;
    }

    newBranch = branchDuplicate(branch, &branchSize, pos);

    if (!isloop(newBranch,branchSize)) { // if there is no loops, create the root and build the tree

        newNode = CreateNewTreeNode(pos, size);
        next = newNode->next_possible_positions;

        for (int i = 0; i < size; i++) { // build the list

            pos = posArr[ROW][COL].positions[i];//next position
            newNode->next_possible_positions->node = BuildTree(pos, posArr, newBranch,branchSize);

       //     if (i + 1 == size) next->next = NULL;// the end of the list is null

            if (newNode->next_possible_positions->node != NULL) { // if the node is null utilize other node in it else - go to the next list node

                next = next->next;
                logicalSize++;/// add 1 in the end or not? maybe else
            }

        }

        reSizeTreelist(&newNode, logicalSize,size);
        free(newBranch);
        return newNode;
    }

    free(newBranch);
    return NULL;

}


///recompute the list size to the phisical size
/// adds null to the end of the list
void reSizeTreelist(treeNode **node, unsigned int logicalSize, unsigned int physicalSize) {

    if (logicalSize == 0) { // free the empty list and point to null
        free((*node)->next_possible_positions);
        (*node)->next_possible_positions = NULL;
    }

    if (physicalSize > logicalSize) {
        (*node) = (treeNode*)realloc((*node), (logicalSize) * sizeof(treeNode)); // recompute the list size
        checkMemoryAllocation(node);

    }
}


boardPos *branchDuplicate(boardPos*oldBranch,int *branchSize, boardPos pos) {

    boardPos *newBranch;
    int i;

    newBranch = (boardPos*)malloc((*branchSize)+1 * sizeof(boardPos)); // *2? or biggest size
    checkMemoryAllocation(newBranch);

    for (i = 0; i < *branchSize; i++) {

        newBranch[i][0] = oldBranch[i][0];
        newBranch[i][1] = oldBranch[i][1];

    }

    newBranch[*branchSize][0] = pos[0];
    newBranch[*branchSize][1] = pos[1];
    (*branchSize)++;

    return newBranch;

}


bool isloop(boardPos *branch, unsigned int size) {

    for (int i = 0; i < size - 1;i++) { // goes through the array

        if (branch[i][0] == branch[size - 1][0] && branch[i][1] == branch[size - 1][1])
            return true;

    }

    return false;
}

/// create new treenode
/// assign the position list with the inserted size
/// if size is 0 treenodelistCell points to NULL
treeNode *CreateNewTreeNode(boardPos pos, unsigned int listCellSize) {
    treeNode *newNode;

    newNode = (treeNode*)malloc(sizeof(treeNode));
    checkMemoryAllocation(newNode);

    newNode->position[0] = pos[0];
    newNode->position[1] = pos[1];

    if (listCellSize == 0) // if there is no childs , possible positions is an empty list
        newNode->next_possible_positions = NULL;


    else {

        newNode->next_possible_positions = (treeNodeListCell*)malloc(listCellSize * sizeof(treeNodeListCell));
        checkMemoryAllocation(newNode->next_possible_positions);
    }

    return newNode;

}

/*
void printTree(pathTree tr) {

	if (tr.head=!NULL)
		printTreeRec(tr.head);

}

void printTreeRec(treeNode *node) {
	treeNodeListCell *list;
	list = node->next_possible_positions;

	if (node == NULL)
		return;

	printf("%d ", node->position );


	while (list != NULL) {
		printTreeRec(list->node);
		list = list->next;
	}

}*/
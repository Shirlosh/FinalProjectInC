#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "stdbool.h"
#include "stdlib.h"
#include "Functions.h"
#include "InputData.h"
#include "TreePath.h"


int main() {
	boardPos positions[] = { "A1","A2","G3","F1","E5"}; ///ex5
	boardPosArray pos_arr = { 5,positions };///ex5
	//boardPosArray **arrayWithValidPositions = NULL;
	boardPos start = {'A',2};///ex4
	movesArray **moves = NULL;///all
	char **board = NULL;///all
	movesList *movesList = NULL;///ex2
	int res;

	board = getCharBoard();
	moves = getMovesArray();
	//movesList = getMoveList();

	//arrayWithValidPositions = validMoves(moves, board);///ex1
	//display(movesList, start, board);///ex2
	//findAllPossiblePaths(start, moves, board);///ex3
	//movesList = findPathCoveringAllBoard(start, moves, board);///ex4
	saveListToBinFile("testBin.bin", &pos_arr);///ex5
	res = checkAndDisplayPathFromFile("testBin.bin", moves, board);

	//freeMoveList(movesList);
	//freeGameBord(board);
	//freeMovmentArray(moves);

}

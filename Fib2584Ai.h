#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include "Fib2584/Typedefs.h"
#include "table/Fib2584Table.h"
#include "Fib2584/TreeSearch.h"

class Fib2584Ai
{
public:
	Fib2584Ai();
	~Fib2584Ai();;
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(int board[4][4], int moveCount = 0);
	int generateEvilMove(int board[4][4], int moveCount);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);
	// tree search one move
	MoveDirection treeSearchMove(int board[4][4], int depth);
	
	void addChildMove(int (&board)[4][4], TreeSearch& TS, int depth);
	void addChildEvil(int (&board)[4][4], TreeSearch& TS, int depth);
	
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
	// board functions
	void show(int board[4][4]);
	bool check(int boardA[4][4], int boardB[4][4]);
	int shift(int &a, int &b);
	double Move(int board[4][4], int direction);
	void Tail(int board[4][4], int position);
	double evaluation(int board[4][4], bool type, int state);
	// train functions
	double trainInit(int board[4][4]);
	double trainMove(int board[4][4]);
	double trainTail(int board[4][4]);
	void trainValue(Fib2584Stack& Play, Fib2584Stack& Evil);
	void adjustValue(int board[4][4], double reward, bool type, int state);
	// index functions
	int computeIndex(int a, int b, int c, int d);
	void computeIndexAll(int board[4][4], int outputIndex[8]);
	void FtoN_board(int board[4][4]);
	void NtoF_board(int board[4][4]);
	// test functions
	MoveDirection randomMove(int board[4][4]);
	int randomEvilMove(int board[4][4]);
	
private:
	int M;
	int NtoF[20];
	int FtoN[6766];
	Fib2584Table play_edge[5];
	Fib2584Table evil_edge[5];
	Fib2584Table play_center[5];
	Fib2584Table evil_center[5];
	Fib2584Stack stackPlay;
	Fib2584Stack stackEvil;
	TreeSearch playTree;
	TreeSearch evilTree;
};

#endif
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include "../Fib2584/GameBoard.h"
#include "../Fib2584/Typedefs.h"
#include "../Fib2584/Statistic.h"
#include "../Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cerr << "usage: train rounds" << endl;
		return 1;
	}
	else if(argc >= 4) {
		if (strcmp(argv[1],"init_table") != 0) {
			cerr << "usage: train rounds" << endl;
			return 1;
		}
		else {
			int i=2, tableSize;
			string tableName;
			while (i<argc) {
				tableName = argv[i];
				tableSize = atoi(argv[i+1]);
				Fib2584Table table_0;
				table_0.initialize_0(tableName, tableSize);
				i += 2;
			}
			cout << "initial table done!" << endl;
			return 1;
		}
	}
	int iPlayRounds = atoi(argv[1]);
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);
	double score = 0;

	// play each round
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		gameBoard.getArrayBoard(arrayBoard);
		
		score += ai.trainInit(arrayBoard);
		if ((i+1)%10==0) {
			cout << "No." << i+1 << " complete" << endl;
			cout << "Average score: " << score/10 << endl;
			score = 0;
		}
	}
	
	return 0;
}

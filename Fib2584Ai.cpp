#include "Fib2584Ai.h"
#include <iomanip>
#include <iostream>
#include <cfloat>

#define alpha 0.0002		// alpha
#define lambda 0.2		// lambda
#define maxDepth 3

Fib2584Ai::Fib2584Ai()
{
	srand(time(NULL));
	M = 0;
	NtoF[0]=0;		NtoF[1]=1;		NtoF[2]=2;		NtoF[3]=3;
	NtoF[4]=5;		NtoF[5]=8;		NtoF[6]=13;		NtoF[7]=21;
	NtoF[8]=34;		NtoF[9]=55;		NtoF[10]=89;	NtoF[11]=144;
	NtoF[12]=233;	NtoF[13]=377;	NtoF[14]=610;	NtoF[15]=987;
	NtoF[16]=1597;	NtoF[17]=2584;	NtoF[18]=4181;	NtoF[19]=6765;
	FtoN[0]=0;		FtoN[1]=1;		FtoN[2]=2;		FtoN[3]=3;
	FtoN[5]=4;		FtoN[8]=5;		FtoN[13]=6;		FtoN[21]=7;
	FtoN[34]=8;		FtoN[55]=9;		FtoN[89]=10;	FtoN[144]=11;
	FtoN[233]=12;	FtoN[377]=13;	FtoN[610]=14;	FtoN[987]=15;
	FtoN[1597]=16;	FtoN[2584]=17;	FtoN[4181]=18;	FtoN[6765]=19;
	play_edge[0].initialize_table("table/play_edge_1", 4);
	play_edge[1].initialize_table("table/play_edge_2", 4);
	play_edge[2].initialize_table("table/play_edge_3", 4);
	play_edge[3].initialize_table("table/play_edge_4", 4);
	play_edge[4].initialize_table("table/play_edge_5", 4);
	evil_edge[0].initialize_table("table/evil_edge_1", 4);
	evil_edge[1].initialize_table("table/evil_edge_2", 4);
	evil_edge[2].initialize_table("table/evil_edge_3", 4);
	evil_edge[3].initialize_table("table/evil_edge_4", 4);
	evil_edge[4].initialize_table("table/evil_edge_5", 4);
	play_center[0].initialize_table("table/play_center_1", 4);
	play_center[1].initialize_table("table/play_center_2", 4);
	play_center[2].initialize_table("table/play_center_3", 4);
	play_center[3].initialize_table("table/play_center_4", 4);
	play_center[4].initialize_table("table/play_center_5", 4);
	evil_center[0].initialize_table("table/evil_center_1", 4);
	evil_center[1].initialize_table("table/evil_center_2", 4);
	evil_center[2].initialize_table("table/evil_center_3", 4);
	evil_center[3].initialize_table("table/evil_center_4", 4);
	evil_center[4].initialize_table("table/evil_center_5", 4);
	cout << "input table done!" << endl;
}

Fib2584Ai::~Fib2584Ai()
{
	play_edge[0].update();
	play_edge[1].update();
	play_edge[2].update();
	play_edge[3].update();
	play_edge[4].update();
	play_center[0].update();
	play_center[1].update();
	play_center[2].update();
	play_center[3].update();
	play_center[4].update();
	evil_edge[0].update();
	evil_edge[1].update();
	evil_edge[2].update();
	evil_edge[3].update();
	evil_edge[4].update();
	evil_center[0].update();
	evil_center[1].update();
	evil_center[2].update();
	evil_center[3].update();
	evil_center[4].update();
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	return;
}

MoveDirection Fib2584Ai::generateMove( int board[4][4], int moveCount /*= 0*/ )
{
	// MoveDirection Move = static_cast<MoveDirection>(rand() % 4);
	double up,down,left,right;
	int direction, zeroNumber=0;
	MoveDirection moveDir;
	int newBoard[4][4];
	for (int i=0; i<16; i++) if (board[i/4][i%4] == 0) zeroNumber++;
	if (zeroNumber < 6) {
		moveDir = treeSearchMove(board,0);
	}
	else {
		for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
		up = (double) Move(newBoard,0);
		up += evaluation(newBoard,1,M);
		for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
		down = (double) Move(newBoard,1);
		down += evaluation(newBoard,1,M);
		for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
		left = (double) Move(newBoard,2);
		left += evaluation(newBoard,1,M);
		for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
		right = (double) Move(newBoard,3);
		right += evaluation(newBoard,1,M);
		if (up > down) {
			if (left > right) {
				if (up > left) direction = 0;
				else direction = 2;
			}
			else {
				if (up > right) direction = 0;
				else direction = 3;
			}
		}
		else {
			if (left > right) {
				if (down > left) direction = 1;
				else direction = 2;
			}
			else {
				if (down > right) direction = 1;
				else direction = 3;
			}
		}
		if (up < -99999 && down < -99999 && left < -99999 && right < -99999) direction = 4;
		moveDir = static_cast<MoveDirection>(direction);
	}
	return moveDir;
}

int Fib2584Ai::generateEvilMove(int board[4][4], int moveCount)
{
	double minim = 9999999;
	int position = -1, tempPosition;
	int newBoard[4][4];
	bool never;
	while (1) {
		never = true;
		for (int i=0; i<16; i++) {
			if (board[i/4][i%4]==0 && never) { //return rand() % 16;
				never = false;
				if (M%5==2 || M%5==0) {
					newBoard[i/4][i%4] = 3;
				}
				else newBoard[i/4][i%4] = 1;
				board[i/4][i%4] = -1;
				tempPosition = i;
			}
			else newBoard[i/4][i%4] = board[i/4][i%4];
		}
		if (check(newBoard,board)) break;
		for (int i=0; i<16; i++) if (newBoard[i/4][i%4]==-1) newBoard[i/4][i%4] = 0;
		if (evaluation(newBoard,0,M) <= minim) {
			minim = evaluation(newBoard,0,M);
			position = tempPosition;
		}
	}
	for (int i=0; i<16; i++) if (board[i/4][i%4]==-1) board[i/4][i%4] = 0;
    return position;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

MoveDirection Fib2584Ai::treeSearchMove(int board[4][4], int depth)
{
	TreeSearch TS;
	TS.initRoot(0);
	int newBoard[4][4];
	for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
	addChildMove(newBoard, TS, depth);
	//show(board);
	int direction = TS.searchAllMax();
	for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
	double a = Move(newBoard,direction);
	if (check(board,newBoard)) {
		direction = (rand() % 4);
	}
	MoveDirection moveDir = static_cast<MoveDirection>(direction);
	return moveDir;
}

void Fib2584Ai::addChildMove(int (&board)[4][4], TreeSearch& TS, int depth)
{
	int newBoard[4][4];
	double temp;
	for (int i=0; i<4; i++) {
		for (int j=0; j<16; j++) newBoard[j/4][j%4] = board[j/4][j%4];
		temp = Move(newBoard,i);
		if (depth == maxDepth) {
			temp = evaluation(newBoard, 1, M+depth);
		}
		if (temp != DBL_MIN) {
			TS.addChild(temp);
			if (depth < maxDepth) {
				TS.moveToChild();
				while (!TS.noSibling()) {
					TS.moveToRSibling();
				}
				addChildEvil(newBoard, TS, depth);
				TS.moveToParent();
			}
		}
	}
}

void Fib2584Ai::addChildEvil(int (&board)[4][4], TreeSearch& TS, int depth)
{
	int newBoard[4][4];
	for (int i=0; i<16; i++) {
		for (int j=0; j<16; j++) newBoard[j/4][j%4] = board[j/4][j%4];
		if (newBoard[i/4][i%4] == 0) {
			Tail(newBoard, i);
			M -= 1;
			TS.addChild(0);
			TS.moveToChild();
			while (!TS.noSibling()) {
				TS.moveToRSibling();
			}
			addChildMove(newBoard, TS, depth+1);
			TS.moveToParent();
		}
	}
}

/**********************************
You can implement any additional functions
you may need.
**********************************/

// board functions
void Fib2584Ai::show(int board[4][4])
{
	for(int i=0; i<16; i++) {
		cout << setw(4) << board[i/4][i%4] << " ";
		if (i%4 == 3) cout << endl;
	}
}

bool Fib2584Ai::check(int boardA[4][4], int boardB[4][4])
{
	bool same = true;
	for (int i=0; i<16; i++) {
		if (boardA[i/4][i%4] != boardB[i/4][i%4]) same = false;
	}
	return same;
}

int Fib2584Ai::shift(int &a, int &b)
{
	if (a<0 || b<0) {
		return 0;
	}
	if (a==0) {
		if (b==0) return 0;
		else {
			a = b;
			b = 0;
		}
	}
	else if (a==1) {
		if (b==0) return 0;
		else if (b==1 || b==2) {
			a = -(b+1);
			b = 0;
			return -a;
		}
	}
	else {
		if (a==b+1) {
			a = -(b+2);
			b = 0;
			return -a;
		}
		else if (a==b-1) {
			a = -(b+1);
			b = 0;
			return -a;
		}
	}
	return 0;
}

// 0:up  1:down  2:left  3:right
double Fib2584Ai::Move(int board[4][4], int direction)
{
	double s = 0;
	int saveBoard[4][4];
	for (int i=0; i<16; i++) saveBoard[i/4][i%4] = board[i/4][i%4];
	if (direction==0) {
		for (int i=0; i<4; i++) {
			s += NtoF[shift(board[0][i],board[1][i])];
			s += NtoF[shift(board[1][i],board[2][i])];
			s += NtoF[shift(board[0][i],board[1][i])];
			s += NtoF[shift(board[2][i],board[3][i])];
			s += NtoF[shift(board[1][i],board[2][i])];
			s += NtoF[shift(board[0][i],board[1][i])];
		}
	}
	else if (direction==1) {
		for (int i=0; i<4; i++) {
			s += NtoF[shift(board[3][i],board[2][i])];
			s += NtoF[shift(board[2][i],board[1][i])];
			s += NtoF[shift(board[3][i],board[2][i])];
			s += NtoF[shift(board[1][i],board[0][i])];
			s += NtoF[shift(board[2][i],board[1][i])];
			s += NtoF[shift(board[3][i],board[2][i])];
		}
	}
	else if (direction==2) {
		for (int i=0; i<4; i++) {
			s += NtoF[shift(board[i][0],board[i][1])];
			s += NtoF[shift(board[i][1],board[i][2])];
			s += NtoF[shift(board[i][0],board[i][1])];
			s += NtoF[shift(board[i][2],board[i][3])];
			s += NtoF[shift(board[i][1],board[i][2])];
			s += NtoF[shift(board[i][0],board[i][1])];
		}
	}
	else if (direction==3) {
		for (int i=0; i<4; i++) {
			s += NtoF[shift(board[i][3],board[i][2])];
			s += NtoF[shift(board[i][2],board[i][1])];
			s += NtoF[shift(board[i][3],board[i][2])];
			s += NtoF[shift(board[i][1],board[i][0])];
			s += NtoF[shift(board[i][2],board[i][1])];
			s += NtoF[shift(board[i][3],board[i][2])];
		}
	}
	for (int i=0; i<16; i++) {
		if (board[i/4][i%4]<0) board[i/4][i%4] = -(board[i/4][i%4]);
	}
	if (check(saveBoard,board)) return DBL_MIN;
	return s;
}

void Fib2584Ai::Tail(int board[4][4], int position)
{
	if (board[position/4][position%4] != 0) return;
	if (M%5 == 1 || M%5 == 4) {
		board[position/4][position%4] = 3;
	}
	else {
		board[position/4][position%4] = 1;
	}
	M += 1;
}

double Fib2584Ai::evaluation(int board[4][4], bool type, int state)
{
	double e = 0;
	int index[8];
	computeIndexAll(board, index);
	if (type) {
		switch(state%5) {
			case 1:
				for (int i=0; i<4; i++) {
					e += play_edge[0].table[index[i]];
					e += play_center[0].table[index[i+4]];
				}
				break;
			case 2:
				for (int i=0; i<4; i++) {
					e += play_edge[1].table[index[i]];
					e += play_center[1].table[index[i+4]];
				}
				break;
			case 3:
				for (int i=0; i<4; i++) {
					e += play_edge[2].table[index[i]];
					e += play_center[2].table[index[i+4]];
				}
				break;
			case 4:
				for (int i=0; i<4; i++) {
					e += play_edge[3].table[index[i]];
					e += play_center[3].table[index[i+4]];
				}
				break;
			case 0:
				for (int i=0; i<4; i++) {
					e += play_edge[4].table[index[i]];
					e += play_center[4].table[index[i+4]];
				}
		}
	}
	else {
		switch(state%5) {
			case 1:
				for (int i=0; i<4; i++) {
					e += evil_edge[0].table[index[i]];
					e += evil_center[0].table[index[i+4]];
				}
				break;
			case 2:
				for (int i=0; i<4; i++) {
					e += evil_edge[1].table[index[i]];
					e += evil_center[1].table[index[i+4]];
				}
				break;
			case 3:
				for (int i=0; i<4; i++) {
					e += evil_edge[2].table[index[i]];
					e += evil_center[2].table[index[i+4]];
				}
				break;
			case 4:
				for (int i=0; i<4; i++) {
					e += evil_edge[3].table[index[i]];
					e += evil_center[3].table[index[i+4]];
				}
				break;
			case 0:
				for (int i=0; i<4; i++) {
					e += evil_edge[4].table[index[i]];
					e += evil_center[4].table[index[i+4]];
				}
		}
	}
	return e;
}

// train functions
double Fib2584Ai::trainInit(int board[4][4])
{
	double totalScore;
	FtoN_board(board);
	totalScore = trainMove(board);
	trainValue(stackPlay, stackEvil);
	//cout << "Total Score: " << totalScore << endl;
	return totalScore;
}

double Fib2584Ai::trainMove(int board[4][4])
{
	// show(board);
	MoveDirection movedir;
	double s;
	movedir = generateMove(board, 0);	// decide direction to move
	//movedir = randomMove(board);
	//movedir = treeSearchMove(board);
	if (movedir == MOVE_UP) {
		s = (double) Move(board, 0);
	}
	else if (movedir == MOVE_DOWN) {
		s = (double) Move(board, 1);
	}
	else if (movedir == MOVE_LEFT) {
		s = (double) Move(board, 2);
	}
	else if (movedir == MOVE_RIGHT) {
		s = (double) Move(board, 3);
	}
	else {
		stackPlay.push(board, 0);
		return 0;
	}
	stackPlay.push(board, s);
	//show(board);
	s += trainTail(board);	// call Tail
	return s;
}

double Fib2584Ai::trainTail(int board[4][4])
{
	// show(board);
	double s;
	int position;
	int saveBoard[4][4];
	position = generateEvilMove(board, 0);	// decide position to add tail
	//position = randomEvilMove(board);
	if (position == -1) return 0;
	Tail(board, position);
	for (int i=0; i<16; i++) saveBoard[i/4][i%4] = board[i/4][i%4];
	s = trainMove(board);	// call Move
	stackEvil.push(saveBoard, s);
	return s;
}

void Fib2584Ai::trainValue(Fib2584Stack& Play, Fib2584Stack& Evil)
{
	Fib2584Stack Temp;
	int PlaySize = Play.s();
	double rewardSum = 0, rewardCenter = 0;
	for (int i=PlaySize; i>1; i--) {
		if (i == PlaySize) {
			rewardSum += evaluation(Play.topBoard(), 1, Play.s());
			rewardSum += Play.topReward();
			rewardSum -= evaluation(Play.nextBoard(), 1, Play.s()-1);
		}
		else {
			rewardSum += evaluation(Play.topBoard(), 1, Play.s());
			rewardSum += Play.topReward();
			for (int j=PlaySize; j>=i; j--) {
				rewardSum *= lambda;
				rewardCenter *= lambda;
				Temp.push(Play.topBoard(), Play.topReward());
				Play.pop();
				rewardSum += Play.topReward();
				rewardCenter += evaluation(Play.topBoard(), 1, Play.s());
			}
			rewardSum += (rewardCenter * (1-lambda));
			rewardSum -= evaluation(Play.nextBoard(), 1, Play.s()-1);
		}
		adjustValue(Play.nextBoard(), rewardSum*alpha, 1, Play.s()-1);
		while (!Temp.empty()) {
			Play.push(Temp.topBoard(), Temp.topReward());
			Temp.pop();
		}
		rewardSum = 0;
		rewardCenter = 0;
	}
	
	int EvilSize = Evil.s();
	while (!Evil.empty()) {
		Temp.push(Evil.topBoard(), Evil.topReward());
		Evil.pop();
	}
	for (int i=EvilSize; i>1; i--) {
		if (i == EvilSize) {
			rewardSum += evaluation(Temp.topBoard(), 0, Temp.s());
			rewardSum += Temp.topReward();
			rewardSum -= evaluation(Temp.nextBoard(), 0, Temp.s()-1);
		}
		else {
			rewardSum += evaluation(Temp.topBoard(), 0, Temp.s());
			rewardSum += Temp.topReward();
			for (int j=EvilSize; j>=i; j--) {
				rewardSum *= lambda;
				rewardCenter *= lambda;
				Evil.push(Temp.topBoard(), Temp.topReward());
				Temp.pop();
				rewardSum += (Temp.topReward() - Evil.topReward());
				rewardCenter += evaluation(Temp.topBoard(), 0, Temp.s());
			}
			rewardSum += (rewardCenter * (1-lambda));
			rewardSum -= evaluation(Temp.nextBoard(), 0, Temp.s()-1);
		}
		adjustValue(Temp.nextBoard(), rewardSum*alpha, 0, Temp.s()-1);
		while (!Evil.empty()) {
			Temp.push(Evil.topBoard(), Evil.topReward());
			Evil.pop();
		}
		rewardSum = 0;
		rewardCenter = 0;
	}
	while (!Play.empty()) Play.pop();
	while (!Evil.empty()) Evil.pop();
	while (!Temp.empty()) Temp.pop();	
	return;
}

void Fib2584Ai::adjustValue(int board[4][4], double reward, bool type, int state)
{
	int index[8];
	computeIndexAll(board, index);
	if (type) {		// play table
		switch(state%5) {
			case 1:
				for (int i=0; i<4; i++) {
					play_edge[0].table[index[i]] += reward;
					play_center[0].table[index[i+4]] += reward;
				}
				break;
			case 2:
				for (int i=0; i<4; i++) {
					play_edge[1].table[index[i]] += reward;
					play_center[1].table[index[i+4]] += reward;
				}
				break;
			case 3:
				for (int i=0; i<4; i++) {
					play_edge[2].table[index[i]] += reward;
					play_center[2].table[index[i+4]] += reward;
				}
				break;
			case 4:
				for (int i=0; i<4; i++) {
					play_edge[3].table[index[i]] += reward;
					play_center[3].table[index[i+4]] += reward;
				}
				break;
			case 0:
				for (int i=0; i<4; i++) {
					play_edge[4].table[index[i]] += reward;
					play_center[4].table[index[i+4]] += reward;
				}
				break;
		}
	}
	else {
		switch(state%5) {
			case 1:
				for (int i=0; i<4; i++) {
					evil_edge[0].table[index[i]] += reward;
					evil_center[0].table[index[i+4]] += reward;
				}
				break;
			case 2:
				for (int i=0; i<4; i++) {
					evil_edge[1].table[index[i]] += reward;
					evil_center[1].table[index[i+4]] += reward;
				}
				break;
			case 3:
				for (int i=0; i<4; i++) {
					evil_edge[2].table[index[i]] += reward;
					evil_center[2].table[index[i+4]] += reward;
				}
				break;
			case 4:
				for (int i=0; i<4; i++) {
					evil_edge[3].table[index[i]] += reward;
					evil_center[3].table[index[i+4]] += reward;
				}
				break;
			case 0:
				for (int i=0; i<4; i++) {
					evil_edge[4].table[index[i]] += reward;
					evil_center[4].table[index[i+4]] += reward;
				}
				break;
		}
	}
}

// index functions
int Fib2584Ai::computeIndex(int a, int b, int c, int d)
{
	if (a>=d) return a + b*20 + c*400 + d*8000;
	else return a*8000 + b*400 + c*20 + d;
}

void Fib2584Ai::computeIndexAll(int board[4][4], int outputIndex[8])
{
	outputIndex[0] = computeIndex(board[0][0], board[0][1], board[0][2], board[0][3]);
	outputIndex[4] = computeIndex(board[1][0], board[1][1], board[1][2], board[1][3]);
	outputIndex[5] = computeIndex(board[2][0], board[2][1], board[2][2], board[2][3]);
	outputIndex[1] = computeIndex(board[3][0], board[3][1], board[3][2], board[3][3]);
	outputIndex[2] = computeIndex(board[0][0], board[1][0], board[2][0], board[3][0]);
	outputIndex[6] = computeIndex(board[0][1], board[1][1], board[2][1], board[3][1]);
	outputIndex[7] = computeIndex(board[0][2], board[1][2], board[2][2], board[3][2]);
	outputIndex[3] = computeIndex(board[0][3], board[1][3], board[2][3], board[3][3]);
}

void Fib2584Ai::FtoN_board(int board[4][4])
{
	for (int i=0; i<16; i++) board[i/4][i%4] = FtoN[board[i/4][i%4]];
}

void Fib2584Ai::NtoF_board(int board[4][4])
{
	for (int i=0; i<16; i++) board[i/4][i%4] = NtoF[board[i/4][i%4]];
}

MoveDirection Fib2584Ai::randomMove(int board[4][4])
{
	bool U=1, D=1, L=1, R=1;
	int newBoard[4][4];
	MoveDirection moveDir;
	while (U || D || L || R) {
		for (int i=0; i<16; i++) newBoard[i/4][i%4] = board[i/4][i%4];
		int temp = (rand() % 4);
		Move(newBoard,temp+1);
		if (!check(newBoard,board)) {
			moveDir = static_cast<MoveDirection>(temp);
			return moveDir;
		}
		if (temp==0) U=0;
		else if (temp==1) D=0;
		else if (temp==2) L=0;
		else if (temp==3) R=0;
	}
	moveDir = static_cast<MoveDirection>(4);
	return moveDir;
}

int Fib2584Ai::randomEvilMove(int board[4][4])
{
	bool zero=false;
	for (int i=0; i<16; i++) {
		if (board[i/4][i%4]==0) zero=true;
	}
	if (zero) {
		do {
			int position = (rand() % 16);
			if (board[position/4][position%4]==0) return position;
		} while (1);
	}
	else return -1;
}

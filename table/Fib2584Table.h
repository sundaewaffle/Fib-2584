#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

class Fib2584Table {
public:
	Fib2584Table();
	~Fib2584Table();
	void initialize_0(string name, int size);
	void initialize_table(string name, int size);
	void update();
	double* table;

private:
	string table_name;
	int table_size;
};

class Fib2584Stack
{
public:
	Fib2584Stack() : array(nullptr) { size=0; }
	~Fib2584Stack() {
		while (!empty()) pop();
	}
	
	void push(int board[4][4], double reward);
	void pop();
	int (&topBoard())[4][4] {
		return (array->next)->board;
	}
	int (&nextBoard())[4][4] {
		return ((array->next)->next)->board;
	}
	double topReward() {
		return (array->next)->reward;
	}
	int s() {
		return size;
	}
	
	bool empty() const {
		return array==nullptr;
	}
	
private:
	struct node {
		node(int b[4][4], double r, node* n) {
			for (int i=0; i<16; i++) board[i/4][i%4] = b[i/4][i%4];
			reward = r;
			next = n;
		}
		int board[4][4];
		double reward;
		node* next;
	};
	node* array;
	int size;
};
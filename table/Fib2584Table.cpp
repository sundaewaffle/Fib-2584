#include "Fib2584Table.h"

// table
Fib2584Table::Fib2584Table()
{
}

Fib2584Table::~Fib2584Table()
{
}

void Fib2584Table::initialize_0(string name, int size)
{
	table_name = name;
	table_size = size;
	ofstream ff;
	ff.open(table_name,ios::out | ios::trunc);
	if (size == 1) {
		for (int i=0; i<20; i++) ff << 0 << " ";
	}
	else if (size == 2) {
		for (int i=0; i<400; i++) ff << 0 << " ";
	}
	else if (size == 3) {
		for (int i=0; i<8000; i++) ff << 0 << " ";
	}
	else if (size == 4) {
		for (int i=0; i<160000; i++) ff << 0 << " ";
	}
	else if (size == 5) {
		for (int i=0; i<3200000; i++) ff << 0 << " ";
	}
	else if (size == 6) {
		for (int i=0; i<64000000; i++) ff << 0 << " ";
	}
	ff.close();
}

void Fib2584Table::initialize_table(string name, int size)
{
	table_name = name;
	table_size = size;
	ifstream ff;
	ff.open(table_name,ios::in);
	double temp;
	if (size == 1) {
		table = new double[20];
		for (int i=0; i<20; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	else if (size == 2) {
		table = new double[400];
		for (int i=0; i<400; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	else if (size == 3) {
		table = new double[8000];
		for (int i=0; i<8000; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	else if (size == 4) {
		table = new double[160000];
		for (int i=0; i<160000; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	else if (size == 5) {
		table = new double[3200000];
		for (int i=0; i<3200000; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	else if (size == 6) {
		table = new double[64000000];
		for (int i=0; i<64000000; i++) {
			ff >> temp;
			table[i] = temp;
		}
	}
	ff.close();
}

void Fib2584Table::update()
{
	ofstream ff;
	ff.open(table_name, ios::out | ios::trunc);
	if (table_size == 1) {
		for (int i=0; i<20; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	else if (table_size == 2) {
		for (int i=0; i<400; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	else if (table_size == 3) {
		for (int i=0; i<8000; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	else if (table_size == 4) {
		for (int i=0; i<160000; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	else if (table_size == 5) {
		for (int i=0; i<3200000; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	else if (table_size == 6) {
		for (int i=0; i<64000000; i++) {
			ff << fixed << table[i] << " ";
		}
	}
	ff.close();
}

// stack
void Fib2584Stack::push(int board[4][4], double reward)
{
	if (empty()) {
		array = new node(board, reward, nullptr);
		array->next = array;
	}
	else {
		node* p = array->next;
		array->next = new node(board, reward, nullptr);
		(array->next)->next = p;
	}
	size++;
}

void Fib2584Stack::pop()
{
	if (array == array->next) {
		array = nullptr;
	}
	else {
		node* p = array->next;
		array->next = (array->next)->next;
		delete p;
	}
	size--;
}
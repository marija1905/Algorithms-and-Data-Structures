#ifndef _HashTable_h_
#define _HashTable_h_
#include "DoubleHashing.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;


class HashTable {
	static int** hashtable;
	static unsigned const int p, k, n;
	unsigned int index;
	string name, surname;
	struct Elem {
		string codeSubject;
		Elem* next;
		Elem(string c, Elem* n = nullptr) : codeSubject(c), next(n) {};
	};
	Elem* head = nullptr;
	Elem* Make_New_Node(string c);
	Elem* Add_Node(string c);
	static int** Get_HashTable_Ready();
public:
	HashTable(Elem* h = nullptr) : head(h) {};
	static unsigned int GetK();
	static unsigned int GetP();
	int Get_Hash_Function(int key);
	int* FindKey(int k);
	bool Read_Dat();
	bool Read_From_Console(int k);
	bool Deal_With_Colision(int a, string n, string s);
	bool insertKey(int k, string name, string surname);
	bool deleteKey(int k);
	void clear();
	int keyCount() const;
	int tableSize() const;
	void Print_Subjects(int num) const;
	void Print_List(int k) const;
	double fillRatio();
	friend ostream& operator<<(ostream& out, HashTable& h);
};
struct FindList {
	static FindList* first;
	unsigned int inde;
	string na, su;
	int* h;
	FindList* next;
	FindList(int in, FindList* n = nullptr) : next(n) {};
	static FindList* Make_New_Node(int in);
	static FindList* Add_Node(int in, string n, string s);
};

#endif
#ifndef _HashTableExtern_h_
#define _HashTableExtern_h_
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include<queue>

using namespace std;

class HashTableExtern : public HashTable{
	static unsigned const int b, k, m;
	struct FindList {
		static int height;
		FindList* first;
		FindList* left;
		int** index, fog = 0, ind;
		string** name, **surname;
		FindList* right;
		FindList(FindList* l = nullptr, FindList* r = nullptr, int flag = 0) : left(l), right(r) {};
		struct Elem {
			int index;
			Elem* head;
			Elem* next;
			string codeSubject;
			Elem(string c, Elem* n = nullptr) : codeSubject(c), next(n) {};
		};
	};
	static FindList** header;
	static FindList** Get_Header_Ready();
	FindList::Elem* head;
	FindList::Elem* Make_New_Node(string c, int index);
	FindList::Elem* Add_Node(string c, int index);
	void Set_To_Nullptr(FindList* node);
	FindList* first;
	static FindList* Make_New_Node(int in, string name, string surname);
	FindList* Add_Node(int in, string n, string s, FindList* curr);
	string Convert_To_Binary(int k);
	int If_Leaf(FindList* curr);
	FindList* Delete_Node(FindList**header, int i);
public:
	HashTableExtern(FindList* f = nullptr) : first(f) {};
	bool Read_Dat();
	int tableSize();
	int Get_Hash_Function(int key);
	int KeyCount();
	void clear();
	friend ostream& operator<<(ostream& out, HashTableExtern& h);
};





#endif
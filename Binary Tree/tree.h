#ifndef _tree_h_
#define _tree_h_
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <queue>
#include <cmath>
using namespace std;

class Tree {
	static const int order;
	struct Elem {
		string* arr;
		Elem** next;
		int len = 0;
		int flag = 0;
		Elem* parent;
		Elem* sort();
		int level;
		Elem();
	};
	static int red();
	void deletee();
	Elem* root;
	static int num;
public:
	Tree(Elem* r = nullptr) : root(r) {};
	~Tree() { deletee(); }
	bool Find_Key();
	Elem* get_root() { return root; }
	string Find_K();
	friend Tree& Add_Key(Tree& tree);
	friend ifstream& operator>>(ifstream& f, Tree& tree);
	friend ostream& operator<<(ostream& out, Tree& tree);
};


#endif
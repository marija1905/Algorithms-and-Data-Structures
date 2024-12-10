#include "HashTableExtern.h"

unsigned const int HashTableExtern::k = GetK();
unsigned const int HashTableExtern::b = GetP();
unsigned const int HashTableExtern::m = pow(2, b);
int HashTableExtern::FindList::height = 0;
HashTableExtern::FindList** HashTableExtern::header = Get_Header_Ready();

int HashTableExtern::Get_Hash_Function(int key) {
	return key % m;
}



HashTableExtern::FindList** HashTableExtern::Get_Header_Ready() {
	header = new HashTableExtern::FindList*[m];
	for (int i = 0; i < m; i++) header[i] = nullptr;
	return header;
}

HashTableExtern::FindList::Elem* HashTableExtern::Make_New_Node(string c, int index) {
	HashTableExtern::FindList::Elem* head = new HashTableExtern::FindList::Elem(c);
	head->next = nullptr;
	head->index = index;
	return head;
}

HashTableExtern::FindList::FindList::Elem* HashTableExtern::Add_Node(string c, int index) {
	if (head == nullptr) {
		head = Make_New_Node(c, index);
	}
	else {
		HashTableExtern::FindList::Elem* node = Make_New_Node(c, index);
		HashTableExtern::FindList::Elem* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = node;
	}
	return head;
}


HashTableExtern::FindList* HashTableExtern::Make_New_Node(int in, string name, string surname) {
	FindList* node = new FindList;
	node->index = new int* [k];
	node->name = new string * [k];
	node->surname = new string * [k];
	for (int i = 0; i < k; i++) {
		node->index[i] = nullptr;
		node->name[i] = nullptr;
		node->surname[i] = nullptr;
	}
	for (int i = 0; i < k; i++) {
		if (node->index[i] == nullptr) {
			node->index[i] = new int;
			*node->index[i] = in;
			break;
		}
	}
	for (int i = 0; i < k; i++) {
		if (node->name[i] == nullptr) {
			node->name[i] = new string;
			*node->name[i] = name;
			break;
		}
	}
	for (int i = 0; i < k; i++) {
		if (node->surname[i] == nullptr) {
			node->surname[i] = new string;
			*node->surname[i] = surname;
			break;
		}
	}
	return node;
}

HashTableExtern::FindList* HashTableExtern::Add_Node(int in, string n, string s, FindList* node) {
	for (int i = 0; i < k; i++) {
		if (node->index[i] == nullptr) {
			node->index[i] = new int;
			*node->index[i] = in;
			break;
		}
	}
	for (int i = 0; i < k; i++) {
		if (node->name[i] == nullptr) {
			node->name[i] = new string;
			*node->name[i] = n;
			break;
		}
	}
	for (int i = 0; i < k; i++) {
		if (node->surname[i] == nullptr) {
			node->surname[i] = new string;
			*node->surname[i] = s;
			break;
		}
	}
	return node;
}

string HashTableExtern::Convert_To_Binary(int k) {
	string num = "";
	int n = k;
	while (n) {
		num += n % 2;
		n = n / 2;
	}
	for (int i = 0; i < num.length() / 2; i++) {
		swap(num[i], num[n - i - 1]);
	}
	return num;
}

int HashTableExtern::If_Leaf(FindList* curr) {
	//if (curr->right == nullptr && curr->left == nullptr) curr->flag = 1;
	//else {
	//	if (curr->right != nullptr || curr->left != nullptr) curr->flag = 0;
	//}
	//FindList::height++;
	//return curr->flag;
	return 0;
}



bool HashTableExtern::Read_Dat(){
	string namedat, line, in, name, surname;
	ifstream dat;
	int t, it, index, fla = 0, notend = b;
	bool find = 1;
	FindList* node;
	cout << "Ime datoteke: ";
	cin >> namedat;
	dat.open(namedat.c_str());
	if (!dat.is_open()) cout << "Nije otvorena datoteka!";

	getline(dat, line);


	while (getline(dat, line)) {
		int j = 0;
		name = "";
		surname = "";
		in = "";
		while (line[j] != ',') {
			in += line[j];
			j++;
		}
		stringstream t(in);
		t >> index;
		j++;
		int a = Get_Hash_Function(index);
		FindList* curr = header[a];

		while (line[j] != ',') {
			while (line[j] != ' ') {
				name += line[j];
				j++;
			}
			j++;
			while (line[j] != ',') {
				surname += line[j];
				j++;
			}
		}
		j++;

		while (j < line.length()) {
			string c;
			for (int g = j; g < line.length(); g++) {
				c += line[j];
				j++;
			}
			if (c == "") head = Add_Node("-1", index);
			else head = Add_Node(c, index);
			j++;
		}
		//if (FindKey(index) != nullptr) {
		//	dat.close();
		//	return false;
		//}
		while (curr != nullptr) {
			for (int i = 0; i < k; i++) {
				if (curr->index[i] == nullptr) {
					curr = Add_Node(index, name, surname, curr);
					fla = 1;
					break;
				}
			}
			if (fla == 1) break;
			in = Convert_To_Binary(index);
			string g = Convert_To_Binary(*curr->index[0]);
			for (int i = b; i < in.length(); i++) {
				if (g[i] != in[i]) {
					if (in[i] == 0) {
						curr = curr->left;
					}
					else curr = curr->right;
				}
			}

		}
		if (fla == 0) {
			for (int i = 0; i < k; i++) {
				if(curr == nullptr) curr = Make_New_Node(index, name, surname);
				if(header[a] == nullptr) header[a] = curr;
				break;
			}
		}
		fla = 0;

	}
	return false;
}

int HashTableExtern::tableSize() {
	return m;
}

ostream& operator<<(ostream& out, HashTableExtern& h) {
	for (int y = 0; y < HashTableExtern::m; y++) {
		if (HashTableExtern::header[y] == nullptr) {
			out << y << endl << "nullptr" << endl << endl;
			continue;
		}
		queue <HashTableExtern::FindList*> q;
		int lenght = 62, f = lenght, between = lenght, i = 0, j;
		HashTableExtern::FindList* node = nullptr;
		HashTableExtern::FindList* curr = HashTableExtern::header[y];
		curr->ind = 0;
		q.push(HashTableExtern::header[y]);
		if (h.HashTableExtern::header[y] != nullptr) {
			out << y << endl << endl;
			while (i <= HashTableExtern::FindList::height) {
				j = (1 << i);
				between = f;
				f = (f - 2) / 2;
				for (int l = 0; l < between; l++) putchar(' ');
				for (int k = 0; k < j; k++) {
					if (q.empty()) break;
					node = q.front();
					q.pop();
					if (node != nullptr) {
						if (node->left != nullptr) node->left->ind = -1;
						if (node->right != nullptr) node->right->ind = 1;
						q.push(node->left);
						q.push(node->right);
						if (i == 0) cout << endl << endl;
					}
					else {
						q.push(node);
						q.push(node);
					}
					if (node != nullptr) {
						for (int l = 0; l < between; l++) out << ' ';
						for (int g = 0; g < HashTableExtern::k; g++) {
							if (node->index[g] == nullptr) break;
							out << *node->index[g] << '\t';
						}
						if (node->ind == 1) out << "//1";
						else {
							if (node->ind == 0) out << "//0";
							else out << "//-1";
						}
					}
					else {
						for (int l = 0; l < between; l++) cout << ' ';
					}
					for (int l = 0; l < between; l++) putchar(' ');
				}
				i++;
				out << endl << endl;
			}
		}
	}
	return out;
}

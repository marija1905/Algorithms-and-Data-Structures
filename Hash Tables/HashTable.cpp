#include "HashTable.h"
int collumn, row;
bool done = false;

unsigned const int HashTable::k = GetK();
unsigned const int HashTable::p = GetP();
unsigned const int HashTable::n = pow(2, p);
int** HashTable::hashtable = Get_HashTable_Ready();
FindList* FindList::first = nullptr;

HashTable::Elem* HashTable::Make_New_Node(string c){
	Elem* head = new Elem(c);
	head->next = nullptr;
	return head;
}

HashTable::Elem* HashTable::Add_Node(string c) {
	if (head == nullptr) {
		head = Make_New_Node(c);
	}
	else {
		Elem* node = Make_New_Node(c);
		Elem* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = node;
	}
	return head;
}

unsigned int HashTable::GetK() {
	cout << "k? ";
	cin >> collumn;
	return collumn;
}

unsigned int HashTable::GetP() {
	cout << "p? ";
	cin >> row;
	return row;
}

int** HashTable::Get_HashTable_Ready() {
	HashTable::hashtable = new int* [n];
	for (int i = 0; i < n; i++) {
		HashTable::hashtable[i] = new int[k];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			hashtable[i][j] = -1;
		}
	}
	return hashtable;
}

int HashTable::Get_Hash_Function(int key) {
	return key % n;
}


bool HashTable::Deal_With_Colision(int a, string n, string s) {
	int* arr = new int[HashTable::n];
	for (int r = 0; r < HashTable::k; r++) {
		if (hashtable[a][r] == -1) {
			hashtable[a][r] = index;
			FindList::first = FindList::Add_Node(hashtable[a][r], n , s);
			return true;
		}
	}
	arr[a] = 1;
	int try1 = 0, i = 1;
	while (true) {
		AdressFunction* ptr = new DoubleHashing;
		int ad = ptr->getAdress(index, a, i, HashTable::n);
		a = ad;
		if (hashtable[a][try1] == -1) {
			hashtable[a][try1] = index;
			FindList::first = FindList::Add_Node(hashtable[a][try1], n, s);
			return true;
		}
		try1++;
		if (try1 == HashTable::k) {
			try1 = 0;
			i++;
			if (arr[a] == 1) return false;
			arr[a] = 1;
		}
	}
	return false;
}


int* HashTable::FindKey(int k) {
	int* arr = new int[HashTable::n];
	int a = Get_Hash_Function(k);
	for (int j = 0; j < HashTable::k; j++) {
		if (hashtable[a][j] == -1) return nullptr;
		if (hashtable[a][j] == k) {
			return &hashtable[a][j];
		}
	}

	arr[a] = 1;
	int try1 = 0, i = 1;
	while (true) {
		AdressFunction* ptr = new DoubleHashing;
		int ad = ptr->getAdress(index, a, i, HashTable::n);
		a = ad;
		if (hashtable[a][try1] == -1) return nullptr;
		if (hashtable[a][try1] == k) {
			return &hashtable[a][try1];
		}
		try1++;
		if (try1 == HashTable::k) {
			try1 = 0;
			i++;
			if (arr[a] == 1) return nullptr;
			arr[a] = 1;
		}
	}
	return nullptr;
}


bool HashTable::Read_Dat() {
	string namedat, line, in;
	ifstream dat;
	int t, it, fla = 0;
	bool find = 1;

	cout << "Ime datoteke: ";
	cin >> namedat;
	dat.open(namedat.c_str());
	if (!dat.is_open()) cout << "Nije otvorena datoteka!";

	getline(dat, line);

	while (getline(dat, line)) {
		int j = 0;
		in = "";
		name = "";
		surname = "";
		while (line[j] != ',') {
			in += line[j];
			j++;
		}
		stringstream t(in);
		t >> index;
		j++;

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
			for(int g = j; g < line.length(); g++){
				c += line[j];
				j++;
			}
			if (c == "") head = Add_Node("-1");
			else head = Add_Node(c);
			j++;
		}

		if (FindKey(index) != nullptr) {
			dat.close();
			return false;
		}

		int a = Get_Hash_Function(index);
		for (int s = 0; s < HashTable::k; s++) {
			if (hashtable[a][s] == -1) {
				hashtable[a][s] = index;
				FindList::first = FindList::Add_Node(hashtable[a][s], name, surname);
				fla = 1;
				break;
			}
		}
		if (fla == 0) find = Deal_With_Colision(a, name, surname);
		else fla = 0;
	}
	dat.close();
	return find;
}

bool HashTable::Read_From_Console(int k) {
	string exam;
	int ind;
	cout << "Unesite ime, prezime i ispite" << endl;
	while (true) {
		index = k;
		cin >> name;
		cin >> surname;
		cin >> exam;
		while (true) {
			head = Add_Node(exam);
			if (exam == "-1") break;
			cin >> exam;
		}
		
		int a = Get_Hash_Function(index);
		for (int s = 0; s < HashTable::k; s++) {
			if (hashtable[a][s] == -1) {
				hashtable[a][s] = index;
				FindList::first = FindList::Add_Node(hashtable[a][s], name, surname);
				return true;
			}
			if (hashtable[a][s] == k) return false;
		}

		return Deal_With_Colision(a, name, surname);
	}
	return false;
}


bool HashTable::insertKey(int k, string name, string surname) {
	int ind;
	bool insert;
	cout << "1. Ucitavanje iz dat" << endl;
	cout << "2. Ucitavanje sa standardnog ulaza" << endl;
	cin >> ind;
	switch (ind) {
	case 1:
		insert = Read_Dat();
		cout << insert << endl;
		break;
	case 2:
		int key;
		cout << "Kljuc? ";
		cin >> key;
		k = key;
		insert = Read_From_Console(k);
		cout << insert << endl;
		break;
	}
	return false;
}

bool HashTable::deleteKey(int k) {
	Elem* now = head;
	Elem* prev = head;
	FindList* curr = FindList::first;
	FindList* before = FindList::first;
	int* arr = new int[HashTable::n];

	while (curr != nullptr) {
		if (k == curr->inde) {
			if (now == head) {
				head = head->next;
				FindList::first = FindList::first->next;
				delete(now);
				delete(curr);
				break;
			}
			else {
				before->next = curr->next;
				prev->next = now->next;
				delete(now);
				delete(curr);
				break;
			}
		}
		prev = now;
		now = now->next;
		before = curr;
		curr = curr->next;
	}

	if (FindKey(k) != nullptr) {
		int a = Get_Hash_Function(k);
		for (int j = 0; j < HashTable::k; j++) {
			if (hashtable[a][j] == -1) return false;
			if (hashtable[a][j] == k) {
				hashtable[a][j] = -2;
				return true;
			}
		}

		arr[a] = 1;
		int try1 = 0, i = 1;
		while (true) {
			AdressFunction* ptr = new DoubleHashing;
			int ad = ptr->getAdress(index, a, i, HashTable::n);
			a = ad;
			if (hashtable[a][try1] == -1) return false;
			if (hashtable[a][try1] == k) {
				hashtable[a][try1] = -2;
				return true;
			}
			try1++;
			if (try1 == HashTable::k) {
				try1 = 0;
				i++;
				if (arr[a] == 1) return false;
				arr[a] = 1;
			}
		}
	}
	return false;
}

void HashTable::clear() {
	Elem* now = head;
	Elem* prev = head;
	FindList* curr = FindList::first;
	FindList* before = FindList::first;
	while (curr != nullptr) {
		curr = curr->next;
		now = now->next;
		delete(before);
		delete(prev);
		before = curr;
		prev = now;
	}
	head = nullptr;
	FindList::first = nullptr;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			hashtable[i][j] = -1;
		}
	}
}

int HashTable::keyCount() const {
	int num = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (hashtable[i][j] != -1 && hashtable[i][j] != -2) num++;
		}
	}
	return num;
}

int HashTable::tableSize() const {
	return n;
}

void HashTable::Print_Subjects(int num) const {
	int s = 0;
	Elem* curr1 = head;
	while (s != num) {
		curr1 = curr1->next;
		s++;
	}
	if(curr1->codeSubject != "-1") cout << curr1->codeSubject << endl;
}

void HashTable::Print_List(int k) const {
	int num = 0, flag = 0;
	FindList* curr = FindList::first;
	while (curr != nullptr) {
		if (k == curr->inde) {
			cout << curr->inde << endl << curr->na << endl << curr->su << endl;
			flag = 1;
			break;
		}
		curr = curr->next;
		num++;
	}
	if(flag == 1)Print_Subjects(num);
}

double HashTable::fillRatio() {
	return keyCount() / (double(tableSize()) * k);
}

FindList* FindList::Make_New_Node(int in) {
	FindList* node = new FindList(in);
	node->next = nullptr;
	return node;
}

FindList* FindList::Add_Node(int in, string n, string s) {
	if (first == nullptr) {
		first = Make_New_Node(in);
		first->inde = in;
		first->na = n;
		first->su = s;
		first->h = &in;
	}
	else {
		FindList* node = Make_New_Node(in);
		node->inde = in;
		node->na = n;
		node->su = s;
		node->h = &in;
		FindList* curr = first;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		curr->next = node;
	}
	return first;
}

ostream& operator<<(ostream& out, HashTable& h) {
	for (int i = 0; i < HashTable::n; i++) {
		for (int j = 0; j < HashTable::k; j++) {
			if (HashTable::hashtable[i][j] == -1) out << "EMPTY" << "\t";
			else {
				if (HashTable::hashtable[i][j] == -2) out << "DELETED" << "\t";
				else out << HashTable::hashtable[i][j] << "\t";
			}
		}
		out << endl;
	}
	out << endl;
	return out;
}

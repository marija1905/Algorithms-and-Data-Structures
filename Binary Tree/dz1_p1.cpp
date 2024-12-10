#include <iostream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;
const int MAX = 256;

struct BinTree {
	string key, info;
	int ind = 0, height = 0;
	BinTree* left, * right, * parent;
};

BinTree* MakeNewNode() {
	BinTree* root = new BinTree;
	root->left = nullptr;
	root->right = nullptr;
	return root;
}

BinTree* FindBefore(BinTree* node) {
	BinTree* r = node->left;
	if (node->left != nullptr) {
		while (r->right != nullptr) r = r->right;
		return r;
	}
	else {
		return nullptr;
	}
}

BinTree* InsertBefore(BinTree* root, BinTree* newnode) {
	BinTree* curr = root;
	while (curr != nullptr) {
		if (curr->key < newnode->key) {
			curr = curr->right;
		}
		else {
			if (curr->key > newnode->key) curr = curr->left;
			else {
				BinTree* r = FindBefore(curr);
				if (r == nullptr) {
					curr->left = newnode;
					break;
				}
				if (curr->left == r) {
					curr->left = newnode;
					newnode->left = r;
				}
				else if (curr->right == r) {
					r->right = newnode;
				}
			}
		}
	}
	return root;

}

BinTree* Read(BinTree* root) {
	BinTree* node = nullptr;
	int flag = 0;
	cout << "kljuc: ";
	if (root == nullptr) {
		root = MakeNewNode();
		cin >> root->key;
		if (root->key == "END") {
			root->ind = 1;
			return root;
		}

		cout << "prevod: ";
		cin >> root->info;
	}
	else {
		if (root->left == nullptr && root->right == nullptr) root->height += 1;
		node = MakeNewNode();
		cin >> node->key;
		if (node->key == "END") {
			root->ind = 1;
			return root;
		}
		cout << "prevod: ";
		cin >> node->info;
		BinTree* curr = root;

		while (curr != nullptr) {
			if (curr->key > node->key) {
				if (curr->left == nullptr) {
					curr->left = node;
					flag = 1;
					break;
				}
				curr = curr->left;
			}
			else {
				if (curr->key == node->key) {
					root = InsertBefore(root, node);
					break;
				}
				if (curr->right == nullptr) {
					curr->right = node;
					flag = 1;
					break;
				}
				curr = curr->right;
			}
			if (flag == 1) break;
		}
		if (node->right == nullptr && node->left == nullptr) root->height += 1;
	}
	return root;

}

BinTree* InsertInfo(BinTree* root, BinTree* curr) {
	int flag = 0;
	if (root == nullptr) {
		curr = root;
	}
	else {
		if (root->left == nullptr && root->right == nullptr) root->height += 1;
		BinTree* node = root;
		while (node != nullptr) {
			if (curr->key < node->key) {
				if (node->left == nullptr) {
					node->left = curr;
					flag = 1;
					break;
				}
				node = node->left;
			}
			else {
				if (curr->key == node->key) {
					root = InsertBefore(root, curr);
					break;
				}
				if (node->right == nullptr) {
					node->right = curr;
					flag = 1;
					break;
				}
				node = node->right;
			}
			if (flag == 1) break;
		}
		if (curr->right == nullptr && curr->left == nullptr) root->height += 1;
	}
	return root;
}

BinTree* GetInfo(BinTree* root, istream& dat) {
	BinTree* curr = root;
	char* array;
	string keep;
	int i = 0, flag = 0, flag1 = 0;
	char c;

	array = new char[MAX];


	while ((c = dat.get()) != EOF) {
		if (root == nullptr) {
			root = MakeNewNode();
			curr = root;
		}
		else curr = MakeNewNode();
		while (c != '-') {
			if (flag1 == 1) break;
			array[i] = c;
			i++;
			c = dat.get();
		}
		if (c == '-') c = dat.get();
		array[i] = '\0';
		curr->key = array;
		if (flag1 == 0) keep = array;
		else curr->key = keep;
		flag1 = 0;
		i = 0;
		while (c != ',' && c != '\n') {
			if (c == EOF) break;
			array[i] = c;
			i++;
			c = dat.get();
		}
		array[i] = '\0';
		curr->info = array;
		i = 0;
		if (c == '\n' || c == EOF || c == ',') {
			if (flag == 1) root = InsertInfo(root, curr);
			flag = 1;
		}
		if (c == ',') flag1 = 1;
	}
	delete[] array;
	return root;
}

BinTree* Read1(BinTree* root) {
	string name;
	ifstream dat;

	cout << "Ime datoteke: ";
	cin >> name;
	dat.open(name.c_str());
	if (!dat.is_open()) cout << "Nije otvorena datoteka!";

	root = GetInfo(root, dat);


	dat.close();
	return root;

}

void Print(BinTree* root) {
	if (root == nullptr) return;
	queue <BinTree*> q;
	BinTree* node = nullptr;
	BinTree* curr = root;
	root->ind = 0;
	int lenght = 62, f = lenght, between = lenght, i = 0, j;
	q.push(root);
	while (i <= root->height) {
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
				for (int l = 0; l < between; l++) cout << ' ';
				cout << node->key;
				if (node->ind == 1) cout << "//1";
				else {
					if (node->ind == 0) cout << "//0";
					else cout << "//-1";
				}
			}
			else {
				for (int l = 0; l < between; l++) cout << ' ';
			}
			for (int l = 0; l < between; l++) putchar(' ');
		}
		i++;
		cout << endl << endl;
	}
}

BinTree* Choose(BinTree* root) {
	int n2;
	cout << "1. Citaj sa standardnog ulaza." << endl;
	cout << "2. Citaj iz datoteke." << endl;
	cin >> n2;
	switch (n2) {
	case 1:
		while (true) {
			root = Read(root);
			if (root->ind == 1) break;
		}
		break;
	case 2:
		root = Read1(root);
		break;

	}
	return root;
}

string Search(BinTree* root) {
	int flag = 0;
	string word;
	string find = "";
	BinTree* before;
	cin >> word;
	while (root != nullptr) {
		if (root->key < word) root = root->right;
		else {
			if (root->key > word) root = root->left;
			else {
				before = root;
				find = root->info;
				cout << "Prevod zadatog kljuca: " << find;
				BinTree* curr = root;
				while (before) {
					before = FindBefore(curr);
					if (before == nullptr) break;
					if ((before->key == curr->key) && (root->key == curr->key)) cout << ", " << before->info;
					curr = before;
				}
				break;
			}
		}
	}
	return find;
}

string FindTheShortest(BinTree* root, string word) {
	int i = 0;
	queue <BinTree*> q;
	BinTree* c;
	string min, find;
	q.push(root);
	BinTree* node;
	while (i <= root->height) {
		if (q.empty() == true) break;
		node = q.front();
		if (node->key == word) q.pop();
		if (node->key[0] != word[0]) {
			q.pop();
		}
		if (node != nullptr) {
			if (node->left != nullptr) q.push(node->left);
			if (node->right != nullptr) q.push(node->right);
		}
		i++;
	}

	if (q.empty() == true) return "";
	else {
		c = q.front();
		min = c->key;
		q.pop();
		while (q.empty() == false) {
			if (q.front() == nullptr) break;
			find = q.front()->key;
			q.pop();
			if (size(find) < size(min)) {
				min = find;
			}
			else {
				int mi = 0, fi = 0, f1 = 0, f2 = 0;
				if (size(min) == size(find)) {
					for (int j = 0; j < size(min); j++) {
						if (min[j] == word[j] && f1 == 0)  mi++;
						else f1 = 1;
						if (find[j] == word[j] && f2 == 0) fi++;
						else f2 = 0;
					}
					if (mi < fi) min = find;
				}
			}
		}

	}
	return min;

}

//brisanje cvorova
BinTree* DeleteNode(BinTree* root, string key) {
	int i = 1;
	BinTree* node1 = root;
	BinTree* node2 = nullptr;
	BinTree* before = nullptr;
	while (node1 != nullptr) {
		if (key == node1->key) break;
		node2 = node1;
		if (key > node1->key) node1 = node1->right;
		else node1 = node1->left;
	}

	BinTree* ptr = nullptr, * s = nullptr, * l = nullptr;
	if (node1 == nullptr) return root;

	if (node1->left == nullptr) ptr = node1->right;
	else {
		if (node1->right != nullptr) {
			ptr = node1->right;
			l = ptr->left;
			s = node1;
			while (l != nullptr) {
				s = ptr;
				ptr = l;
				l = ptr->left;
			}
			if (s != node1) {
				s->left = ptr->right;
				ptr->right = node1->right;
			}
			if (ptr != nullptr) ptr->left = node1->left;
		}
		else ptr = node1->left;
	}
	if (node2 == nullptr) root = ptr;
	else {
		if (node1 != node2->left) node2->right = ptr;
		else node2->left = ptr;
	}
	delete node1;

	return root;

}

BinTree* S(BinTree* root, string key) {
	BinTree* h = root;
	while (h) {
		if (h->key < key) h = h->right;
		else {
			if (h->key == key) return h;
			h = h->left;
		}
	}
	return nullptr;
}

void DeleteTree(BinTree* root) {
	queue <BinTree*> q;
	q.push(root);
	while (q.empty() == false) {
		root = q.front();
		if (root != nullptr) {
			q.push(root->left);
			q.push(root->right);
			root = DeleteNode(root, root->key);
		}
		q.pop();
		if (root == nullptr) break;
	}
}

int main() {
	BinTree* root = nullptr;
	string find, key, word, min;
	cout << "1. Formiranje stabla na osnovu zadatog skupa reci i njihovog prevoda." << endl;
	cout << "2. Pretraga stabla na zadatu rec i dohvatanje prevoda." << endl;
	cout << "3. Umetanje u stablo nov par reci." << endl;
	cout << "4. Ispis sadrzaja stabla." << endl;
	cout << "5. Brisanje zadatog kljuca." << endl;
	cout << "6. Brisanje stabla iz memorije." << endl;
	cout << "7. Nalazenje najkrace reci sa istim prefiksom." << endl;
	cout << "8. Kraj :)" << endl;
	int ind1;
	cin >> ind1;
	do {
		switch (ind1) {
		case 1:
			root = nullptr;
			root = Choose(root);
			break;
		case 2:
			cout << "Trazeni kljuc: ";
			find = Search(root);
			if (find == "") cout << "Zadati kljuc ne postoji u stablu!";
			break;
		case 3:
			root = Read(root);
			break;
		case 4:
			Print(root);
			break;
		case 5:
			cout << "Unesite kljuc koji zelite da izbrisete: ";
			cin >> key;
			BinTree* before;
			root = DeleteNode(root, key);
			before = S(root, key);
			while ((before != nullptr) && (before->key == key)) {
				root = DeleteNode(root, key);
				before = S(root, key);
			}
			break;
		case 6:
			DeleteTree(root);
			break;
		case 7:
			cout << "Zadata rec: ";
			cin >> word;
			min = FindTheShortest(root, word);
			cout << "Najkraca rec sa istim prefiksom: " << min << endl;
			break;
		case 8:
			break;
		}
		cin >> ind1;

	} while (ind1 != 8);
	return 0;
}
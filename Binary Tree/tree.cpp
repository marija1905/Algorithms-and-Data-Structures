#include "tree.h"
int n;
int Tree::num = 0;
int Tree::red() {
	do {
		cout << "Unesite red stabla: ";
		cin >> n;
	} while (n < 3 || n > 10);
	return n;
}

Tree::Elem* Tree::Elem::sort() {
	if (len == 0) return this;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (i == j) continue;
			if (i < j) {
				if (arr[i] > arr[j]) {
					string tmp = arr[i];
					arr[i] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}
	return this;
}

Tree::Elem::Elem() {
	arr = new string [n];
	next = new (Elem * [n + 1]);
	parent = nullptr;
	for (int i = 0; i < n + 1; i++) {
		next[i] = nullptr;
	}
}

const int Tree::order = red();


void Tree::deletee() {
	queue <Elem*> q;
	Elem* node = root;
	q.push(node);
	while(q.empty() != true) {
		node = q.front();
		for (int i = 0; i < order + 1; i++) {
			if (node->next[i] == nullptr) break;
			q.push(node->next[i]);
		}
		delete(node);
		q.pop();
	}

}

bool Tree::Find_Key() {
	string key;
	cout << "Unesite vrednost kljuca: ";
	cin >> key;
	queue <Elem*> q;
	Elem* node = root;
	q.push(node);
	while (q.empty() != true) {
		node = q.front();
		for (int i = 0; i < order + 1; i++) {
			if (node->next[i] == nullptr) break;
			q.push(node->next[i]);
		}
		for (int k = 0; k < node->len; k++) {
			if (key == node->arr[k]) {
				return true;
			}
		}

		q.pop();
	}
	return false;
}

string Tree::Find_K() {
	int k;
	cout << "Unesite k: ";
	cin >> k;
	queue <Elem*> q;
	Elem* node = root;
	Elem* p = new Elem[num * order];
	p->arr = new string[num * order];
	int s = num;
	int j = 0;
	q.push(node);
	s--;
	while (s != 0) {
		node = q.front();
		for (int i = 0; i < order + 1; i++) {
			if (node->next[i] == nullptr) break;
			q.push(node->next[i]);
		}
		int z = 0;
		while(z < node->len) {
			p->arr[j] = node->arr[z];
			z++;
			j++;
		}
		q.pop();
		if (q.empty() == true) break;
		s--;
	}
	p->len = s;
	p->sort();
	return p->arr[k];
}

Tree& Add_Key(Tree& tree) {
	string key;
	cout << "Unseite vrednost kljuca: ";
	cin >> key;
	Tree::Elem* q = tree.root;
	int i, ind = 0;
	if (q == nullptr) q = new Tree::Elem;
	int j;
	i = q->len;
	Tree::num++;
	if (i != Tree::order) q->len++;
	if (i == Tree::order) {
		q->flag = 1;
	}
	if (i != Tree::order) {
		q->arr[i] = key;
		i++;
	}
	q->sort();
	tree.root = q;
	if (q->flag == 1) {
		int i, j;
		int l = Tree::order;
		Tree::Elem* p = new Tree::Elem;
		p->arr = new string[3 * l];
		Tree::Elem* node = q;
		for (i = 0; i < node->len; i++) {
			if (node->next[i] == nullptr && q->flag == 1) {
				for (j = 0; j < node->len; j++) {
					p->arr[j] = node->arr[j];
				}
				p->arr[node->len] = key;
				p->len = node->len + 1;
				p->sort();
				for (j = 0; j < node->len; j++) node->arr[j] = "";
				node->arr[0] = p->arr[(node->len + 1) / 2 - 1];
				node->next[0] = new Tree::Elem;
				node->next[1] = new Tree::Elem;

				for (int k = 0; k < (node->len + 1) / 2 - 1; k++) {
					node->next[0]->arr[k] = p->arr[k];
					node->next[0]->len++;
				}
				int t = 0;
				for (int k = (node->len + 1) / 2; k < node->len + 1; k++) {
					node->next[1]->arr[t] = p->arr[k];
					node->next[1]->len++;
					t++;
				}
				node->len = 1;
				tree.root = node;
				q->flag = 0;
			}
			else {
				Tree::Elem* b = node;
				int fl = 0, t = 0;
				while (b != nullptr) {
					for (t = 0; t < b->len; t++) {
						if (key < b->arr[t]) {
							if (b->next[t] != nullptr) {
								Tree::Elem* node1 = b;
								b = b->next[t];
								b->parent = node1;
							}
							else {
								fl = 1;
								break;
							}
						}
						if (t == b->len - 1) {
							if (b->next[t + 1] != nullptr) {
								Tree::Elem* node1 = b;
								b = b->next[t + 1];
								fl = 1;
								b->parent = node1;
								break;
							}
						}
					}
					if (fl) {
						b->arr[b->len + 1] = key;
						b->len++;
						b->sort();
						break;
					}
				}
				if (b->len >= l - 1) {
					for (int s = 0; s < 3 * l; s++) p->arr[s] = "";
					p->len = 0;
					for (int s = 0; s < b->parent->next[t]->len; s++) {
						p->arr[s] = b->parent->next[t]->arr[s];
						p->len++;
					}
					p->arr[b->parent->next[t]->len] = b->parent->arr[t];
					p->len++;
					for (int s = 0; s < b->parent->next[t + 1]->len; s++) {
						p->arr[s + b->parent->next[t]->len + 1] = b->parent->next[t + 1]->arr[s];
						p->len++;
					}
					for (int s = 0; s < b->parent->next[t]->len; s++) b->parent->next[t]->arr[s] = "";
					for (int s = 0; s < b->parent->next[t + 1]->len; s++) b->parent->next[t + 1]->arr[s] = "";
					if (b->parent->next[t]->len < l - 1 || b->parent->next[t + 1]->len < l - 1) {
						b->parent->arr[t] = p->arr[p->len / 2];
						for (int s = 0; s < p->len / 2; s++) {
							b->parent->next[t]->arr[s] = p->arr[s];
							b->parent->next[t]->len = p->len / 2;
						}
						cout << b->parent->next[t]->arr[0] << b->parent->next[t]->arr[1];
						int z = 0;
						for (int s = p->len / 2 + 1; s < p->len; s++) {
							b->parent->next[t + 1]->arr[z] = p->arr[s];
							b->parent->next[t + 1]->len = p->len - (p->len / 2);
							z++;
						}
					}
					else {
						for (int s = 0; s < 3 * l; s++) p->arr[s] = "";
						p->len = 0;
						for (int s = 0; s < b->parent->next[t]->len; s++) {
							p->arr[s] = b->parent->next[t]->arr[s];
							p->len++;
						}
						p->arr[b->parent->next[t]->len] = b->parent->arr[t];
						p->len++;
						for (int s = 0; s < b->parent->next[t + 1]->len; s++) {
							p->arr[s + b->parent->next[t]->len + 1] = b->parent->next[t + 1]->arr[s];
							p->len++;
						}
						b->parent->next[t]->len = 0;
						b->parent->next[t + 1]->len = 0;
						for (int s = 0; s < b->parent->next[t]->len; s++) b->parent->next[t]->arr[s] = "";
						for (int s = 0; s < b->parent->next[t + 1]->len; s++) b->parent->next[t + 1]->arr[s] = "";
						for (int s = 0; s < ((2 * l - 2) / 3); s++) {
							b->parent->next[t]->arr[s] = p->arr[s];
							b->parent->next[t]->len++;
						}
						b->parent->arr[t] = p->arr[(2 * l - 2) / 3];
						int z = 0;
						for (int s = ((2 * l - 2) / 3) + 1; s < ((2 * l - 1) / 3); s++) {
							b->parent->next[t + 1]->arr[z] = p->arr[s];
							b->parent->next[t + 1]->len++;
							z++;
						}
						b->parent->arr[t + 1] = p->arr[(2 * l - 1) / 3];
						b->parent->next[t + 2] = new Tree::Elem;
						z = 0;
						for (int s = (2 * l - 1) / 3 + 1; s < 2 * l / 3; s++) {
							b->parent->next[t + 2]->arr[z] = p->arr[s];
							b->parent->next[t + 2]->len++;
							z++;
						}
					}
				}
			}
		}
	}
	return tree;
}

ifstream& operator>>(ifstream& f, Tree& tree) {
	Tree::Elem* q = tree.root;
	int i, ind = 0;
	string h;
	q = new Tree::Elem();
	q->parent = q;
	if (q->len < Tree::order) {
		int j;
		i = 0;
		while (getline(f, h)) {
			Tree::num++;
			if (i != Tree::order) q->len++;
			if (i == Tree::order) {
				if (h == "") return f;
				q->flag = 1;
				break;
			}
			q->arr[i] = h;
			i++;
		}
		q->sort();
		tree.root = q;
	}
	if (q->flag == 1) {
		int i, j;
		while (true) {
			int l = Tree::order;
			Tree::Elem* p = new Tree::Elem;
			p->arr = new string[3 * l];
			Tree::Elem* node = q;
			for (i = 0; i < node->len; i++) {
				if (node->next[i] == nullptr && q->flag == 1) {
					for (j = 0; j < node->len; j++) {
						p->arr[j] = node->arr[j];
					}
					p->arr[node->len] = h;
					p->len = node->len + 1;
					p->sort();
					for (j = 0; j < node->len; j++) node->arr[j] = "";
					node->arr[0] = p->arr[(node->len + 1) / 2 - 1];
					node->next[0] = new Tree::Elem;
					node->next[1] = new Tree::Elem;

					for (int k = 0; k < (node->len + 1) / 2 - 1; k++) {
						node->next[0]->arr[k] = p->arr[k];
						node->next[0]->len++;
					}
					int t = 0;
					for (int k = (node->len + 1) / 2; k < node->len + 1; k++) {
						node->next[1]->arr[t] = p->arr[k];
						node->next[1]->len++;
						t++;
					}
					node->len = 1;
					tree.root = node;
					q->flag = 0;
				}
				else {
					Tree::Elem* b = node;
					int fl = 0, t = 0;
					while (b != nullptr) {
						for (t = 0; t < b->len; t++) {
							if (h < b->arr[t]) {
								if (b->next[t] != nullptr) {
									Tree::Elem* node1 = b;
									b = b->next[t];
									b->parent = node1;
								}
								else {
									fl = 1;
									break;
								}
							}
							if (t == b->len - 1) {
								if (b->next[t + 1] != nullptr) {
									Tree::Elem* node1 = b;
									b = b->next[t + 1];
									fl = 1;
									b->parent = node1;
									break;
								}
								else {
									fl = 1;
									break;
								}
							}
						}
						if (fl) {
							b->arr[b->len + 1] = h;
							b->len++;
							b->sort();
							break;
						}
					}
					if (b->len >= l - 1) {
						for (int s = 0; s < 3 * l; s++) p->arr[s] = "";
						p->len = 0;
						for (int s = 0; s < b->parent->next[t]->len; s++) {
							p->arr[s] = b->parent->next[t]->arr[s];
							p->len++;
						}
						p->arr[b->parent->next[t]->len] = b->parent->arr[t];
						p->len++;
						for (int s = 0; s < b->parent->next[t + 1]->len; s++) {
							p->arr[s + b->parent->next[t]->len + 1] = b->parent->next[t + 1]->arr[s];
							p->len++;
						}
						for (int s = 0; s < b->parent->next[t]->len; s++) b->parent->next[t]->arr[s] = "";
						for (int s = 0; s < b->parent->next[t + 1]->len; s++) b->parent->next[t + 1]->arr[s] = "";
						if (b->parent->next[t]->len < l - 1 || b->parent->next[t + 1]->len < l - 1) {
							b->parent->arr[t] = p->arr[p->len / 2];
							for (int s = 0; s < p->len / 2; s++) {
								b->parent->next[t]->arr[s] = p->arr[s];
								b->parent->next[t]->len = p->len / 2;
							}
							cout << b->parent->next[t]->arr[0] << b->parent->next[t]->arr[1];
							int z = 0;
							for (int s = p->len / 2 + 1; s < p->len; s++) {
								b->parent->next[t + 1]->arr[z] = p->arr[s];
								b->parent->next[t + 1]->len = p->len - (p->len / 2);
								z++;
							}
						}
						else {
							for (int s = 0; s < 3 * l; s++) p->arr[s] = "";
							p->len = 0;
							for (int s = 0; s < b->parent->next[t]->len; s++) {
								p->arr[s] = b->parent->next[t]->arr[s];
								p->len++;
							}
							p->arr[b->parent->next[t]->len] = b->parent->arr[t];
							p->len++;
							for (int s = 0; s < b->parent->next[t + 1]->len; s++) {
								p->arr[s + b->parent->next[t]->len + 1] = b->parent->next[t + 1]->arr[s];
								p->len++;
							}
							b->parent->next[t]->len = 0;
							b->parent->next[t + 1]->len = 0;
							for (int s = 0; s < b->parent->next[t]->len; s++) b->parent->next[t]->arr[s] = "";
							for (int s = 0; s < b->parent->next[t + 1]->len; s++) b->parent->next[t + 1]->arr[s] = "";
							for (int s = 0; s < ((2 * l - 2) / 3); s++) {
								b->parent->next[t]->arr[s] = p->arr[s];
								b->parent->next[t]->len++;
							}
							b->parent->arr[t] = p->arr[(2 * l - 2) / 3];
							int z = 0;
							for (int s = ((2 * l - 2) / 3) + 1; s < ((2 * l - 1) / 3); s++) {
								b->parent->next[t + 1]->arr[z] = p->arr[s];
								b->parent->next[t + 1]->len++;
								z++;
							}
							b->parent->arr[t + 1] = p->arr[(2 * l - 1) / 3];
							b->parent->next[t + 2] = new Tree::Elem;
							z = 0;
							for (int s = (2 * l - 1) / 3 + 1; s < 2 * l / 3; s++) {
								b->parent->next[t + 2]->arr[z] = p->arr[s];
								b->parent->next[t + 2]->len++;
								z++;
							}
						}
					}
				}
			}
			Tree::num++;
			getline(f, h);
			if (h == "") break;
		}
	}
	return f;
}

ostream& operator<<(ostream& out, Tree& tree) {
	queue <Tree::Elem*> q;
	Tree::Elem* node;
	tree.root->level = 0;
	q.push(tree.root);
	int u = 0;
	node = tree.root;
	while (q.empty() != true) {
		u++;
		for (int i = 0; i < Tree::order + 1; i++) {
			if (node->next[i] != nullptr) {
				q.push(node->next[i]);
				node->next[i]->level = u;
			}
		}
		q.pop();
		if (q.empty() == true) break;
		node = q.front();
	}
	node = tree.root;
	string s = "				";
	q.push(node);
	for (int i = 0; i < u; i++) {
		while (i == node->level) {
			out << s;
			for (int j = 0; j < Tree::order + 1; j++) if (node->next[j] != nullptr) q.push(node->next[j]);
			for (int j = 0; j < node->len; j++) {
				out << node->arr[j] << " ";
			}
			q.pop();
			if (q.empty() == true) break;
			node = q.front();
		}
		cout << endl;
	}
	return out;
}

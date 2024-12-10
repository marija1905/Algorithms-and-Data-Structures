#include <stdio.h>
#include <stdlib.h>
#define SAFE_MALLOC(p, n, type)\
p = malloc(n*sizeof(type));\
if(p == NULL) {\
exit(-1);\
}
#define SAFE_CALLOC(p, n, type)\
p = calloc(n, sizeof(type));\
if(p == NULL){\
exit(-1);\
}
typedef struct treeNode {
	struct treeNode* parent;
	struct treeNode** sons;
	int** matrix;
	int* magic, * used;
	int val;
	int level, ind;
}TreeNode;
typedef struct listNode {
	struct listNode* next;
	int el;
}ListNode;
typedef struct Queue {
	struct Queue* next;
	int** m;
}queue;
queue* Alocate(queue* front, int n) {
	int** m = NULL;
	SAFE_MALLOC(front, n, queue)
		SAFE_MALLOC(front->m, n, int*)
		for (int i = 0; i < n; i++) {
			SAFE_MALLOC(front->m[i], n, int)
		}
	return front;
}
queue* newnode(int n) {
	queue* new = NULL;
	new = Alocate(new, n);
	return new;
}
TreeNode* NewNode(TreeNode* parent, int n) {
	int** matrix = NULL;
	TreeNode** sons = NULL;
	SAFE_MALLOC(parent, n, TreeNode)
		SAFE_MALLOC(parent->matrix, n, int*)
		for (int i = 0; i < n; i++) {
			SAFE_MALLOC(parent->matrix[i], n, int)
		}
	SAFE_CALLOC(parent->used, n * n, int);
	SAFE_MALLOC(parent->sons, n * n, TreeNode*)
		return parent;
}
ListNode* node() {
	ListNode* new = NULL;
	SAFE_MALLOC(new, 1, ListNode)
		new->el = 0;
	new->next = NULL;
	return new;
}
ListNode* AddNode(ListNode* head, int el) {
	ListNode* new = node();
	if (head == NULL) {
		head = new;
		head->el = el;
	}
	else {
		new->next = head;
		head = new;
		head->el = el;
	}
	return head;
}
ListNode* LinkedList(ListNode* head, int n) {
	int el;
	printf("Unesite skup vrednosti : ");
	for (int i = 0; i < n * n; i++) {
		scanf_s("%d", &el);
		head = AddNode(head, el);
	}
	return head;
}
ListNode* CopyList(ListNode* head, ListNode* head1, int n) {
	ListNode* curr = head;
	while (curr != NULL) {
		head1 = AddNode(head1, curr->el);
		curr = curr->next;
	}
	return head1;
}
TreeNode* Load(ListNode* head, TreeNode* parent, int n) {
	int find = 0;
	int ini, inj, tmp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			parent->matrix[i][j] = 0;
		}
	}
	ListNode* curr = head;
	ListNode* curr1 = head;
	while (1) {
		printf("Unesite vrednost koju zelite da dodate u kvadrat (0 za izlaz): ");
		scanf_s("%d", &tmp);
		if (tmp < 0) exit(-1);
		if (tmp == 0) break;
		for (curr1; curr1 != NULL; curr1 = curr1->next) {
			if (curr1->el == tmp) {
				find = 1;
				break;
			}
		}
		if (find == 1) {
			if (!tmp) break;
			printf("Unesite indeks elementa koji zelite da dodate (od 0,0 do %d,%d): ", n - 1, n - 1);
			scanf_s("%d,%d", &ini, &inj);
			if (ini > n || inj > n || ini < 0 || inj < 0) break;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (ini == i && inj == j) {
						parent->matrix[i][j] = tmp;
						break;
					}
				}
			}
		}
	}
	return parent;
}
int Sum(ListNode* head, int n) {
	int s = 0;
	ListNode* curr = head;
	for (curr; curr != NULL; curr = curr->next) {
		s += curr->el;
	}
	s = s / n;
	return s;
}
int Check_row(TreeNode* parent, int n, int s, ListNode* head) {
	int i, j, smatrix_row = 0, find = 0, smr, c = 0;
	ListNode* curr = head;
	for (i = 0; i < n; i++) {
		smatrix_row = 0;
		for (j = 0; j < n; j++) {
			smatrix_row += parent->matrix[i][j];
			curr = head;
			for (curr; curr != NULL; curr = curr->next) {
				if (curr->el == parent->matrix[i][j]) {
					curr->el = 0;
				}
			}
		}
		smr = smatrix_row;
		curr = head;
		if (smr >= 0 && smr < n * n + 1) return find = 1;
		for (int t = 0; t < n; t++) {
			c = 0;
			for (j = 0; j < n; j++) {
				if (parent->matrix[t][j] != 0) c++;
			}
			if (c == n) {
				if (smatrix_row != s) return find = -1;
				else return find = 1;
			}
			if (c < n) {
				if (smr == s) return find = -1;
			}
			if (c == n - 1 && smr < s) return find = 1;
		}
		for (curr; curr != NULL; curr = curr->next) {
			if (curr->el + smr < s) {
				smr += curr->el;
				curr->el = 0;
			}
			if (curr->el + smr == s) return find = 1;
			if (smr == s) return find = 1;
			if (smr > s) return find = -1;
		}
	}
}
int Check_collumn(TreeNode* parent, int n, int s, ListNode* head) {
	int i, j, smatrix_collumn = 0, find = 0, smc, c = 0;
	ListNode* curr = head;
	for (j = 0; j < n; j++) {
		smatrix_collumn = 0;
		for (i = 0; i < n; i++) {
			smatrix_collumn += parent->matrix[i][j];
			curr = head;
			for (curr; curr != NULL; curr = curr->next) {
				if (curr->el == parent->matrix[i][j]) {
					curr->el = 0;
				}
			}
		}
		curr = head;
		smc = smatrix_collumn;
		if (smc >= 0 && smc < n * n + 1) return find = 1;
		if (smc == s) return find = 1;
		for (i = 0; i < n; i++) {
			c = 0;
			for (int t = 0; t < n; t++) {
				if (parent->matrix[t][i] != 0) c++;
			}
			if (c == n) {
				if (smc != s) return find = -1;
				else return find = 1;
			}
			if (c < n) {
				if (smc == s) return find = -1;
			}
			if (c == n - 1 && smc < s) return find = 1;
		}
		for (curr; curr != NULL; curr = curr->next) {
			if (curr->el + smc < s) {
				smc += curr->el;
				curr->el = 0;
			}
			if (curr->el + smc == s) return find = 1;
			if (smc == s) return find = 1;
			if (smc > s) return find = -1;
		}
	}
}
int Check_diagonal(TreeNode* parent, int n, int s, ListNode* head) {
	int i, j, smatrix_diagonal, find = 0, ind1 = 0, c = 0;
	ListNode* curr = head;
	for (i = 0; i < n; i++) {
		smatrix_diagonal = 0;
		for (j = 0; j < n; j++) {
			if (i == j) {
				smatrix_diagonal += parent->matrix[i][j];
				curr = head;
				for (curr; curr != NULL; curr = curr->next) {
					if (curr->el == parent->matrix[i][j]) {
						curr->el = 0;
					}
				}
			}
		}
		curr = head;
		for (int t = 0; t < n; t++) {
			c = 0;
			for (j = 0; j < n; j++) {
				if (t == j) {
					if (parent->matrix[t][j] != 0) c++;
				}
			}
		}
		if (c == n) {
			if (smatrix_diagonal != s) return find = -1;
			else return find = 1;
		}
		if (c < n) {
			if (smatrix_diagonal == s) return find = -1;
		}
		if (c == n - 1 && smatrix_diagonal < s) return find = 1;
	}

	for (curr; curr != NULL; curr = curr->next) {
		if (curr->el + smatrix_diagonal < smatrix_diagonal) {
			smatrix_diagonal += curr->el;
			curr->el = 0;
		}
		if (smatrix_diagonal >= 0 && smatrix_diagonal < n * n + 1) return find = 1;
		if (smatrix_diagonal == 0) return find = 1;
		if (smatrix_diagonal == s) return find = 1;
		if (curr->el + smatrix_diagonal == s) ind1 = 1;
		if (curr->el + smatrix_diagonal < s) smatrix_diagonal += curr->el;
		if (smatrix_diagonal > s) return find = -1;
		if (ind1 == 1) return find = 1;
	}
}
int Checkd(TreeNode* parent, int n, int s, ListNode* head) {
	int i, j, find = 0, smd = 0, ind2 = 0, c = 0;
	ListNode* curr = head;
	for (i = 0; i < n; i++) {
		for (j = n - 1; j <= 0; j--) {
			smd += parent->matrix[i][j];
			curr = head;
			for (curr; curr != NULL; curr = curr->next) {
				if (curr->el == parent->matrix[i][j]) {
					curr->el = 0;
				}
			}
		}
		curr = head;
		for (int t = 0; t < n; t++) {
			c = 0;
			for (j = n - 1; j < 0; j++) {
				if (parent->matrix[t][j] != 0) c++;
			}
			if (c == n) {
				if (smd != s) return find = -1;
				else return find = 1;
			}
			if (c < n) {
				if (smd == s) return find = -1;
			}
			if (c == n - 1 && smd < s) return find = 1;
		}
		for (curr; curr != NULL; curr = curr->next) {
			if (curr->el + smd < smd) {
				smd += curr->el;
				curr->el = 0;
			}
		}
		curr = head;
		if (smd >= 0 && smd < n * n + 1) return find = 1;
		if (smd == 0) return find = 1;
		if (smd == s) return find = 1;
		if (curr->el + smd == s) ind2 = 1;
		if (curr->el + smd < s) smd += curr->el;
		if (smd > s) return find = -1;
		if (ind2 == 1) return find = 1;
	}


}
int IsAritmethic(ListNode* head) {
	int check = 1;
	ListNode* curr = head;
	ListNode* prev = head;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		if (curr->next == NULL) break;
		if ((prev->el + (curr->next)->el) / 2 == curr->el) continue;
		else check = 0;
	}
	return check;
}
int Check(TreeNode* parent, int n, int s, ListNode* head) {
	int find_row, find_collumn, find_diagonal, find = 0, find_d;
	find_row = Check_row(parent, n, s, head);
	find_collumn = Check_collumn(parent, n, s, head);
	find_diagonal = Check_diagonal(parent, n, s, head);
	find_d = Checkd(parent, n, s, head);
	if (n % 2 == 1) {
		if (parent->matrix[n / 2][n / 2] != 0) {
			if (parent->matrix[n / 2][n / 2] != s / n) return find = -1;
		}
	}
	if (find_row == 1 && find_collumn == 1 && find_diagonal == 1 && find_d == 1) return find = 1;
	else return find = -1;

}
ListNode* Decision(ListNode* head1, TreeNode* parent, int n) {
	ListNode* curr = head1;
	ListNode* root = NULL;
	root = parent;
	int count = 0, flag, num = 0;
	for (int i = 0; i < n; i++) {
		curr = head1;
		for (int j = 0; j < n; j++) {
			curr = head1;
			while (curr != NULL) {
				if (curr->el == parent->matrix[i][j]) {
					parent->used[i] = curr->el;
					curr->el = 0;
				}
				curr = curr->next;
			}
		}
	}
	curr = head1;
	for (curr; curr != NULL; curr = curr->next) {
		num++;
		if (curr->el != 0) count++;
	}
	curr = head1;
	for (int i = 0; i < count; i++) {
		flag = 0;
		parent->sons[i] = NewNode(parent->sons[i], n);
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				parent->sons[i]->matrix[j][k] = parent->matrix[j][k];
			}
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (parent->sons[i]->matrix[j][k] == 0) {
					curr = head1;
					for (curr; curr != NULL; curr = curr->next) {
						if (curr->el != 0) {
							parent->sons[i]->matrix[j][k] = curr->el;
							curr->el = 0;
							flag = 1;
							break;
						}
					}
				}
				if (flag == 1) break;
			}
			if (flag == 1) break;
		}
	}
	for (int i = count; i < num; i++) parent->sons[i] = NULL;
	return root;

}
void PrintMatrix(TreeNode* parent, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%5d", parent->matrix[i][j]);
		}
		printf("\n");
	}
}
queue* Insert(TreeNode* parent, queue* front, int n) {
	queue* new = newnode(n);
	if (front == NULL) {
		front = new;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				front->m[i][j] = parent->matrix[i][j];
			}
		}
	}
	else {
		new->next = front;
		front = new;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				front->m[i][j] = parent->matrix[i][j];
			}
		}
	}
	return front;
}
void PrintTree(queue* front, int n) {
	queue* curr = front;
	for (curr; curr != NULL; curr++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf(" %5d", curr->m[i][j]);
			}
		}
	}

}
TreeNode* Tree(ListNode* head, ListNode* head1, TreeNode* parent, int n, int s, queue* front) {
	int k = 0, find1, find2;
	TreeNode* root = parent;
	while (parent->sons[k] != 0) {
		if (parent->sons[k] != NULL) PrintMatrix(parent->sons[k], n);
		else break;
		front = Insert(parent->sons[k], front, n);
		find1 = Check(parent->sons[k], n, s, head);
		parent->sons[k]->magic = find1;
		parent->sons[k]->level = 1;
		if (find1 == -1) printf("%d", -1);
		else printf("%d", 1);
		head = CopyList(head1, head, n);
		k++;
	}
	return root;
}
int main() {
	int n, s, find;
	ListNode* head = NULL;
	ListNode* head1 = NULL;
	TreeNode* parent = NULL;
	TreeNode* root = NULL;
	queue* front = NULL;
	printf("1. Ucitavanje dimenzije kvadrata i skupa vrednosti:\n");
	printf("2. Validacija stanja prvog cvora:\n");
	printf("3. Formiranje stabla:\n");
	printf("4. Ispis stabla:\n");
	printf("5. Izadji iz programa\n");
	int num;
	do {
		scanf_s("%d", &num);
		switch (num) {
		case 1:
			printf("Unesite dimenzije kvadrata:\n");
			scanf_s("%d", &n);
			parent = NewNode(root, n);
			head = LinkedList(head, n);
			if (!IsAritmethic(head)) exit(-1);
			parent = Load(head, parent, n);
			front = Insert(parent, front, n);
			break;
		case 2:
			head1 = CopyList(head, head1, n);
			PrintMatrix(parent, n);
			s = Sum(head, n);
			find = Check(parent, n, s, head, head1);
			printf("%d\n", find);
			break;
		case 3:
			if (find == 1) {
				parent = Decision(head, parent, n);
				root = Tree(head, head1, parent, n, s, front);
			}
			else exit(-1);
			break;
		case 4:
			PrintTree(front, n);
			break;
		case 5:
			break;
		}
	} while (num != 5);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
typedef struct one {
	int value;
	int* next;
}One;
typedef struct graph {
	int dim;
	struct one* index[1000];
	int edges[1000];
}Graph;
Graph* MakeOneNode(Graph* graph) {
	int num, until = 0;
	printf("Unesite vrednost cvora koji zelite da dodate\n");
	scanf_s("%d ", &num);
	for (int i = 0; i < graph->dim; i++) {
		graph->index[i]->next = NULL;
	}
	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == num) {
			graph->index[i]->value = 0;
		}
	}
	for (int i = 0; i < graph->dim; i++) {
		if (graph->index[i]->value > until) until = graph->index[i]->value;
	}
	graph->index[graph->dim]->value = until;
	return graph;
}
Graph* DeleteOneNode(Graph* graph) {
	int num;
	printf("Unesite vrednost cvora koji zelite da uklonite ");
	scanf_s("%d ", &num);
	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == num) {
			graph->index[i]->value = -1;
		}
	}
	return graph;
}
Graph* ConnectTwo(Graph* graph) {
	int num1, num2, ind, j = 0, len = 0;
	printf("Zelim da povezem ");
	scanf_s("%d %d", &num1, &num2);

	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == num1) {
			if (graph->index[i]->next != NULL) {
				while (graph->edges[j] != 0) {
					len++;
					j++;
				}
				if (graph->edges[i + 1] != 0) {
					for (j = len - 1; j <= 0; j--) {
						graph->edges[j + 1] = graph->edges[j];
					}
				}
				graph->edges[len] = num2;
				if (graph->index[i + 1]->value != 0) {
					graph->index[i + 1]->value = len + 2;
				}
				break;
			}
			else {
				for (j = 0; j < graph->index[graph->dim]->value + 1; j++) {
					if (graph->edges[j] == 0) {
						graph->index[i]->value = j + 1;
						graph->edges[j] = num2;
						graph->index[i]->next = graph->edges[j];
						break;
					}
				}
			}
		}
	}
	graph->index[graph->dim]->value += 2;
	return graph;

}
Graph* DeleteConnection(Graph* graph) {
	int num1, num2, until = 0;
	printf("Zelim da obrisem vezu izmedju ");
	scanf_s("%d %d ", &num1, &num2);

	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == num1) {
			if ((abs(graph->index[i + 1]->value - graph->index[i]->value) > 1) && graph->edges[graph->index[i]->value] != 0) {
				int k = i;
				while(graph->edges[k] != 0){
					graph->edges[k] = graph->edges[k + 1];
					k++;
				}
				for (int j = i + 1; j < graph->dim; j++) {
					graph->index[j]->next = graph->edges[j - 1];
					if (graph->index[j]->value > 0) graph->index[j]->value--;
				}
				graph->edges[k - 1] = 0;
			}
			else {
				graph->index[i]->next == NULL;
				int k = graph->index[i]->value - 1;
				graph->index[i]->value = 0;
				while (graph->edges[k] != 0) {
					graph->edges[k] = graph->edges[k + 1];
					k++;
				}
				for (int j = i; j < graph->dim; j++) {
					graph->index[j]->next = graph->edges[j - 1];
					if (graph->index[j]->value > 0) graph->index[j]->value--;
				}
				graph->edges[k - 1] = 0;
			}
		}

	}
	return graph;

}
void PrintGraph(Graph* graph) {
	int until = 0;
	for (int i = 0; i < graph->dim; i++) {
		if (graph->index[i]->value > until) until = graph->index[i]->value;
	}
	printf("Edges array\nIndeksi: ");
	for (int i = 0; i < until; i++) {
		printf("%d ", i + 1);
	}
	printf("\nCvorovi: ");
	for (int i = 0; i < until; i++) {
		printf("%d ", graph->edges[i]);
	}
	printf("\nIndex array\nCvorovi: ");
	for (int i = 0; i <= graph->dim; i++) {
		printf("%d ", i + 1);
	}
	printf("\nIndeksi: ");
	for (int i = 0; i <= graph->dim; i++) {
		printf("%d ", graph->index[i]->value);
	}
}
void FreeMemory(Graph* graph) {
	free(graph);
}
int FindFirstWay(Graph* graph, int start, int end) {
	int mif, nowf = 0, o = 1, ind = 0;
	One* first;
	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == start) {
			first = graph->index[i];
		}
	}
	for (int i = 0; i < graph->dim; i++) {
		first = graph->index[i]->next;
		nowf++;
		if ((abs(graph->index[i + 1]->value - graph->index[i]->value) > 1) && graph->edges[graph->index[i]->value] != 0) {
			if (graph->edges[i + 1] == end) {
				mif = nowf;
				printf("First: %d\n", mif);
				return;
			}
		}
		if (o == 1 && (first == end || graph->edges[i] == end)) {
			mif = nowf;
			nowf = 0;
			for (int j = 0; j < graph->dim; j++) {
				if ((abs(graph->index[i + 1]->value - graph->index[i]->value) > 1) && graph->edges[graph->index[i]->value] != 0) {
					ind++;
					if (abs(graph->index[i + 1]->value - graph->index[i]->value) == ind) continue;
					graph->index[i]->next = graph->edges[i + 1];
				}
			}
			o = 0;
		}
		if (o == 0 && (first == end || graph->edges[i] == end)) {
			if (nowf < mif && nowf != 0) mif = nowf;
		}
	}
	printf("First: %d\n", mif);
	return mif;

}
int FindSecondWay(Graph* graph, int start, int end) {
	int mis, nows = 0, o = 1, j = 0, ind = 0;
	One* second = NULL;
	for (int i = 0; i < graph->dim; i++) {
		if (i + 1 == start) {
			second = graph->index[i];
		}
	}
	for (int i = 0; i < graph->dim; i++) {
		if ((i + 1) % 2 == 1) {
			second = graph->index[j]->next;
		}
		else {
			second = graph->edges[++j];
		}
		if (second == NULL) return 0;
		nows++;
		if ((abs(graph->index[j + 1]->value - graph->index[j]->value) > 1) && graph->edges[graph->index[j]->value] != 0) {
			if (graph->edges[j + 1] == end) {
				mis = nows;
				printf("Second: %d", mis);
				return;
			}
		}
		if (o == 1 && (second == end || graph->edges[j] == end)) {
			mis = nows;
			nows = 0;
			for (int k = 0; k < graph->dim; k++) {
				if ((abs(graph->index[j + 1]->value - graph->index[j]->value) > 1) && graph->edges[graph->index[j]->value] != 0) {
					ind++;
					if (abs(graph->index[j + 1]->value - graph->index[j]->value) == ind) continue;
					graph->index[j]->next = graph->edges[j + 1];
				}
			}
			o = 0;
		}
		if (o == 0 && (second == end || graph->edges[j] == end)) {
			if (nows < mis && nows != 0) mis = nows;
			break;
		}
		j++;
	}
	printf("Second: %d", mis);
	return mis;
}
int main() {
	int n, ind;
	Graph* graph = NULL;
	Graph* pointer[1000];
	Graph* edges[1000];
	graph = malloc(sizeof(graph));
	printf("1. Dodaj cvor u graf\n");
	printf("2. Ukloni cvor iz grafa\n");
	printf("3. Dodaj granu izmedju dva cvora\n");
	printf("4. Ukloni granu izmedju dva cvora\n");
	printf("5. Ispisi graf\n");
	printf("6. Izbrisi graf iz memorije\n");
	printf("7. Ne ljuti se covece\n");
	printf("8. Kraj:)\n");
	printf("Unesite broj cvorova: ");
	scanf_s("%d", &n);
	int o = 1, mif, mis, start, end;
	for (int i = 0; i <= n; i++) {
		graph->index[i] = malloc(sizeof(One));
	}
	do {
		scanf_s("%d", &ind);
		switch (ind) {
		case 1:
			graph->dim = n;
			if (o == 1) {
				for (int i = 0; i < graph->dim; i++) {
					graph->index[i]->value = -1;
				}
				for(int i = 0; i < 2*graph->dim; i++) graph->edges[i] = 0;
				o = 0;
			}
			graph = MakeOneNode(graph);
			break;
		case 2:
			graph = DeleteOneNode(graph);
			break;
		case 3:
			graph = ConnectTwo(graph);
			break;
		case 4:
			graph = DeleteConnection(graph);
			break;
		case 5:
			 PrintGraph(graph);
			 break;
		case 6:
			FreeMemory(graph);
			break;
		case 7:
			printf("Startni cvor: ");
			scanf_s("%d", &start);
			printf("Ciljni cvor: ");
			scanf_s("%d", &end);
			mif = FindFirstWay(graph, start, end);
			mis = FindSecondWay(graph, start, end);
			if (mis == 0) {
				printf("\nFirst won");
				break;
			}
			if (mif > mis) printf("\nSecond won");
			else {
				if (mif < mis) printf("\nFirst won");
				else printf("\nTie");
			}
			break;
		case 8:
			break;
		}

	} while (ind != 8);
	return 0;
}
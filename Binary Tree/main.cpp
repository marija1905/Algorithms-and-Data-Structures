#include "tree.h"

int main() {
	int d;
	cout << "1. Stvarane objekta stabla zadatog reda i brisanje objekta stabla " << endl;
	cout << "2. Pronalazenje kljuca u stablu" << endl;
	cout << "3. Ispisivanje sadrzaja stabla" << endl;
	cout << "4. Umetanje kljuca u stablo" << endl;
	cout << "5. Brisanje kljuca iz stabla" << endl;
	cout << "6. K-ti bajmanji kljuc" << endl << "7. Kraj" << endl;
	Tree t;
	ifstream file;
	string name;
	Tree tree;
	cin >> d;
	do {
		switch (d) {
		case 1:
			cout << "Unesite naziv datoteke: ";
			cin >> name;
			file.open(name);
			if (!file.is_open()) {
				cout << "Ne postoji datoteka sa zadatim nazivom.";
				exit(1);
			}
			file >> tree;
			file.close();
			cout << tree;
			tree.~Tree();
			break;
		case 2:
			cout << t.Find_Key();
			break;
		case 3:
			cout << t;
			break;
		case 4:
			Add_Key(t);
			break;
		case 5:
			break;
		case 6:
			cout << t.Find_K();
			break;
		case 7:
			break;
		}
		cin >> d;

	} while (d != 7);
}
#include "HashTable.h"
#include "HashTableExtern.h"
int main() {
	HashTable* ha = new HashTable;
	HashTableExtern* ex = new HashTableExtern;
	int n = 5, o;
	do{
		cout << "1. Zadatak" << endl;
		cout << "2. Zadatak" << endl;
		cin >> o;
		switch (o) {
		case 1:
			cout << "MENI" << endl << endl;
			cout << "1. Nadji kljuc" << endl;
			cout << "2. Umetni kljuc" << endl;
			cout << "3. Izbrisi kjuc" << endl;
			cout << "4. Isprazni tabelu" << endl;
			cout << "5. Broj kljuceva u tabeli" << endl;
			cout << "6. Velicina tabele" << endl;
			cout << "7. Ispis sadrzaja tabele" << endl;
			cout << "8. Stepen popunjenosti tabele" << endl;
			cout << "9. Kraj :)" << endl;
			cout << "---------------------------------" << endl;
			int ind;
			do {
				cin >> ind;
				switch (ind) {
				case 1:
					int k;
					cout << "Kljuc? ";
					cin >> k;
					ha->Print_List(k);
					break;
				case 2:
					ha->insertKey(n, "", "");
					break;
				case 3:
					int ka;
					cout << "Unesite kljuc koji zelite da izbrisete: ";
					cin >> ka;
					ha->deleteKey(ka);
					break;
				case 4:
					ha->clear();
					break;
				case 5:
					cout << "Broj kljuceva u tabeli: " << ha->keyCount();
					break;
				case 6:
					cout << "Velicina tabele: " << ha->tableSize();
					break;
				case 7:
					cout << *ha;
					break;
				case 8:
					cout << "Popunjenost: " << ha->fillRatio();
					break;
				case 9:
					break;
				default:
					break;
				}
			} while (ind < 9 && ind > 0);
			break;
		case 2:
			cout << "MENI" << endl << endl;
			cout << "1. Nadji kljuc" << endl;
			cout << "2. Umetni kljuc" << endl;
			cout << "3. Izbrisi kjuc" << endl;
			cout << "4. Isprazni tabelu" << endl;
			cout << "5. Broj kljuceva u tabeli" << endl;
			cout << "6. Velicina tabele" << endl;
			cout << "7. Ispis sadrzaja tabele" << endl;
			cout << "8. Stepen popunjenosti tabele" << endl;
			cout << "9. Kraj :)" << endl;
			cout << "---------------------------------" << endl;
			int ind1;
			do {
				cin >> ind1;
				switch (ind1) {
				case 1:
					break;
				case 2:
					ex->Read_Dat();
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					cout << "Velicina tabele: " << ex->tableSize();
					break;
				case 7:
					cout << *ex;
					break;
				case 8:
					break;
				case 9:
					break;
				default:
					break;
				}
			} while (ind1 < 9 && ind1 > 0);
		}
	
	} while (o != 1 || o != 2);
	

	
	
}
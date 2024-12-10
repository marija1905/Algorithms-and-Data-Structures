#include <iostream>
#include <string>

using namespace std;

//binarna pretraga
double BinSearch(double low, double high, double err, int& i) {
	double mid;
	int fi;
	while (low <= high) {
		mid = low + (high - low) / 2;
		cout << mid << endl;
		cout << i << ". Da li je trazeni broj veci(1), manji(-1) ili jednak(0)? ";
		i++;
		cin >> fi;
		if (fi == 0 || (high - low) <= err) return mid;
		else {
			if (fi == -1) high = mid - err;
			else low = mid + err;
		}
	}
}
double Find() {
	int i = 1, f;
	double high, low, err, mid, find, l;
	cout << "low: "; cin >> low;
	cout << "high: "; cin >> high;
	cout << "tacnost: "; cin >> err;
	l = low;
	while (true) {
		mid = low + (high - low) * 0.2; // prvih 20% intervala
		cout << mid << endl;
		cout << i << ". Da li je trazeni broj veci(1), manji(-1) ili jednak(0)? ";
		i++;
		cin >> f;
		if (f == 0) {
			cout << "Trazeni broj je " << mid << endl;
			cout << "Broj koraka: " << i-1 << endl;
			return 0;

		}
		else {
			if (f == -1) { 
				find = BinSearch(l, mid, err, i);
				cout << "Trazeni broj je " << find << endl;
				cout << "Broj koraka: " << i-1 << endl;
				return find;
			}
			else {
				low = mid;
			}
		}
	}
}
int main() {
	int sw;
	double find;
	cout << "1. Zapocni igru " << endl;
	cout << "2. Kraj " << char(3) << endl;
	do {
		cin >> sw;
		switch (sw) {
		case 1:
			find = Find();
			break;
		case 2:
			break;
		}
	} while (sw < 3);
	return 0;
}

#include "Zellen.hpp"
#include "ranglist.hpp"
#include <string.h>
#include <fstream>

int mezo::cellaszam;


int main() {
	int psz;
	cout << "Udvozol teged az aknakereso!" << endl;
	cout << endl;
	cout << "A jatek soran harom nehezsegi fokozat kozul tudsz valasztani:" << endl;
	cout << "   - Nyomj 1-est, ha kezdo vagy (1 pont)" << endl;
	cout << "   - Nyomj 2-est, ha halado vagy (2 pont)" << endl;
	cout << "   - Nyomj 3-ast, ha profi vagy (3 pont)" << endl;
	cout << endl;
	cout << "Az eredmenyed egy ranglistan fog elmentodni, ami alapjan osszemerheted magad masokkal" << endl;
	cout << "Add meg a felhasznaloneved:" << endl;
	char nev[50];
	cin >> nev;
	bool ingame = true;
	player lista[20];
	load(lista);

	while (ingame==true) {
		
		int fokozat = 5;
		cout << "Add meg a nehezsegiszintet, amin jatszani szeretnel:" << endl;

		while (fokozat < 0 || fokozat > 2) {
			cin >> fokozat;
			if (fokozat < 0 || fokozat >2) cout << "Nem ervenyes nehezsegi szint." << endl;
		}

		mezo A(fokozat);
		int x = 0, y = 0;
		A.print();
		int z = 1;

		while ((z != 0) && (z != 2)) {
			while (x<1 || x >(A.getsize() + 1) || y < 1 || y >(A.getsize() + 1)) {
				cin >> x;
				cin >> y;
			}
			koords koordinatak(y, x);
			z = A - koordinatak;
			A.print();
			x = 0;
			y = 0;
		}
		if (z == 0) {
			cout << "Vesztettel!" << endl;
		}
		else if (z == 2) {
			cout << "Gyoztel!" << endl;
			save(nev, fokozat, lista);
		}
		cout << endl;
		cout << "Meg szeretned nezni a ranglistat?" << endl;
		cout << "0-->nem   1-->igen" << endl;
		int a = 0;
		cin >> a;
		if (a == 1) {
			if (lista[0].psz == (-1)) cout << "egyelore ures a lista" << endl;
			else {
				int i = 0;
				while (lista[i].psz != (-1)) {
					cout << (i+1) << ". helyezett: " << lista[i].nev << "  " << lista[i].psz <<" Pont"<< endl;
					i++;
				}
			}
		}
		cout << "Nyomj 1-est, ha ujrakezdened a jatekot, vagy 0-at, ha nem:" << endl;
		cin >> ingame;
	}

	
	return 0;
}
#include "Zellen.hpp"
#include <time.h>
using namespace std;

mezo::mezo(int szint) {
	srand(time(0));
	Tot_Y = 0;
	Tot_X = 0;
	Bombanzahl = 0;
	if (szint == 1) {
		Tot_Y = 9;
		Tot_X = 9;
		Bombanzahl = 10;
		mezo::cellaszam = 9 * 9;
	}
	else if (szint == 2) {
		Tot_Y = 16;
		Tot_X = 16;
		Bombanzahl = 40;
		mezo::cellaszam = 16 * 16;
	}
	else if (szint == 3) {
		Tot_Y = 24;
		Tot_X = 24;
		Bombanzahl = 99;
		mezo::cellaszam = 24 * 24;
	}
	
	playground = new Zellen**[(Tot_Y+2)];
	for (int i = 0; i < (Tot_Y+2); i++) {
		playground[i] = new Zellen*[(Tot_X+2)];
	}

	for (int x = 0; x < Tot_X + 2; x++) { 
		for (int y=0; y < Tot_Y + 2; y++) {
			playground[x][y] = new ures();
		}
	}

	int mines = 0;
	while (mines < Bombanzahl)
	{
		int x = 0, y = 0;
		while (x<1 || x >(Tot_X + 1) || y<1 || y>(Tot_Y + 1)) {
			x = rand() % (Tot_X);
			y = rand() % (Tot_Y);
		}

		if (playground[x][y]->type != 1)
		{
			playground[x][y]->type = 1;
			playground[x][y] = new Bomb();
			mines++;
		}
	}

	for (int x = 0; x < Tot_X+2; x++) {
		for (int y =0 ; y < Tot_Y+2; y++) {
			if (x == 0 || x == Tot_X + 1 || y == 0 || y == Tot_Y + 1) { 
				delete[] playground[x][y];
				playground[x][y] = new edge; 
			}
			if ((playground[x][y]->type != 1) && (playground[x][y]->type != 4)) {
				int szomszed = 0;
					if (playground[x + 1][y + 1]->type == 1) szomszed++;
					if (playground[x + 1][y]->type == 1) szomszed++;
					if (playground[x + 1][y - 1]->type == 1) szomszed++;
					if (playground[x][y + 1]->type == 1) szomszed++;
					if (playground[x][y - 1]->type == 1) szomszed++;
					if (playground[x - 1][y + 1]->type == 1) szomszed++;
					if (playground[x - 1][y]->type == 1) szomszed++;
					if (playground[x - 1][y - 1]->type == 1) szomszed++;

					if (szomszed > 0) {
						delete[] playground[x][y];
						playground[x][y] = new number(szomszed);
					}
			}
		}
	}
}


ostream& operator<<(ostream& os, const Bomb& bomba) {
	if (bomba.hidden == 1) {
		os << " - ";
	}
	else {
		os << " * ";
	}
	return os;
}
ostream& operator<<(ostream& os, const number& szam) {
	if (szam.hidden == 1) {
		os << " - ";
	}
	else {
		os << " " <<szam.Zustand << " ";
	}
	return os;
}
ostream& operator<<(ostream& os, const ures& urescella) {
	if (urescella.hidden == 1) {
		os << " - ";
	}
	else {
		os << "   ";
	}
	return os;
}
ostream& operator<<(ostream& os, const edge& szelso) {
	cout << " x ";
	return os;
}
void Bomb::print() {
	cout << (*this);
}
void edge::print() {
	cout << (*this);
}
void ures::print() {
	cout << (*this);
}
void number::print() {
	cout << (*this);
}
void mezo::print() {
	cout << "    ";
	for (int i = 1; i < (Tot_X + 1); i++) { 
		if(i<10) cout << "  " << i;
		if (i > 9) cout << " " << i;
	}
	cout << endl;
	int i = 1;
	for (int x = 0; x < (Tot_X + 2); x++) {
		if ((1 + Tot_X) > x &&  0<x ) {
			if(i<10) cout << i << " ";
			if (i > 9) cout << i;
			i++;
		}
		else {
			cout << "  ";
		}
		for (int y = 0; y < (Tot_Y + 2); y++) {
			(*playground[x][y]).print();
		}
		cout << endl;
	}
}

int mezo::tipp(const int x,const int y) {
	playground[x][y]->hidden = 0;
	if (playground[x][y]->type != 4 && playground[x][y]->type != 1) cellaszam--;
	if (cellaszam == Bombanzahl) return 2;
	if (((playground[x][y]->type) == 3 && x>0 && x <(Tot_X+2) && y > 0 && y <(Tot_Y+2))) {
		if ((playground[x+1][y+1]->type == 3 || playground[x + 1][y + 1]->type == 2) && playground[x + 1][y + 1]->hidden) tipp(x + 1, y + 1);
		if ((playground[x+1][y]->type == 3 || playground[x + 1][y]->type == 2) && playground[x + 1][y]->hidden) tipp(x + 1, y);
		if ((playground[x+1][y-1]->type == 3 || playground[x + 1][y - 1]->type == 2) && playground[x + 1][y - 1]->hidden) tipp(x + 1, y - 1);
		if ((playground[x][y+1]->type == 3 || playground[x][y + 1]->type == 2) && playground[x][y + 1]->hidden) tipp(x, y + 1);
		if ((playground[x][y - 1]->type == 3 || playground[x][y - 1]->type == 2) && playground[x][y - 1]->hidden) tipp(x, y - 1);
		if ((playground[x-1][y+1]->type == 3 || playground[x - 1][y + 1]->type == 2) && playground[x - 1][y + 1]->hidden) tipp(x - 1, y + 1);
		if ((playground[x-1][y]->type == 3 || playground[x - 1][y]->type == 2)&& playground[x - 1][y]->hidden) tipp(x - 1, y);
		if ((playground[x-1][y-1]->type == 3 || playground[x - 1][y - 1]->type == 2) && playground[x - 1][y - 1]->hidden) tipp(x - 1, y - 1);
	}
	else if (playground[x][y]->type == 1) {
		lose();
		return 0;
	}
	return 1;
}
int mezo::operator-(const koords& other) {
	return (this->tipp(other.x, other.y));
}
void mezo::lose() {
	for (int x = 0; x < Tot_X + 2; x++) {
		for (int y = 0; y < Tot_Y + 2; y++) {
			if(playground[x][y]->type == 1) playground[x][y]->hidden = false;
		}
	}
}


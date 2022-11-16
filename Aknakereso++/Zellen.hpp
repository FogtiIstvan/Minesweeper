#ifndef ZELLEN_HPP
#define ZELLEN_HPP

#include <iostream>
#include <string>

using namespace std;

class Zellen{
public:
	Zellen() : hidden(1), type(0) {};
	
	virtual void print() = 0;
	friend class mezo;
protected:
	bool hidden;
	int type;
};


class Bomb:public Zellen {
public:
	Bomb() : Zellen() { type = 1; };
	
	void print();
	friend ostream& operator<<(ostream& os, const Bomb&);
};


class number:public Zellen {
	int Zustand;
public:
	number(int szomszed = 0) : Zellen() { type = 2; Zustand = szomszed; }
	friend class mezo;

	void print();
	friend ostream& operator<<(ostream& os, const number&);
};


class ures:public Zellen {
public:
	ures() : Zellen() { type = 3; };
	
	void print();
	friend ostream& operator<<(ostream& os, const ures&);
};


class edge :public Zellen {
public:
	edge() :Zellen() { type = 4; }

	void print();
	friend ostream& operator<<(ostream& os, const edge&);
};
struct koords {
	int x;
	int y;
	koords(int x, int y) : x(x), y(y) {};
};

class mezo {
private:
	Zellen*** playground;
	int Tot_Y;
	int Tot_X;
	int Bombanzahl;
public:
	mezo(int szint);
	~mezo() { for (int i = 0; i < (Tot_Y + 2); i++) delete[] playground[i]; delete[] playground; }
	friend class ures;
	void print();
	int tipp(int x, int y);
	int getsize() { return Tot_X; }
	void lose();
	int operator-(const koords& other);

	static int cellaszam;
};



#endif // !ZELLEN_HPP


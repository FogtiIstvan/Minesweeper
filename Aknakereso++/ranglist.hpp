#pragma once
#ifndef RANGLIST_HPP
#define RANGLIST_HPP

#include <iostream>
#include <string>
using string = std::string;

struct player {
	string nev;
	int psz;

	player(string nev, int psz) :nev(nev), psz(psz) {};
	player() :nev(""), psz(-1) {};
	~player() {};
	friend void sort(player* arr);
};

void save(string nev, int psz, player* arr);
void load(player* arr);


#endif // !RANGLIST_HPP

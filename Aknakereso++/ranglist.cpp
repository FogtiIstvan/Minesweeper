#include "ranglist.hpp"
#include <fstream>

void sort(player* arr) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 19; j++) {
			if (arr[j].nev == arr[j + 1].nev) {
				arr[j].psz += arr[j + 1].psz;
				arr[j + 1].nev = " ";
				arr[j + 1].psz = -1;
			}
			if (arr[j].psz < arr[j + 1].psz) {
				player tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
void save(string nev, int psz, player* arr) {
	player ujjatekos(nev, psz);

	std::ifstream ranglista("lista.dat", std::ios::out | std::ios::binary);
	for (int i = 0; i < 20; i++) {
		ranglista.read((char*)&arr[i], sizeof(player));
	}
	ranglista.close();
	remove("lista.dat");

	arr[19] = ujjatekos;
	sort(arr);

	std::ofstream lista("lista.dat", std::ios::out | std::ios::binary);
	for (int i = 0; i < 20; i++) {
		lista.write((char*)&arr[i], sizeof(player));
	}
	lista.close();
}

void load(player* arr) {
	std::ifstream ranglista("lista.dat", std::ios::out | std::ios::binary);
	for (int i = 0; i < 20; i++) {
		ranglista.read((char*)&arr[i], sizeof(player));
	}
	ranglista.close();
}
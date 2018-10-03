#pragma once
#include <vector>

using namespace std;
void backwards(string& buff) {
	string stringek = "";
	for (int i = buff.length()-1; i >= 0; i--) {
		stringek += buff[i];
	}
	buff = stringek;
}

int decy(string bin) {
	int liczba = 0;
	backwards(bin);
	for (int i = 0; i < int(bin.length()); i++) {
		if (bin[i] == '1') {
			liczba += int(pow(2, i));
		}
	}
	return liczba;
}

void command(string& line, vector<char>& transistors, string& buffor, string& wyswietlacz) {
	char commandS = line[0];
	if (commandS != '/') {
		int number = 0;
		char gettransistor[3];
		for (int i = 2; i < int(line.length()); i++) {
			gettransistor[i - 2] = line[i];
		}
		number = atoi(gettransistor);
		if (number > 324) {
			number = 324;
		}
		if (commandS == '0') {
			transistors[number] = 0;
		}
		if (commandS == '1') {
			transistors[number] = 1;
		}
		if (commandS == '2') {
			if (transistors[number] == 0) {
				transistors[number] = 1;
			}
			else {
				transistors[number] = 0;
			}
		}
		if (commandS == '3') {
			if (buffor.length() < 32) {
				buffor += to_string(transistors[number]);
			}
		}
		if (commandS == '4') {
			wyswietlacz = buffor + " - " + to_string(decy(buffor));
		}
		if (commandS == '5') {
			buffor = "";
		}
	}
}
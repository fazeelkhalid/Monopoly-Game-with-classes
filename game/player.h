#ifndef player_H
#define player_H
#include"money.h"
#include<SFML\Graphics.hpp>
#include<fstream>
#include<iostream>
#include<string.h>

using namespace std;

class player:public money {
private:
	int PlayerNumber;
	int owner[38];
	int numberOfProperties;
	bool inJail;
	bool bitCancel;
	bool Retire;
	bool Bankrupt;
	int move[2][40]; // x at 0 and y at 1
	int currentPosition;
	
public:
	int turn = 2;
	player();
	void setPosition(int position, sf::RenderWindow &window, sf::Sprite *player, int turn, int totalPlayer, sf::Sprite dice1, sf::Sprite dice2, sf::Sprite board, sf::Text *sentece, sf::Sprite pointer, sf::Sprite *currentPlayer);
	void setPositionUnconditionally(int);
	void setPlayerNumber(int);
	void setOwner(int);
	void removeOwner(int);
	void setbitCancel(bool);
	void setRetire(bool);
	void setInJail(bool);

	bool getInjail();
	bool getbitCancel();
	int getPosition();
	int getOwner(int); // if onwer exist number if not -2
	bool getRetire();
	int getX();
	int houseOwner = 0;
	int hostelOwner = 0;
	int getY();
	void print() {
		for (int i = 0; owner[i] != -2; i++) {
			cout << owner[i] << " , ";
		}
		cout << endl;
	}
	string getPicture();
	int getX(int);
	int getY(int);
	int* getownerArray();
	friend ofstream& operator<<(ofstream& fout, player&);
	friend ifstream& operator >> (ifstream& fout, player&);
};
int* player::getownerArray() {
	return owner;
}

void player:: setInJail(bool j) {
	inJail = j;
}

bool player::getInjail() {
	return inJail;
}

void player::setRetire(bool r) {
	Retire = r;
}
bool player::getRetire() {
	return Retire;
}
void player::setPositionUnconditionally(int p) {
	currentPosition = p;
}

void player::setbitCancel(bool bit) {
	bitCancel = bit;
}


bool player::getbitCancel() {
	return bitCancel;
}

void player::setOwner(int o) {
	int size = 0;
	for (int i = 0; owner[i]!=-2; i++) {
		size++;
	}
	owner[size] = o;
	owner[size+1] = -2;
	numberOfProperties++;
}
void player::setPlayerNumber(int p) {
	PlayerNumber = p;
}
player::player() {
	owner[0] = -2;
	bitCancel = false;
	numberOfProperties = 0;
	ifstream fin;
	fin.open("Data\\Position.txt");
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 2; j++) {
			fin >> move[j][i];
		}
	}
	currentPosition = 0;
	PlayerNumber = 0;
	inJail = false;
	Retire = false;
	Bankrupt = false;
}

int player:: getOwner(int o) {
	if (owner != NULL) {
		for (int i = 0; owner[i] != -2; i++) {
			if (o == owner[i]) {
				return i;
			}
		}
	}
	return -2;
}
void player::removeOwner(int p) {
	numberOfProperties--;
	int size = 0;
	for (int i = 0; owner[i] != -2; i++) {
		size++;
	}

	for (int i = 0; i< size; i++) {
		if (p == owner[i]) {
			for (int j = i; j < size; j++) {
				owner[j] = owner[j + 1];
			}
		}
	}
	
}

void player::setPosition(int position, sf::RenderWindow &window, sf::Sprite *player,int turn,int totalPlayer, sf::Sprite dice1, sf::Sprite dice2, sf::Sprite board, sf::Text *sentece, sf::Sprite pointer, sf::Sprite *currentPlayer) {
	float temp = (float)currentPosition;
	currentPosition += position;
	while ((int)temp != currentPosition + 1) {
		player[turn].setPosition(getX(temp), getY(temp));
		window.draw(board);
		window.draw(dice1);
		window.draw(dice2);
		for (int i = 0; i < totalPlayer; i++) {
			window.draw(player[i]);
			window.draw(player[turn]);
			window.draw(sentece[i]);
			window.draw(currentPlayer[i]);
		}
		window.draw(pointer);
		window.display();
		if (temp >= 40) {
			increaseMoney(200);
			int temp1 = temp - 40;
			temp = temp1;
		}
		if (currentPosition >= 40) {
			increaseMoney(200);
			int temp1 = currentPosition - 40;
			currentPosition = temp1;
		}
		temp += 0.003;
	}
	
//7750
	//8875
}

int player::getX() {
	return move[0][currentPosition];
}
int player::getY() {
	return move[1][currentPosition];
}
int player::getX(int x) {
	return move[0][x];
}
int player::getY(int x) {
	return move[1][x];
}


string player:: getPicture() {
	if (PlayerNumber == 0) {
		return"Images\\Pieces\\Pieces0.png";
	}
	else if(PlayerNumber == 1) {
		return"Images\\Pieces\\Pieces1.png";
	}
	else if (PlayerNumber == 2) {
		return"Images\\Pieces\\Pieces2.png";
	}
	else if (PlayerNumber == 3) {
		return"Images\\Pieces\\Pieces3.png";
	}
	else if (PlayerNumber == 4) {
		return"Images\\Pieces\\Pieces4.png";
	}
	else if (PlayerNumber == 5) {
		return"Images\\Pieces\\Pieces5.png";
	}
	else if (PlayerNumber == 6) {
		return"Images\\Pieces\\Pieces6.png";
	}
}

int player:: getPosition() {
	return currentPosition;
}

ofstream& operator<<(ofstream& fout, player& p) {
	fout << p.PlayerNumber;
	fout << " ";
	for (int i = 0; p.owner[i - 1] != -2; i++) {
		fout << p.owner[i];
		fout << " ";
	}
	fout << p.inJail;
	fout << " ";
	fout << p.bitCancel;
	fout << " ";
	fout << p.Retire;
	fout << " ";
	fout << p.currentPosition;
	fout << " ";
	fout << p.getMoney();
	return fout;
}
ifstream& operator>>(ifstream& fin, player& p ) {
	fin>> p.PlayerNumber;
	for (int i = 0; p.owner[i - 1] != -2; i++) {
		fin >> p.owner[i];
	}
	fin >> p.inJail;
	fin >> p.bitCancel;
	fin >> p.Retire;
	fin >> p.currentPosition;
	int money;
	fin >> money;
	p.setMoney(money);
	return fin;
}



#endif
#ifndef chance_H
#define chance_H
#include <cstdlib>
#include <ctime>   
#include"player.h"
#include<iostream>

using namespace std;

class chance{
private:
	int card[15];
	int index;
	void shuffled();
public:
	chance();
	string getChancePic(); 
	void chanceCardAction(player *p,int turn, int totalPlayer);
};

void chance::chanceCardAction(player *p, int turn, int totalPlayer) {
	int cardNumber = card[index];
	if (cardNumber == 0) {
		if (p[turn].getPosition() > 14) {
			p[turn].increaseMoney(300);
		}
		p[turn].setPositionUnconditionally(14);
	}
	else if (cardNumber == 1) {
		p[turn].increaseMoney(100);
	}
	else if (cardNumber == 2) {
		int position = p[turn].getPosition();
		if (position == 0) {
			p[turn].setPositionUnconditionally(36);
		}
		else if (position == 1) {
			p[turn].setPositionUnconditionally(37);
		}
		else if (position == 2) {
			p[turn].setPositionUnconditionally(38);
		}
		else if (position == 3) {
			p[turn].setPositionUnconditionally(39);
		}
		else {
			position -= 4;
			p[turn].setPositionUnconditionally(position);
		}
	}
	else if (cardNumber == 3) {
		int house = p[turn].houseOwner * 50;
		int hostel = p[turn].hostelOwner * 100;
		house += hostel;
		p[turn].decreaseMoney(house);
	}
	else if (cardNumber == 4) {
		p[turn].decreaseMoney(25);
	}
	else if (cardNumber == 5) {
		int price = totalPlayer * 25;
		p[turn].decreaseMoney(price);
		for (int i = 0; i < totalPlayer; i++) {
			if (i != turn) {
				p[i].increaseMoney(25);
			}
		}
	}
	else if (cardNumber == 6) {
		p[turn].increaseMoney(150);
	}

	else if (cardNumber == 7) {
		if (p[turn].getPosition() > 5) {
			p[turn].increaseMoney(200);
		}
		p[turn].setPositionUnconditionally(5);
	}
	else if (cardNumber == 8) {
		if (p[turn].getPosition() > 5) {
			p[turn].increaseMoney(200);
		}
		p[turn].setPositionUnconditionally(5);

	}
	else if (cardNumber == 9) {

		p[turn].increaseMoney(300);
		p[turn].setPositionUnconditionally(0);

	}
	else if (cardNumber == 10) {
		if (p[turn].getPosition() > 5) {
			p[turn].increaseMoney(200);
		}
		p[turn].setPositionUnconditionally(5);
	}
	else if (cardNumber == 11) {
		p[turn].decreaseMoney(50);
	}
	else if (cardNumber == 12) {
		p[turn].decreaseMoney(50);
	}
	else if (cardNumber == 13) {
		p[turn].setPositionUnconditionally(5);
	}
	else if (cardNumber == 14) {
		p[turn].increaseMoney(400);
		p[turn].setPositionUnconditionally(0);
	}
}


void chance::shuffled() {
	int temp;
	int i = 0;
	int j = 0;
	srand(time(0));
	for (i = 0; i < 10;) {
		temp = rand() % 10;
		for (j = 0; j < i; j++) {
			if (temp == card[j]) {
				break;
			}
		}
		if (j == i) {
			card[i] = temp;
			i++;
		}
	}
}
chance::chance(){
	index = -1;
	shuffled();
}
string chance::getChancePic() {
	index++; 
	if (index == 9) {
		index = 0;
	}
	if (card[index] == 0) {
		return "Images\\Chance\\chanceTemplate 1.jpg";
	}
	else if (card[index] == 1) {
		return "Images\\Chance\\chanceTemplate 2.jpg";
	}
	else if (card[index] == 2) {
		return "Images\\Chance\\chanceTemplate 3.jpg";
	}
	else if (card[index] == 3) {
		return "Images\\Chance\\chanceTemplate 4.jpg";
	}
	else if (card[index] == 4) {
		return "Images\\Chance\\chanceTemplate 5.jpg";
	}
	else if (card[index] == 5) {
		return "Images\\Chance\\chanceTemplate 6.jpg";
	}
	else if (card[index] == 6) {
		return "Images\\Chance\\chanceTemplate 7.jpg";
	}
	else if (card[index] == 7) {
		return "Images\\Chance\\chanceTemplate 8.jpg";
	}
	else if (card[index] == 8) {
		return "Images\\Chance\\chanceTemplate 9.jpg";
	}
	else if (card[index] == 9) {
		return "Images\\Chance\\chanceTemplate 10.jpg";
	}
	else if (card[index] == 10) {
		return "Images\\Chance\\chanceTemplate 11.jpg";
	}
	else if (card[index] == 11) {
		return "Images\\Chance\\chanceTemplate 12.jpg";
	}
	else if (card[index] == 12) {
		return "Images\\Chance\\chanceTemplate 13.jpg";
	}
	else if (card[index] == 13) {
		return "Images\\Chance\\chanceTemplate 14.jpg";
	}
	else if (card[index] == 14) {
		return "Images\\Chance\\chanceTemplate 15.jpg";
	}
}

#endif // !chance_H

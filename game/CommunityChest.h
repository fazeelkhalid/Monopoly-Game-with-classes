#ifndef CommunityChest_H
#define CommunityChest_H
#include <cstdlib>
#include <ctime>   
#include<iostream>
#include"player.h"

using namespace std;

class CommunityChest {
private:
	int card[15];
	int index;
	void shuffled();
public:
	void comunityCardAction(player &p, int cardNumber);
	CommunityChest();
	int getCardNumber();
	string getCommunityPic();
	~CommunityChest();
};
void CommunityChest::comunityCardAction(player &p, int cardNumber) {
	if (cardNumber == 0) {
		p.increaseMoney(200);
	}
	else if (cardNumber == 1) {
		p.decreaseMoney(200);
	}
	else if (cardNumber == 2) {
		p.decreaseMoney(50);
	}
	else if (cardNumber == 3) {
		p.decreaseMoney(200);
	}
	else if (cardNumber == 4) {
		p.decreaseMoney(500);
	}
	else if (cardNumber == 5) {
		p.increaseMoney(500);
	}
	else if (cardNumber == 6) {
		p.decreaseMoney(100);
	}
	else if (cardNumber == 7) {
		p.decreaseMoney(200);
	}
	else if (cardNumber == 8) {
		p.increaseMoney(50);
	}
	else if (cardNumber == 9) {
		p.decreaseMoney(325);
	}
	else if (cardNumber == 10) {
		p.increaseMoney(300);
	}
	else if (cardNumber == 11) {
		p.decreaseMoney(50);
	}
	else if (cardNumber == 12) {
		p.decreaseMoney(80);
	}
	else if (cardNumber == 13) {
		p.decreaseMoney(50);
	}
	else if (cardNumber == 14) {
		p.increaseMoney(400);
		p.setPositionUnconditionally(0);
	}
}

int CommunityChest:: getCardNumber() {
	return card[index];
}


void CommunityChest::shuffled() {
	int temp;
	int i = 0;
	int j = 0;
	srand(time(0));
	for (i = 0; i < 15;) {
		temp = rand() % 15;
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

CommunityChest::CommunityChest() {
	shuffled();
	index = -1;
}
string CommunityChest::getCommunityPic() {
	index++;
	if (index == 15) {
		index = 0;
	}
	if (card[index] == 0) {
		return "Images\\Community Chest\\communityTemplate 1.jpg";
	}
	else if (card[index] == 1)  {
		return "Images\\Community Chest\\communityTemplate 2.jpg";
	}
	else if (card[index] == 2) {
		return "Images\\Community Chest\\communityTemplate 3.jpg";
	}
	else if (card[index] == 3) {
		return "Images\\Community Chest\\communityTemplate 4.jpg";
	}
	else if (card[index] == 4) {
		return "Images\\Community Chest\\communityTemplate 5.jpg";
	}
	else if (card[index] == 5) {
		return "Images\\Community Chest\\communityTemplate 6.jpg";
	}
	else if (card[index] == 6) {
		return "Images\\Community Chest\\communityTemplate 7.jpg";
	}
	else if (card[index] == 7) {
		return "Images\\Community Chest\\communityTemplate 8.jpg";
	}
	else if (card[index] == 8) {
		return "Images\\Community Chest\\communityTemplate 9.jpg";
	}
	else if (card[index] == 9) {
		return "Images\\Community Chest\\communityTemplate 10.jpg";
	}
	else if (card[index] == 10) {
		return "Images\\Community Chest\\communityTemplate 11.jpg";
	}
	else if (card[index] == 11) {
		return "Images\\Community Chest\\communityTemplate 12.jpg";
	}
	else if (card[index] == 12) {
		return "Images\\Community Chest\\communityTemplate 13.jpg";
	}
	else if (card[index] == 13) {
		return "Images\\Community Chest\\communityTemplate 14.jpg";
	}
	else if (card[index] == 14) {
		return "Images\\Community Chest\\communityTemplate 15.jpg";
	}
}
CommunityChest::~CommunityChest() {

}
#endif // !CommunityChest_H
 
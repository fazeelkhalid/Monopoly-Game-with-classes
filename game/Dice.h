#ifndef Dice_H
#define Dice_H
#include <stdlib.h>
#include <time.h>
#include <string>
#include<iostream>

using namespace std;

class dice {
private:
	int firstNumber; 
	int secondNumber;
	int index;
	int numbers[300];
public:
	dice(); // defult constructor
	int getFirstNumber(); // return 1st number
	int getSecondNumber(); // return 2nd number
	string getDicePicture(int num); // return dice pic
	void setDise(); // dice set;
	~dice();
};

dice::dice() {
	firstNumber = 1;
	secondNumber = 3;
	index = 0; // 1 increment
	srand((unsigned)time(NULL));
	for (int i = 0; i < 300; i++) {
		numbers[i] = rand() % 6 + 1;
	}
}

int dice:: getFirstNumber() {
	return firstNumber;
}

int dice::getSecondNumber() {
	return secondNumber;
}

void dice:: setDise() { 
	firstNumber = numbers[index];
	secondNumber = numbers[index+150];
	index++;
	if (index == 149) {
		index = 0;
	}
}
string dice::getDicePicture(int num) {
	if (num == 1) {
		return"Images\\Dice\\dice1.png";
	}
	else if (num == 2) {
		return"Images\\Dice\\dice2.png";
	}
	else if (num == 3) {
		return"Images\\Dice\\dice3.png";
	}
	else if (num == 4) {
		return"Images\\Dice\\dice4.png";
	}
	else if (num == 5) {
		return"Images\\Dice\\dice5.png";
	}
	else if (num == 6) {
		return"Images\\Dice\\dice6.png";
	}

}
dice::~dice() {

}
#endif // !Dice_H

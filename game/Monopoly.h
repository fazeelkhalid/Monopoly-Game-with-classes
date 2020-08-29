#ifndef Monopoly_H
#define Monopoly_H
#include<SFML/Graphics.hpp>
#include"Dice.h"
#include"CommunityChest.h"
#include"chance.h"
#include"player.h"
#include"property.h"
#include<iostream>
#include<fstream>

using namespace std;


class Monopoly {
private:
	property land[40];
	player *p;
	int x;
	int y;
	int turn; // player turn
	int totalPlayer;

	sf::Texture pro[40];
	sf::Sprite proLoad[40];
	
	int moneySize = 0;
	sf::Event event;
	void setpropertyInfo();
	int drawBuildBox(sf::RenderWindow &window,sf::Sprite);
	int buildopetionSelector(int, int);

public:
	Monopoly();
	void LoadPropertyImage(property *p);
	bool SelectPlayer(bool);
	int SelectMoney(bool&);
	void drawBoard(int, bool isCancel); // actual work
	void UpdateTurn(player*p);
	void assignProperty(player *p,int, int);
	void moneyAction(player *p, int, int, int);
	void PropertyRentAction(player *p, int);
	void Mortage(player *p, property *pro, sf::RenderWindow &window,sf::Sprite);
	void sale(player *p, property *pro, sf::RenderWindow &window, sf::Sprite);
	void build(player *p, property *pro, sf::RenderWindow &window, sf::Sprite);
	int PropertySelected(int, int);
	void TradeWithMoney(player *p,property *pro, sf::RenderWindow &window, sf::Sprite button);
	int selectPlayer(sf::RenderWindow &window);
	int money;
	
	void propertyBuyAction(player *p, int);
	int searchTotalBlockInProperty(property *p,const char *t);
	int searchTotalBlockInplayer(int *p, int block);
	char*intToCharArray(int);
	friend ofstream& operator << (ofstream& fout, Monopoly& M);
	friend ifstream& operator >>(ifstream&fin, Monopoly& m);
	void decision(player *p, property * pro, sf::RenderWindow &window, sf::Sprite button);
	~Monopoly();
};
Monopoly::Monopoly() {
	setpropertyInfo();
	x = 0;
	y = 0;
	for (int i = 0; i < 40; i++) {
		land[i].setPropertyId(i);
	}
	totalPlayer = 0;
	money = 0;
	turn = 0;
}

//check if current property where player exist if he is onwer then no rent, if not then take rent and give rent to his owner
void  Monopoly::PropertyRentAction(player *p, int turn) {
	int position = p[turn].getPosition();
	int landOwner = land[position].getOwner();
	int owner = p[turn].getOwner(land[position].getOwner());

	if (landOwner == -1) {
		moneyAction(p, turn, land[position].getOwner(), land[position].getRent());
	}
	else if (landOwner != owner) {
		moneyAction(p, turn, land[position].getOwner(), land[position].getRent());
	}
}

//if user want to buy propert then it will take money from that user and gave it to the benk this work only for bank Property;
void Monopoly::propertyBuyAction(player *p, int turn) {
	int position = p[turn].getPosition();
	int landOwner = land[position].getOwner();
	int owner = p[turn].getOwner(land[position].getOwner());
	int landPrice = land[position].getSalePrice();
	if (owner == -2) {
		p[turn].decreaseMoney(landPrice);
		p[turn].setOwner(position);
		land[position].setOwner(turn);
	}
}

//select how many player will play game
bool Monopoly::SelectPlayer(bool isCancel) {
	sf::Texture selectPlayer;
	sf::Sprite selectPlayerLoad;

	selectPlayer.loadFromFile("Images\\select player\\player0.png");
	selectPlayerLoad.setTexture(selectPlayer);

	sf::RenderWindow selectPlayerWindow(sf::VideoMode(800, 650), "Monopoly", sf::Style::Titlebar | sf::Style::Close);
	selectPlayerWindow.setKeyRepeatEnabled(false);
	bool isSelect = false;
	while (selectPlayerWindow.isOpen()) {

		while (selectPlayerWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				selectPlayerWindow.close();
				isCancel = true;
			}
			else if (sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.mouseButton.y > 240 && event.mouseButton.y < 300) {
						if (event.mouseButton.x > 180 && event.mouseButton.x < 220) {
							selectPlayer.loadFromFile("Images\\select player\\player2.png");
							totalPlayer = 2;
							isSelect = true;
						}
						else if (event.mouseButton.x > 310 && event.mouseButton.x < 360) {
							selectPlayer.loadFromFile("Images\\select player\\player3.png");
							totalPlayer = 3;
							isSelect = true;
						}
						else if (event.mouseButton.x > 440 && event.mouseButton.x < 490) {
							selectPlayer.loadFromFile("Images\\select player\\player4.png");
							isSelect = true;
							totalPlayer = 4;
						}
						else if (event.mouseButton.x > 560 && event.mouseButton.x < 620) {
							selectPlayer.loadFromFile("Images\\select player\\player5.png");
							isSelect = true;
							totalPlayer = 5;
						}
					}
					else if (event.mouseButton.y > 420 && event.mouseButton.y < 510) {
						if (event.mouseButton.x > 340 && event.mouseButton.x < 480 && isSelect) {
							selectPlayerWindow.close();
						}
					}
				}
			}
		}
		selectPlayerWindow.draw(selectPlayerLoad);
		selectPlayerWindow.display();
	}
	return isCancel;
}

//select initial money for each user
int Monopoly::SelectMoney(bool & isCancel) {
	bool isSelect = false;
	if (!isCancel) {
		sf::Texture selectMoney;
		sf::Sprite selectMoneyLoad;

		selectMoney.loadFromFile("Images\\select money\\money0.png");
		selectMoneyLoad.setTexture(selectMoney);

		sf::RenderWindow selectMoneyWindow(sf::VideoMode(800, 650), "Monopoly", sf::Style::Titlebar | sf::Style::Close);
		selectMoneyWindow.setKeyRepeatEnabled(false);
		while (selectMoneyWindow.isOpen()) {

			while (selectMoneyWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					selectMoneyWindow.close();
					isCancel = true;
				}
				else if (sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (event.mouseButton.y > 280 && event.mouseButton.y < 305) {
							if (event.mouseButton.x > 100 && event.mouseButton.x < 250) {
								selectMoney.loadFromFile("Images\\select money\\money2000.png");
								money = 5000;
								moneySize = 4;
								isSelect = true;
							}
							else if (event.mouseButton.x > 250 && event.mouseButton.x < 400) {
								selectMoney.loadFromFile("Images\\select money\\money3000.png");
								money = 10000;
								moneySize = 5;
								isSelect = true;
							}
							else if (event.mouseButton.x > 400 && event.mouseButton.x < 550) {
								selectMoney.loadFromFile("Images\\select money\\money4000.png");
								money = 15000;
								moneySize = 5;
								isSelect = true;
							}
							else if (event.mouseButton.x > 550 && event.mouseButton.x < 700) {
								selectMoney.loadFromFile("Images\\select money\\money5000.png");
								money = 20000;
								moneySize = 5;
								isSelect = true;
							}
						}
						else if (event.mouseButton.y > 430 && event.mouseButton.y < 480 && isSelect) {
							if (event.mouseButton.x > 300 && event.mouseButton.x < 510 && isSelect) {
								selectMoneyWindow.close();
							}
						}
					}
				}
			}
			selectMoneyWindow.draw(selectMoneyLoad);
			selectMoneyWindow.display();
		}
	}
	return money;
}

//as Sfml cannot display integer but it can display string so i will convert integer into char array 
char*Monopoly::intToCharArray(int m) {
	if (m <= 0) {
		m = 0;
	}
	char temp[30];
	char temp2[30];
	int num = m;
	int size = 0;
	for (size = 0; num != 0; size++) {
		num = num / 10;
	}
	num = m;
	for (int i = 0; i < size; i++) {
		temp[i] = (num % 10)+48;
		num = num / 10;
	}
	int j = size - 1;
	for (int i = 0; i < size; i++) {
		temp2[i] = temp[j];
		j--;
	}
	temp2[size] = '\0';

	return temp2;
}

// it will display ownership image all circle that occur on screen after buy a property this function creat
void Monopoly::LoadPropertyImage(property *p) {
	for (int i = 0; i < 40; i++) {
		if (p[i].getOwner() == -1) {
			pro[i].loadFromFile("Images\\subBox\\-1.png");
			proLoad[i].setTexture(pro[i]);
		}
		if (p[i].getOwner() == 4) {
			if (p[i].getMortage()) {
				pro[i].loadFromFile("Images\\subBox\\m4.png");
			}
			else {
				pro[i].loadFromFile("Images\\subBox\\4.png");
			}
			proLoad[i].setTexture(pro[i]);
		}
		else if (p[i].getOwner() == 0) {
			if (p[i].getMortage()) {
				pro[i].loadFromFile("Images\\subBox\\m0.png");
			}
			else {
				pro[i].loadFromFile("Images\\subBox\\0.png");
			}
			proLoad[i].setTexture(pro[i]);
		}
		else if (p[i].getOwner() == 2) {
			if (p[i].getMortage()) {
				pro[i].loadFromFile("Images\\subBox\\m2.png");
			}
			else {
				pro[i].loadFromFile("Images\\subBox\\2.png");
			}
			proLoad[i].setTexture(pro[i]);
		}
		else if (p[i].getOwner() == 3) {
			if (p[i].getMortage()) {
				pro[i].loadFromFile("Images\\subBox\\m3.png");
			}
			else {
				pro[i].loadFromFile("Images\\subBox\\3.png");
			}
			proLoad[i].setTexture(pro[i]);
		}
		else if (p[i].getOwner() == 1) {
			if (p[i].getMortage()) {
				pro[i].loadFromFile("Images\\subBox\\m1.png");
			}
			else {
				pro[i].loadFromFile("Images\\subBox\\1.png");
			}
			proLoad[i].setTexture(pro[i]);
		}
		else {
			pro[i].loadFromFile("Images\\subBox\\-1.png");
			proLoad[i].setTexture(pro[i]);
		}
	}

	ifstream fin;
	fin.open("Images\\subBox\\position.txt");
	int index = 0;
	while (!fin.eof()) {
		int x;
		int y;
		fin >> x;
		fin >> y;
		proLoad[index].setPosition(x,y);
		index++;
	}
}

//sett property infortaion when game start eg rent, wecan buy or not, upgrade or not, name, bock, price, etc
void Monopoly::setpropertyInfo() {
	

	land[0].setUpgradeStatus(0, 0);


	land[1].setSalePrice(250);
	land[1].setRent(250);
	land[1].setGroup("IQBAL");
	land[1].setUpgradeStatus(1,1);
	
	land[2].setUpgradeStatus(0, 0);

	land[3].setSalePrice(300);
	land[3].setRent(300);
	land[3].setGroup("IQBAL");
	land[3].setUpgradeStatus(1,1);
	
	land[4].setSalePrice(400);
	land[4].setRent(400);
	land[4].setGroup("IQBAL");
	land[4].setUpgradeStatus(1,1);

	land[5].setSalePrice(1200);
	land[5].setRent(200);
	land[5].setGroup("STATION");
	land[5].setUpgradeStatus(0, 1);


	land[6].setSalePrice(200);
	land[6].setRent(200);
	land[6].setGroup("JOHAR");
	land[6].setUpgradeStatus(1,1);

	land[7].setUpgradeStatus(0, 0);

	land[8].setSalePrice(250);
	land[8].setRent(250);
	land[8].setGroup("JOHAR");
	land[8].setUpgradeStatus(1,1);

	land[9].setSalePrice(1200);
	land[9].setRent(200);
	land[9].setGroup("STATION");
	land[9].setUpgradeStatus(0, 1);

	land[10].setUpgradeStatus(0, 0);

	land[11].setSalePrice(300);
	land[11].setRent(300);
	land[11].setGroup("FAISAL");
	land[11].setUpgradeStatus(1,1);

	land[12].setSalePrice(500);
	land[12].setRent(450);
	land[12].setGroup("UTILITY");
	land[12].setUpgradeStatus(0, 1);

	land[13].setSalePrice(400);
	land[13].setRent(400);
	land[13].setGroup("FAISAL");
	land[13].setUpgradeStatus(1,1);

	land[14].setSalePrice(400);
	land[14].setRent(400);
	land[14].setGroup("FAISAL");
	land[14].setUpgradeStatus(1,1);

	land[15].setSalePrice(1500);
	land[15].setRent(200);
	land[15].setGroup("STATION");
	land[15].setUpgradeStatus(0, 1);
	
	land[16].setSalePrice(800);
	land[16].setRent(800);
	land[16].setGroup("MODEL");
	land[16].setUpgradeStatus(1,1);

	land[17].setUpgradeStatus(0, 0);

	land[18].setSalePrice(850);
	land[18].setRent(850);
	land[18].setGroup("MODEL");
	land[18].setUpgradeStatus(1,1);

	land[19].setSalePrice(1500);
	land[19].setRent(1500);
	land[19].setGroup("MODEL");
	land[19].setUpgradeStatus(1,1);

	land[20].setUpgradeStatus(0, 0);

	land[21].setSalePrice(1000);
	land[21].setRent(1000);
	land[21].setGroup("GULBERG");
	land[21].setUpgradeStatus(1,1);

	land[22].setUpgradeStatus(0, 0);

	land[23].setSalePrice(1200);
	land[23].setRent(1200);
	land[23].setGroup("GULBERG");
	land[23].setUpgradeStatus(1,1);

	land[24].setSalePrice(1700);
	land[24].setRent(200);
	land[24].setGroup("GULBERG");
	land[24].setUpgradeStatus(1,1);

	land[25].setSalePrice(1400);
	land[25].setRent(350);
	land[25].setGroup("STATION");
	land[25].setUpgradeStatus(0, 1);

	land[26].setSalePrice(800);
	land[26].setRent(500);
	land[26].setGroup("UTILITY");
	land[26].setUpgradeStatus(0, 1);


	land[27].setSalePrice(1200);
	land[27].setRent(200);
	land[27].setGroup("DHA");
	land[27].setUpgradeStatus(1,1);

	land[28].setUpgradeStatus(0, 0);

	land[29].setSalePrice(1200);
	land[29].setRent(200);
	land[29].setGroup("DHA");
	land[29].setUpgradeStatus(1,1);

	land[30].setUpgradeStatus(0, 0);

	land[31].setSalePrice(1500);
	land[31].setRent(35);
	land[31].setGroup("UTILITY");
	land[31].setUpgradeStatus(0, 1);

	land[32].setSalePrice(1400);
	land[32].setRent(230);
	land[32].setGroup("DHA");
	land[32].setUpgradeStatus(1,1);

	land[33].setUpgradeStatus(0, 0);

	land[34].setSalePrice(300);
	land[34].setRent(250);
	land[34].setGroup("BAHRIA");
	land[34].setUpgradeStatus(1,1);

	land[35].setSalePrice(600);
	land[35].setRent(350);
	land[35].setGroup("STATION");
	land[35].setUpgradeStatus(0, 1);

	land[36].setUpgradeStatus(0, 0);

	land[37].setSalePrice(1600);
	land[37].setRent(1600);
	land[37].setGroup("BAHRIA");
	land[37].setUpgradeStatus(1,1);

	land[38].setUpgradeStatus(0, 0);

	land[39].setSalePrice(900);
	land[39].setRent(300);
	land[39].setGroup("BAHRIA");
	land[39].setUpgradeStatus(1,1);

}

//dtake money and give it to the owner of that property not work for those propert whose owner is a bank
void Monopoly::assignProperty(player *p,int position, int own) {
	int temp[12] = { 0,2,7,10,17,20,22,28,30,33,36,38 };
	bool isFound = false;;
	for (int i = 0; i < 12; i++) {
		if (position == temp[i]) {
			isFound = true;
		}
	}
	if (!isFound && (land[position].getOwner() == -2)) {
		land[position].setOwner(own);
		p[own].setOwner(position);
	}
}

//perform money action eg increase money of one player and decrease money of the other player
void Monopoly::moneyAction(player *p, int firstPlayer, int secondPlayer, int amount) {
	p[firstPlayer].decreaseMoney(amount);
	if (secondPlayer != -1) {
		p[secondPlayer].increaseMoney(amount);
	}
}

//update turn and skip those player how already lost
void Monopoly::UpdateTurn(player *p) {
	bool isRetire = false;
	while (!isRetire) {
		if (turn + 1 == totalPlayer) {
			turn = 0;
			while (p[turn].getRetire()) {
				turn++;
			}
		}
		else {
			turn++;
			while (p[turn].getRetire()) {
				turn++;
			}
		}
		if (!p[turn].getRetire()) {
			isRetire = true;
		}
	}
}

// return whic propert selected when we try for mortage sale buy and for update from relevant button
int Monopoly::PropertySelected(int x, int y) {
	int start[2][40];
	int last[2][40];
	fstream fin;
	fin.open("Images\\subBox\\MortageCordinates.txt");
	int index = 0;
	while (!fin.eof()) {
		fin >> start[0][index];
		fin >> start[1][index];
		fin >> last[0][index];
		fin >> last[1][index];
		index++;
	}
	for (int i = 0; i < 40; i++) {
		if (x > start[0][i] && x < last[0][i]) {
			if (y > start[1][i] && y < last[1][i]) {
				return i;
			}
		}
	}
	return -3;
}

//use for mortage aand unMortage
void Monopoly::Mortage(player *p, property *pro, sf::RenderWindow &window, sf::Sprite button) {
	sf::Texture Mortage;
	sf::Sprite MortageLoad;
	Mortage.loadFromFile("Images\\property\\moltage.png");
	MortageLoad.setTexture(Mortage);
	MortageLoad.setPosition(135, 120);
	bool isCancel = false;
	int landId = 0;
	while (!isCancel) {
		window.draw(MortageLoad);
		window.draw(button);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
				if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
					landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
				}
				if (landId > -3 &&event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 411 && event.mouseButton.x < 491) {
					if (p[turn].getOwner(landId) != -2 && !pro[landId].getMortage()) {
						land[landId].setMortage(1);
						isCancel = true;
						p[turn].increaseMoney(land[landId].getSalePrice() / 2);
					}
					else {
						bool ok = false;
						cout << "\t\t\nlandID : " << landId<<endl;
						sf::Texture MortageButton;
						sf::Sprite MortageButtonLoad;
						MortageButton.loadFromFile("Images\\subBox\\DEBT2.png");
						MortageButtonLoad.setTexture(MortageButton);
						MortageButtonLoad.setPosition(404, 475);
						sf::Texture alert;
						sf::Sprite alertLoad;
						alert.loadFromFile("Images\\subBox\\mortageAlert.png");
						alertLoad.setTexture(alert);
						alertLoad.setPosition(225, 225);
						while (!ok) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed) {
									window.close();
								}
								else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
									if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
										ok = true;
									}
								}
								window.draw(alertLoad);
								window.draw(MortageButtonLoad);
								window.display();
							}
						}
					}
				}
				else if (event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 161 && event.mouseButton.x < 243) {
					if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
						landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
					}

					if (p[turn].getOwner(landId) != -2 && pro[landId].getMortage()) {
						land[landId].setMortage(0);
						p[turn].increaseMoney(land[landId].getSalePrice() / 2);
						isCancel = true;
					}
					else {
						bool ok = false;
						cout << "\t\t\nlandID : " << landId << endl;
						sf::Texture MortageButton;
						sf::Sprite MortageButtonLoad;
						MortageButton.loadFromFile("Images\\subBox\\undebt.png");
						MortageButtonLoad.setTexture(MortageButton);
						MortageButtonLoad.setPosition(153, 475);						
						sf::Texture alert;
						sf::Sprite alertLoad;
						alert.loadFromFile("Images\\subBox\\unMortage.png");
						alertLoad.setTexture(alert);
						alertLoad.setPosition(225, 225);
						while (!ok) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed) {
									window.close();
								}
								else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
									if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
										
										ok = true;
									}
								}
								window.draw(alertLoad);
								window.draw(MortageButtonLoad);
								window.display();
							}
						}
					}	
				}
				else if (event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 305 && event.mouseButton.x < 347) {
					if (p[turn].getMoney() > 0) {
						isCancel = true;
					}
				}
			}
		}
	}
}

//sale any property that user want to sale
void Monopoly::sale(player *p, property *pro, sf::RenderWindow &window, sf::Sprite button) {
	sf::Texture Mortage;
	sf::Sprite MortageLoad;
	Mortage.loadFromFile("Images\\subBox\\saleProperty.png");
	MortageLoad.setTexture(Mortage);
	MortageLoad.setPosition(135, 120);
	bool isCancel = false;
	int landId = 0;
	while (!isCancel) {
		window.draw(MortageLoad);
		window.draw(button);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
				if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
					landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
				}
				if (landId > -3 && event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 411 && event.mouseButton.x < 491) { // sale Property
					if (p[turn].getOwner(landId) != -2) {
						land[landId].setOwner(-1);
						
						p[turn].increaseMoney(land[landId].getSalePrice());
						isCancel = true;
						p[turn].removeOwner(landId);
					}
					else {
						bool ok = false;
						sf::Texture alert;
						sf::Sprite alertLoad;
						alert.loadFromFile("Images\\subBox\\mortageAlert.png");
						alertLoad.setTexture(alert);
						alertLoad.setPosition(225, 225);
						while (!ok) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed) {
									window.close();
								}
								else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
									if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
										ok = true;
									}
								}
								window.draw(alertLoad);
								window.display();
							}
						}
					}
				}
				
				else if (event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 161 && event.mouseButton.x < 243) {
					isCancel = true;
				}
				
			}
		}
	}
}

//select Player For trade
int Monopoly::selectPlayer(sf::RenderWindow &window) {//select player for trade 
	sf::Texture PlayerButton[5];
	sf::Sprite PlayerButtonLoad[5];
	sf::Texture selectPlayerButton[5];
	sf::Sprite selectPlayerButtonLoad[5];
	sf::Texture trade;
	sf::Sprite tradeLoad;
	trade.loadFromFile("Images\\subBox\\t3.png");
	tradeLoad.setTexture(trade);
	tradeLoad.setPosition(135, 120);

	PlayerButton[0].loadFromFile("Images\\subBox\\tb1.png");
	PlayerButton[1].loadFromFile("Images\\subBox\\tb2.png");
	PlayerButton[2].loadFromFile("Images\\subBox\\tb3.png");
	PlayerButton[3].loadFromFile("Images\\subBox\\tb4.png");
	PlayerButton[4].loadFromFile("Images\\subBox\\tb5.png");

	selectPlayerButton[0].loadFromFile("Images\\subBox\\tb6.png");
	selectPlayerButton[1].loadFromFile("Images\\subBox\\tb7.png");
	selectPlayerButton[2].loadFromFile("Images\\subBox\\tb8.png");
	selectPlayerButton[3].loadFromFile("Images\\subBox\\tb9.png");
	selectPlayerButton[4].loadFromFile("Images\\subBox\\tb10.png");

	int x = 220;
	int y = 225;

	for (int i = 0; i < totalPlayer; i++) {
		PlayerButtonLoad[i].setTexture(PlayerButton[i]);
		selectPlayerButtonLoad[i].setTexture(selectPlayerButton[i]);
		if (turn != i) {
			selectPlayerButtonLoad[i].setPosition(x, y);
			PlayerButtonLoad[i].setPosition(x, y);
			y += 60;
		}
	}
	bool ok = false;
	int opetion = -5;
	bool isSelect = false;
	int player = -8;
	while (!ok) {

		window.draw(tradeLoad);
		for (int i = 0; i < totalPlayer; i++) {
			if (turn != i) {
				window.draw(PlayerButtonLoad[i]);
			}
		}
		if (player >=0 && player < totalPlayer) {
			window.draw(selectPlayerButtonLoad[player]);
		}

		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
				if (event.mouseButton.x > 250, event.mouseButton.x < 420) {
					if (event.mouseButton.y > 231 && event.mouseButton.y < 267) {
						player = 0;
						isSelect = true;
						if (player == turn || player > turn) {
							player++;

						}
					}
					else if (event.mouseButton.y > 297 && event.mouseButton.y < 321) {
						player = 1;
						isSelect = true;
						if (player == turn || player > turn) {
							player++;

						}
					}
					else if (event.mouseButton.y > 355 && event.mouseButton.y < 385) {
						player = 2;
						isSelect = true;
						if (player == turn || player > turn) {
							player++;

						}
					}
					else if (event.mouseButton.y > 413 && event.mouseButton.y < 443) {
						player = 3;
						isSelect = true;
						if (player == turn || player > turn) {
							player++;

						}
					}

					
				}
				else if (event.mouseButton.x > 444, event.mouseButton.x < 480 && event.mouseButton.y > 483 && event.mouseButton.y < 511 && isSelect) {
					ok = true;
					return player;
				}
				if (event.mouseButton.x > 169, event.mouseButton.x < 205 && event.mouseButton.y > 485 && event.mouseButton.y < 515) {
					ok = true;

				}
			}
		}

	}

}

//if user want to trade with money
void Monopoly::TradeWithMoney(player *p, property *pro, sf::RenderWindow &window, sf::Sprite button) {
	sf::Texture trade1;
	int landNumber = 0;
	sf::Texture tradeButton[2];
	sf::Sprite tradeButtonLoad[2];
	tradeButton[0].loadFromFile("Images\\subBox\\t0.png");
	tradeButton[1].loadFromFile("Images\\subBox\\t1.png");
	tradeButtonLoad[0].setTexture(tradeButton[0]);
	tradeButtonLoad[1].setTexture(tradeButton[1]);
	tradeButtonLoad[0].setPosition(220, 282);
	tradeButtonLoad[1].setPosition(220, 334);
	int amount = 0;

	sf::Sprite trade1Load;
	trade1.loadFromFile("Images\\subBox\\trade1.png");
	trade1Load.setTexture(trade1);
	trade1Load.setPosition(135, 120);
	bool isSelect = false;
	int operation = -6;
	bool ok = false;
	while (!ok) {
		window.draw(trade1Load);
		window.draw(button);
		if (operation != -6) {
			window.draw(tradeButtonLoad[operation]);
		}
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
				if (event.mouseButton.x > 237 && event.mouseButton.x < 421 && event.mouseButton.y>286 && event.mouseButton.y < 320) {//select Money
					int addNUmber = 0;
					int number = 0;
					sf::Texture purches;
					sf::Sprite purchesLoad;
					purches.loadFromFile("Images\\subBox\\calculator.png");
					purchesLoad.setTexture(purches);
					purchesLoad.setPosition(225, 225);
					bool done = false;
					while (!done) {
						window.draw(purchesLoad);
						window.display();
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								window.close();
							}
							if (sf::Event::MouseButtonPressed) {
								if (event.mouseButton.button == sf::Mouse::Left) {
									
									if (addNUmber % 2 == 0) {
										p[turn].selestMoneyFromCalculator(event.mouseButton.x, event.mouseButton.y, number);
									}
									else if (event.mouseButton.y > 389 && event.mouseButton.y < 412) {
										if (event.mouseButton.x > 250 && event.mouseButton.x < 282) {
											amount = number;
											done = true;
										}
										else if (event.mouseButton.x > 376 && event.mouseButton.x < 408) {
											done = true;
											amount = number;
										}
									}
									addNUmber++;
								}
							}
						}
					}
					operation = 0;
					isSelect = true;
				}
				else if (event.mouseButton.x > 237 && event.mouseButton.x < 421 && event.mouseButton.y>338 && event.mouseButton.y < 374) { // select property for trade
					operation = 1;
					sf::Texture t;
					sf::Sprite tLoad;
					t.loadFromFile("Images\\subBox\\trade2.png");
					tLoad.setTexture(t);
					tLoad.setPosition(135, 120);
					bool done = false;
					int landId = -5;
					while (!done) {
						window.draw(tLoad);
						window.display();
						while (window.pollEvent(event)) {
							if (event.type == sf::Event::Closed) {
								window.close();
							}
							else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
								std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
								if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
									landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
								}
								if (event.mouseButton.y > 483 && event.mouseButton.y < 516 && event.mouseButton.x > 440 && event.mouseButton.x < 492) { // sale Property
									if (landId == -2) {
										bool ok = false;
										sf::Texture alert;
										sf::Sprite alertLoad;
										alert.loadFromFile("Images\\subBox\\mortageAlert.png");
										alertLoad.setTexture(alert);
										alertLoad.setPosition(225, 225);
										while (!ok) {
											while (window.pollEvent(event)) {
												if (event.type == sf::Event::Closed) {
													window.close();
												}
												else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
													if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
														ok = true;
													}
												}
												window.draw(alertLoad);
												window.display();
											}
										}
									}
									else {
										done = true;
										landNumber = landId;
									}
								}
							}
						}

					}
					operation = 1;
					isSelect = true;
				}
				else if (event.mouseButton.x > 165 && event.mouseButton.x < 209 && event.mouseButton.y>482 && event.mouseButton.y < 515) {
					ok  = true;
					cout << "cancel";
				}

				else if (event.mouseButton.x > 444 && event.mouseButton.x < 482 && event.mouseButton.y>482 && event.mouseButton.y < 515) {
					if (isSelect) {
						ok = true;
						int PlayerNumber = selectPlayer(window);
						if (PlayerNumber >= 0 && PlayerNumber < 5) {
							sf::Texture tradeProperty;
							sf::Sprite tradePropertyLoad;
							tradeProperty.loadFromFile("Images\\subBox\\trade2.png");
							tradePropertyLoad.setTexture(tradeProperty);
							tradePropertyLoad.setPosition(135, 120);
							bool ok = false;
							int landId = -5;
							while (!ok) {
								window.draw(tradePropertyLoad);
								window.display();
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed) {
										window.close();
									}

									else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
										std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
										if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
											landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
										}
										if (landId > -3 && event.mouseButton.y > 483 && event.mouseButton.y < 516 && event.mouseButton.x > 440 && event.mouseButton.x < 492) { // sale Property
											sf::Texture agrement;
											sf::Sprite agrementLoad;
											agrement.loadFromFile("Images\\subBox\\TradeAgreeMent.png");
											agrementLoad.setTexture(agrement);
											agrementLoad.setPosition(225, 225);
											window.draw(agrementLoad);
											window.display();
											if (p[PlayerNumber].getOwner(landId) != -2) {
												bool fine = false;
												while (!fine) {
													window.draw(agrementLoad);
													window.display();
													while (window.pollEvent(event)) {
														if (event.type == sf::Event::Closed) {
															window.close();
														}
														else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
															std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
															if (event.mouseButton.y > 375 && event.mouseButton.y < 405 && event.mouseButton.x > 387 && event.mouseButton.x < 413) {
																if (operation == 0) {
																	p[PlayerNumber].removeOwner(landId);
																	p[PlayerNumber].increaseMoney(amount);
																	p[turn].setOwner(landId);
																	p[turn].decreaseMoney(amount);
																	land[landId].setOwner(turn);
																}
																else {
																	p[PlayerNumber].removeOwner(landId);
																	p[PlayerNumber].setOwner(landNumber);
																	pro[landNumber].setOwner(PlayerNumber);
																	p[turn].removeOwner(landNumber);
																	p[turn].setOwner(landId);
																	pro[landId].setOwner(turn);
																}
																fine = true;
																ok = true;
															}
															else if (event.mouseButton.y > 375 && event.mouseButton.y < 405 && event.mouseButton.x > 240 && event.mouseButton.x < 267) {
																fine = true;
																ok = true;
															}

														}
													}
												}
											}
											else if (landId == -2) {
												bool ok = false;
												sf::Texture alert;
												sf::Sprite alertLoad;
												alert.loadFromFile("Images\\subBox\\mortageAlert.png");
												alertLoad.setTexture(alert);
												alertLoad.setPosition(225, 225);
												while (!ok) {
													while (window.pollEvent(event)) {
														if (event.type == sf::Event::Closed) {
															window.close();
														}
														else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
															if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
																ok = true;
															}
														}
														window.draw(alertLoad);
														window.display();
													}
												}
											}

										}
										else if (event.mouseButton.x > 159 && event.mouseButton.x < 244 && event.mouseButton.y>478 && event.mouseButton.y < 510) {
											ok = true;
										}
									}
								}

							}
						}


					}
				}
				
			}
		}
	}
	sf::Texture Trade;
}

//when user select a propert for buil an thing it will check how many propert are in the same block
int Monopoly::searchTotalBlockInProperty(property *p,const char*t) {//find how many property are in a block of property
	int block = 0;
	for (int i = 0; i < 40; i++){
		if (p[i].getGroup() != NULL) {
			const char* temp = p[i].getGroup();
			if (!strcmp(temp, t)) {
				block++;
			}
		}
	}
	return block;
}

//after counting property of a block it will count how many propert exist under his ownership
int Monopoly::searchTotalBlockInplayer(int *p, int block) {// search how many propert of same block exist in sam eblock
	int size = 0;
	int numberPresent = 0; 
	for (int i = 0; p[i] != -2; i++) {
		size++;
	}

	for (int i = 0; i < size; i++) {
		if (block == p[i]) {
			numberPresent++;
		}
	}
	return numberPresent;
}

//select user want to trade with whic player
int Monopoly::buildopetionSelector(int x, int y) { // select what user want to build;
	fstream fin;
	fin.open("Build Button.txt");

	int start[2][6];
	int end[2][6];
	int index = 0;
	while (index < 6) {
		fin >> start[0][index];
		fin >> start[1][index];
		fin >> end[0][index];
		fin >> end[1][index];
		index++;
	}
	for (int i = 0; i < 8; i++) {
		if (x > start[0][i] && x < end[0][i]) {
			if (y > start[1][i] && y < end[1][i]) {
				return i;
			}
		}
	}
	return -5;
} 

//draw buil box means here we can select which kind of building we can buil on a certain property eg(hotel, house, shope , wifi etc)
int Monopoly::drawBuildBox(sf::RenderWindow &window, sf::Sprite b){//draw GUI select user what wnat to build on specific property
	sf::Texture button;
	sf::Sprite buttonLOad;
	sf::Texture subButton[6];
	sf::Sprite subButtonLoad[6];

	subButton[0].loadFromFile("Images\\subBox\\s0.png");
	subButton[1].loadFromFile("Images\\subBox\\s1.png");
	subButton[2].loadFromFile("Images\\subBox\\s2.png");
	subButton[3].loadFromFile("Images\\subBox\\s3.png");
	subButton[4].loadFromFile("Images\\subBox\\s4.png");
	subButton[5].loadFromFile("Images\\subBox\\s5.png");
	
	int x = 215;
	int y = 201;
	
	for (int i = 0; i < 6; i++) {
		subButtonLoad[i].setTexture(subButton[i]);
		subButtonLoad[i].setPosition(x, y);
		y += 46;
	}

	button.loadFromFile("Images\\subBox\\buildItems.png");
	buttonLOad.setTexture(button);
	buttonLOad.setPosition(135,120);
	bool cancel = false;
	int opetion = -5;
	while (!cancel) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				cout << event.mouseButton.x << " , " << event.mouseButton.y<<endl;
				/*165  485	203  513
				  441  483	477  515
				*/
				if (event.mouseButton.y > 485 && event.mouseButton.y < 515) {
					if (event.mouseButton.x > 441 && event.mouseButton.x < 477 && opetion != -5) {
						return opetion;
					}
					if (event.mouseButton.x > 165 && event.mouseButton.x < 203) {
						cancel = true;
					}
				}
				else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
					opetion = buildopetionSelector(event.mouseButton.x, event.mouseButton.y);
				}
			}
			window.draw(b);
			window.draw(buttonLOad);
			if (opetion != -5) {
				window.draw(subButtonLoad[opetion]);
			}
			window.display();

		}
	}

} 

//it will build proerty that user select from the upper function
void Monopoly::build(player *p, property *pro, sf::RenderWindow &window, sf::Sprite button) {
	window.draw(button);
	window.display();
	sf::Texture build;
	sf::Sprite buildLoad;
	build.loadFromFile("Images\\subBox\\buildHouse.png");
	buildLoad.setTexture(build);
	sf::Texture buildbuildButton;
	sf::Sprite buildbuildButtonLoad;
	buildbuildButton.loadFromFile("Images\\subBox\\buildbuildButton.png");
	buildbuildButtonLoad.setTexture(buildbuildButton);
	buildbuildButtonLoad.setPosition(403, 474);
	buildLoad.setPosition(135, 120);
	bool isCancel = false;
	int landId = 0;
	while (!isCancel) {
		window.draw(buildLoad);
		window.draw(button);
		window.display();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << event.mouseButton.x << "  " << event.mouseButton.y << endl;
				if (event.mouseButton.y > 186 && event.mouseButton.y < 461 && event.mouseButton.x > 151 && event.mouseButton.x < 501) {
					landId = PropertySelected(event.mouseButton.x, event.mouseButton.y);
				}
				if (landId > -3 && event.mouseButton.y > 478 && event.mouseButton.y < 509 && event.mouseButton.x > 407 && event.mouseButton.x < 492) { // sale Property
					window.draw(buildbuildButtonLoad);
					window.display();
					if (p[turn].getOwner(landId) != -2) {
						int numberPresent = searchTotalBlockInplayer(p[turn].getownerArray(),landId);
						int totalProperty = searchTotalBlockInProperty(pro, pro[landId].getGroup());
						if (totalProperty == numberPresent && pro[landId].getUpgradeStatus()&& !pro[landId].getMortage()){
							int opetion = drawBuildBox(window,button);
							land[landId].UpdateProperty(p, opetion);
						}
						else {
							bool ok = false;
							sf::Texture alert;
							sf::Sprite alertLoad;
							if (!pro[landId].getUpgradeStatus()) {
								alert.loadFromFile("Images\\subBox\\buildPropertyUnUpgraded.png");
							}
							else if (pro[landId].getMortage()) {
								alert.loadFromFile("Images\\subBox\\mortageupgrade.png"); 
							}
							else{
								alert.loadFromFile("Images\\subBox\\Alert.png");
							}
							alertLoad.setTexture(alert);
							alertLoad.setPosition(225, 225);
							while (!ok) {
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed) {
										window.close();
									}
									else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
										if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
											ok = true;
										}
									}
									window.draw(alertLoad);
									window.draw(buildbuildButtonLoad);
									window.display();
								}
							}
						}
					}
					else {
						bool ok = false;
						sf::Texture alert;
						sf::Sprite alertLoad;
						alert.loadFromFile("Images\\subBox\\mortageAlert.png");
						alertLoad.setTexture(alert);
						alertLoad.setPosition(225, 225);
						while (!ok) {
							while (window.pollEvent(event)) {
								if (event.type == sf::Event::Closed) {
									window.close();
								}
								else if (sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
									if (event.mouseButton.x > 286 && event.mouseButton.x < 366 && event.mouseButton.y>381 && event.mouseButton.y < 407) {
										ok = true;
									}
								}
								window.draw(alertLoad);
								window.draw(buildbuildButtonLoad);
								window.display();
							}
						}
					}
				}
				else if (event.mouseButton.y > 484 && event.mouseButton.y < 502 && event.mouseButton.x > 161 && event.mouseButton.x < 243) {
					isCancel = true;
				}

			}
		}
	}
}

// draw monopoly board, dice,player position, etc
void Monopoly::drawBoard(int loadFromFile,bool isCancel) {
	int inJail = 0;
	if (!isCancel) {
		dice d;
		CommunityChest c;
		chance ch;
	
		if (loadFromFile) {
			p = new player[totalPlayer];
			for (int i = 0; i < totalPlayer; i++) {
				p[i].setPlayerNumber(i);
				p[i].setMoney(money);
			}
		}
		sf::RenderWindow window(sf::VideoMode(800, 650), "Monopoly", sf::Style::Titlebar | sf::Style::Close);
		window.setKeyRepeatEnabled(false);

		sf::Texture board;
		sf::Texture Dice[2];
		sf::Texture community;
		sf::Texture chancePic;
		sf::Texture pointer;
		sf::Texture *symbol;
		sf::Texture *currentPlayer;
		symbol = new sf::Texture[totalPlayer];
		currentPlayer = new sf::Texture[totalPlayer];

		sf::String *sentence = new sf::String[totalPlayer];
		sf::Font font;
		font.loadFromFile("font\\Gabriola.ttf");
		sf::String se;
		sf::Uint32 **zz = new sf::Uint32*[totalPlayer];
		sf::Uint32 zzz[20];
		for (int i = 0; i < totalPlayer; i++) {
			zz[i] = new sf::Uint32[30];
		}
		sf::Text *text = new sf::Text[totalPlayer];
		sf::Text zzztext(" ", font, 40);
		sf::Text t(" ", font, 30);
		sf::Color color(249, 154, 64);
		text->setFillColor(color);
		zzztext.setPosition(660, 60);

		int tx = 670;
		int ty = 150;
		for (int i = 0; i < totalPlayer; i++) {
			text[i] = t;
			char *temp = intToCharArray(money);
			for (int j = 0; temp[j] != '\0'; j++) {
				zz[i][j] = temp[j];
			}
			for (int j = 0; j < moneySize; j++) {
				sentence[i] += zz[i][j];
			}
			text[i].setFillColor(color);
			text[i].setPosition(tx, ty);
			ty += 50;
		}
		sf::Sprite boardLoad;
		sf::Sprite DiceLoad[2];
		sf::Sprite communityLoad;
		sf::Sprite chanceLoad;
		sf::Sprite pointerLoad;
		sf::Sprite *symbolLoad;
		sf::Sprite *currentPlayerLoad;

		symbolLoad = new sf::Sprite[totalPlayer];
		currentPlayerLoad = new sf::Sprite[totalPlayer];
		int x = 725;
		int y = 150;
		for (int i = 0; i < totalPlayer; i++) {
			currentPlayer[i].loadFromFile(p[i].getPicture());
			currentPlayerLoad[i].setTexture(currentPlayer[i]);
			currentPlayerLoad[i].setPosition(x, y);
			y += 50;
		}
		board.loadFromFile("Images\\main board\\Monopoly.jpg");
		Dice[0].loadFromFile("Images\\Dice\\dice1.png");
		Dice[1].loadFromFile("Images\\Dice\\dice5.png");
		chancePic.loadFromFile("Images\\Chance\\chanceTemplate 0.jpg");
		community.loadFromFile("Images\\Community Chest\\communityTemplate 0.jpg");
		pointer.loadFromFile("Images\\subBox\\point.png");
		for (int i = 0; i < totalPlayer; i++) {
			symbol[i].loadFromFile(p[i].getPicture());
		}


		DiceLoad[0].setTexture(Dice[0]);
		DiceLoad[1].setTexture(Dice[1]);
		boardLoad.setTexture(board);
		communityLoad.setTexture(community);
		chanceLoad.setTexture(chancePic);
		pointerLoad.setTexture(pointer);
		if (turn == 0) {
			pointerLoad.setPosition(770, 160);
		}
		else if (turn == 1) {
			pointerLoad.setPosition(770, 160 + 55);
		}
		else if (turn == 2) {
			pointerLoad.setPosition(770, 160 + 110);
		}
		else if (turn == 3) {
			pointerLoad.setPosition(770, 160 + 155);
		}
		else if (turn == 4) {
			pointerLoad.setPosition(770, 160 + 210);
		}

		for (int i = 0; i < totalPlayer; i++) {
			symbolLoad[i].setTexture(symbol[i]);
		}

		chanceLoad.setPosition(325, 400);
		communityLoad.setPosition(130, 130);

		for (int i = 0; i < totalPlayer; i++) {
			symbolLoad[i].setPosition(p[i].getX(), p[i].getY());
		}
		DiceLoad[0].setPosition(390, 210);
		DiceLoad[1].setPosition(220, 350);
		int a = 0;
		LoadPropertyImage(land);
		for (int i = 0; i < 40; i++) {
			window.draw(proLoad[i]);
			window.display();
		}
		window.draw(boardLoad);
		window.draw(DiceLoad[0]);
		window.draw(DiceLoad[1]);
		window.draw(communityLoad);
		window.draw(chanceLoad);

		for (int i = 0; i < totalPlayer; i++) {
			window.draw(symbolLoad[i]);
			window.draw(currentPlayerLoad[i]);
			text[i].setString(sentence[i]);
			window.draw(text[i]);
		}
		window.draw(pointerLoad);
		float position = 0;

		window.display();
		while (window.isOpen()) {
			window.draw(boardLoad);
			window.draw(DiceLoad[0]);
			window.draw(DiceLoad[1]);
			window.draw(communityLoad);
			window.draw(chanceLoad);
			for (int i = 0; i < totalPlayer; i++) {
				window.draw(symbolLoad[i]);
				window.draw(currentPlayerLoad[i]);
				text[i].setString(sentence[i]);
				window.draw(text[i]);
			}
			LoadPropertyImage(land);
			for (int i = 0; i < 40; i++) {
				window.draw(proLoad[i]);
			}
			window.draw(pointerLoad);
			window.display();
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed || isCancel) {
					window.close();
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::R) { // scrool dice and update player position
					
						d.setDise();
						Dice[0].loadFromFile(d.getDicePicture(d.getFirstNumber()));
						Dice[1].loadFromFile(d.getDicePicture(d.getSecondNumber()));
						DiceLoad[0].setTexture(Dice[0]);
						DiceLoad[1].setTexture(Dice[1]);
						DiceLoad[0].setPosition(390, 210);
						DiceLoad[1].setPosition(220, 350);
						int d1 = d.getFirstNumber();
						int d2 = d.getSecondNumber();
						p[turn].setPosition(d1+d2,window, symbolLoad ,turn, totalPlayer, DiceLoad[0], DiceLoad[1], boardLoad, text, pointerLoad, currentPlayerLoad);

						symbolLoad[turn].setPosition(p[turn].getX(), p[turn].getY());
						
						if (p[turn].getPosition() == 2 || p[turn].getPosition() == 17 || p[turn].getPosition() == 33) {
							community.loadFromFile(c.getCommunityPic());
							communityLoad.setTexture(community);
							communityLoad.setPosition(130, 130);
							c.comunityCardAction(p[turn], c.getCardNumber());
						}
						if (p[turn].getPosition() == 30) {
							p[turn].setPositionUnconditionally(10);
							if (1) {
								p[turn].decreaseMoney(200);
							}
							else {
								int c = p[turn].turn;
								c--;
								p[turn].turn--;
							}
						}
						if (p[turn].getPosition() == 7 || p[turn].getPosition() == 22 || p[turn].getPosition() == 36) {
							chancePic.loadFromFile(ch.getChancePic());
							chanceLoad.setTexture(chancePic);
							chanceLoad.setPosition(325, 400);
							ch.chanceCardAction(p, turn, totalPlayer);
						}
						symbolLoad[turn].setPosition(p[turn].getX(), p[turn].getY());
						PropertyRentAction(p, turn);
						if (p[turn].getMoney() <= 0) {
							p[turn].setRetire(1);
						}
						for (int i = 0; i < totalPlayer; i++) {
							sentence[i].erase(sentence[i].getSize() - sentence[i].getSize(), sentence[i].getSize());
						}
						for (int i = 0; i < totalPlayer; i++) {
							char *temp = intToCharArray(p[i].getMoney());
							int size = 0;
							for (int j = 0; temp[j] != '\0'; j++) {
								zz[i][j] = temp[j];
								size++;
							}
							if (p[i].getRetire()) {
								size++;
								zz[i][0] = 48;
							}
							for (int j = 0; j < size; j++) {
								sentence[i] += zz[i][j];
							}
						}

						if (land[p[turn].getPosition()].getBuyStatus() && (land[p[turn].getPosition()].getOwner() == -1)) {
							bool done = false;
							bool notPurchase = false;
							int place = p[turn].getPosition();
							while (!done) {
								sf::Texture purches;
								sf::Sprite purchesLoad;
								purches.loadFromFile("Images\\subBox\\purchase.png");
								purchesLoad.setTexture(purches);
								purchesLoad.setPosition(225, 225);
								while (window.pollEvent(event)) {
									if (event.type == sf::Event::Closed || isCancel) {
										window.close();
									}
									if (sf::Event::MouseButtonPressed) {
										if (event.mouseButton.button == sf::Mouse::Left) {
											if (event.mouseButton.x > 277 && event.mouseButton.x < 372) {
												if (event.mouseButton.y > 305 && event.mouseButton.y < 324) {
													done = true;
													propertyBuyAction(p, turn);
													if (p[turn].getMoney() <= 0) {
														p[turn].setRetire(1);
													}
													for (int i = 0; i < totalPlayer; i++) {
														sentence[i].erase(sentence[i].getSize() - sentence[i].getSize(), sentence[i].getSize());
													}
													for (int i = 0; i < totalPlayer; i++) {
														char *temp = intToCharArray(p[i].getMoney());
														int size = 0;
														for (int j = 0; temp[j] != '\0'; j++) {
															zz[i][j] = temp[j];
															size++;
														}
														if (p[i].getRetire()) {
															size++;
															zz[i][0] = 48;
														}
														for (int j = 0; j < size; j++) {
															sentence[i] += zz[i][j];
														}
													}

												}
												else if (event.mouseButton.y > 360 && event.mouseButton.y < 375) {
													int number = 0;
													int cancel[5];

													sf::Texture play;
													sf::Sprite playLoad;

													int bitTurn = turn;
													int addNUmber = 0;
													int lastMoney = 0;
													int index = 0;
													cancel[0] = -1;

													while (index != totalPlayer - 1) {
														int number = 0;
														done = false;
														while (!done) {
															
															purches.loadFromFile("Images\\subBox\\calculator.png");
															if (bitTurn >= 5) {
																bitTurn = 0;
															}
															play.loadFromFile(p[bitTurn].getPicture());
															playLoad.setTexture(play);
															purchesLoad.setTexture(purches);
															purchesLoad.setPosition(225, 225);
															playLoad.setPosition(230, 225);
															while (window.pollEvent(event)) {
																if (event.type == sf::Event::Closed || isCancel) {
																	window.close();
																}
																if (sf::Event::MouseButtonPressed) {
																	if (event.mouseButton.button == sf::Mouse::Left) {
																		if (addNUmber % 2 == 0) {
																			p[bitTurn].selestMoneyFromCalculator(event.mouseButton.x, event.mouseButton.y, number);
																		}
																		else if (event.mouseButton.y > 389 && event.mouseButton.y < 412) {
																			if (event.mouseButton.x > 250 && event.mouseButton.x < 282) {
																				p[bitTurn].setbitCancel(1);
																				bitTurn++;
																				done = true;
																				index++;
																			}
																			else if (event.mouseButton.x > 376 && event.mouseButton.x < 408) {

																				if (lastMoney < number) {
																					lastMoney = number;
																					done = true;
																					bitTurn++;
																					if (bitTurn >= totalPlayer) {
																						bitTurn = 0;
																					}
																					for (int i = 0; i < totalPlayer; i++) {
																						if (p[bitTurn].getbitCancel()) {
																							bitTurn++;
																							if (bitTurn >= totalPlayer) {
																								bitTurn = 0;
																							}
																						}
																						else {
																							i = totalPlayer;
																						}
																					}
																				}
																				se.erase(se.getSize() - se.getSize(), se.getSize());
																				se[0];
																				int size = 0;
																				char *temp = intToCharArray(lastMoney);
																				for (int j = 0; temp[j] != '\0'; j++) {
																					zzz[j] = temp[j];
																					size++;
																				}
																				for (int j = 0; j < size; j++) {
																					se += zzz[j];
																				}
																				zzztext.setFillColor(color);
																				zzztext.setString(se);
																			}
																		}
																		addNUmber++;
																	}
																}
															}
															sf::Texture bitMoney;
															bitMoney.loadFromFile("Images\\subBox\\bitMoney.png");
															sf::Sprite bitMoneyLoad;
															bitMoneyLoad.setTexture(bitMoney);
															bitMoneyLoad.setPosition(650, 60);

															window.draw(bitMoneyLoad);
															window.draw(purchesLoad);
															window.draw(playLoad);
															zzztext.setString(se);
															window.draw(zzztext);
															window.display();
														}
													}

													for (int i = 0; i < totalPlayer; i++) {
														if (!p[i].getbitCancel()) {
															p[i].decreaseMoney(lastMoney);
															int landId = land[place].getPropertyId();
															p[i].setOwner(landId);
															land[place].setOwner(i);
														}
													}
													if (p[turn].getMoney() <= 0) {
														p[turn].setRetire(1);
													}
													for (int i = 0; i < totalPlayer; i++) {
														sentence[i].erase(sentence[i].getSize() - sentence[i].getSize(), sentence[i].getSize());
													}
													for (int i = 0; i < totalPlayer; i++) {
														char *temp = intToCharArray(p[i].getMoney());
														int size = 0;
														for (int j = 0; temp[j] != '\0'; j++) {
															zz[i][j] = temp[j];
															size++;
														}
														if (p[i].getRetire()) {
															size++;
															zz[i][0] = 48;
														}
														for (int j = 0; j < size; j++) {
															sentence[i] += zz[i][j];
														}
													}
													for (int i = 0; i < totalPlayer; i++) {
														p[i].setbitCancel(0);
													}


												}
											}
										}

									}
									//goto;

									window.draw(purchesLoad);
									window.draw(purchesLoad);
									window.display();
									//	if (event.key.code == sf::Keyboard::R) {
								}
							}
						}

						assignProperty(p, p[turn].getPosition(), turn);
						if (d.getFirstNumber() != d.getSecondNumber()) {
							UpdateTurn(p);

							if (turn == 0) {
								pointerLoad.setPosition(770, 160);
							}
							else if (turn == 1) {
								pointerLoad.setPosition(770, 160 + 55);
							}
							else if (turn == 2) {
								pointerLoad.setPosition(770, 160 + 110);
							}
							else if (turn == 3) {
								pointerLoad.setPosition(770, 160 + 155);
							}
							else if (turn == 4) {
								pointerLoad.setPosition(770, 160 + 210);
							}
						}
					}
				}
				sf::Texture *button = new sf::Texture[4];
				sf::Sprite *buttonLoad = new sf::Sprite[4];
				button[0].loadFromFile("Images\\subBox\\trade.png");
				button[1].loadFromFile("Images\\subBox\\build.png");
				button[2].loadFromFile("Images\\subBox\\sale.png");
				button[3].loadFromFile("Images\\subBox\\debt.png");
				int bx = 664;

				for (int i = 0; i < 4; i++) {
					buttonLoad[i].setTexture(button[i]);

				}
				buttonLoad[0].setPosition(bx, 413);
				buttonLoad[1].setPosition(bx, 469);
				buttonLoad[2].setPosition(bx, 528);
				buttonLoad[3].setPosition(bx, 588);

				if (sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (event.mouseButton.x > 665 && event.mouseButton.x < 780) {
							if (event.mouseButton.y > 420 && event.mouseButton.y < 465) {
								TradeWithMoney(p, land, window, buttonLoad[0]);
							}
							else if (event.mouseButton.y > 480 && event.mouseButton.y < 525) {
								build(p, land, window, buttonLoad[1]);
							}
							else if (event.mouseButton.y > 535 && event.mouseButton.y < 580) { // 3rd bottom  right Button
								sale(p, land, window, buttonLoad[2]);
							}
							else if (event.mouseButton.y > 590 && event.mouseButton.y < 640) { // 4th right bottom button
								Mortage(p, land, window, buttonLoad[3]);
							}
						}
					}
				}
			}
			window.draw(boardLoad);
			window.draw(DiceLoad[0]);
			window.draw(DiceLoad[1]);
			window.draw(communityLoad);
			window.draw(chanceLoad);
			LoadPropertyImage(land);
			for (int i = 0; i < 40; i++) {
				window.draw(proLoad[i]);
			}
			for (int i = 0; i < totalPlayer; i++) {
				window.draw(symbolLoad[i]);
				window.draw(currentPlayerLoad[i]);
				text[i].setString(sentence[i]);
				window.draw(text[i]);
			}
			window.draw(pointerLoad);
			window.display();
		}
	}
}

//save current state in file automatically when user exist game
ofstream& operator << (ofstream& fout, Monopoly& M) {
	fout.open("Data\\MonopolyProperty.txt");
	fout << M.turn;
	fout << "\n";
	fout << M.totalPlayer;
	fout << "\n";
	for (int i = 0; i < 40; i++) {
		fout << M.land[i];
		fout << endl;
	}
	fout.close();
	fout.open("Data\\player.txt");
	for (int i = 0; i < M.totalPlayer; i++) {
		fout << M.p[i];
		fout << endl;
	}
	fout.close();
	return fout;
}

//load game when user don't want to run new game 
ifstream& operator >>(ifstream&fin, Monopoly& m) {
	fin.open("Data\\MonopolyProperty.txt");
	fin >> m.turn;
	fin >> m.totalPlayer;
	for (int i = 0; i < 40; i++) {
		fin >> m.land[i];
	}
	fin.close();
	m.p = new player[m.totalPlayer];
	fin.open("Data\\player.txt");
	for (int i = 0; i < m.totalPlayer; i++) {
		fin >> m.p[i];
	}
	fin.close();
	return fin;
}

//decide which player lost the game
void Monopoly::decision(player *p, property * pro, sf::RenderWindow &window, sf::Sprite button) {
	int size = 0;
	for (int i = 0; i < 40; i++) {
		if (p[turn].getOwner(i) != -2) {
			size++;
		}
	}
	int size2 = 0;
	
	
	while(p[turn].getMoney() <= 0) {
		for (int i = 0; i < 40; i++) {
			if (pro[i].getMortage()) {
				size2++;
			}
		}
		Mortage(p, pro, window,button);
		if (p[turn].getMoney() <= 0 && size == size2) {
			p[turn].setRetire(1); 
		}
	}
}


Monopoly::~Monopoly() {

}
#endif // !Monopoly_H

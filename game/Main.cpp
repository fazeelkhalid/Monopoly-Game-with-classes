#include<iostream>
#include"Monopoly.h"
#include<fstream>


int main(){
	CommunityChest c;
	Monopoly M;
	sf::Texture saveScreen;
	sf::Sprite saveScreenLoad;
	saveScreen.loadFromFile("Images\\subBox\\money0.png");
	saveScreenLoad.setTexture(saveScreen);
	sf::RenderWindow selectPlayerWindow(sf::VideoMode(800, 650), "Monopoly", sf::Style::Titlebar | sf::Style::Close);
	selectPlayerWindow.setKeyRepeatEnabled(false);
	sf::Event event;
	bool isSelect = false;
	bool isCancel = false;
	while (selectPlayerWindow.isOpen()) {
		selectPlayerWindow.draw(saveScreenLoad);
		selectPlayerWindow.display();
		while (selectPlayerWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				selectPlayerWindow.close();
				isCancel = true;
			}
			else if (sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (event.mouseButton.x > 287 && event.mouseButton.x < 492) {
						if (event.mouseButton.y > 272 && event.mouseButton.y < 329) {
							selectPlayerWindow.close();
							ofstream fout;
							isCancel = M.SelectPlayer(isCancel);
							M.SelectMoney(isCancel);
							M.drawBoard(1, isCancel);
							fout << M;
						}
						else if (event.mouseButton.y > 377 && event.mouseButton.y < 430) {
							selectPlayerWindow.close();
							ifstream fin;
							ofstream fout;
							fin>>M;
							M.drawBoard(0, isCancel);
							fout << M;
						}
					}
				}
				
			}
		}
	}

	return 0;
}
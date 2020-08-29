#pragma once
#include<SFML/Graphics.hpp>
#include"property.h"
#include"player.h"

class build {
protected:
	int houseNumber;
	int Houses;
	bool shopes;
	bool hotels;
	bool wifi;
	bool gasConnection;
	bool Electricity;
	int houseBuy;
	int shopeBuy;
	int hotelsBuy;
	int wifiBuy;
	int GasConnectionbuy;
	int ElectricityBuy;
	int houseIncreseRent;
	int shopeIncreseRent;
	int hotelIncreseRent;
	int wifiIncreseRent;
	int gasConnectionIncreseRent;
	int electricityIncreseRent;
public:
	build();
	virtual void UpdateProperty(player *p,int opetion) = 0;
	int getHouses();
	int getshopes();
	int getHotels();
	int getWifi();
	int getgasConnection();
	int getElectricity();

};
build::build() {
	houseNumber = 0;
	Houses = 0;
	shopes = 0;
	hotels = 0;
	wifi = 0;
	gasConnection = 0;
	Electricity = 0;
	houseBuy = 100;
	shopeBuy = 300 ;
	hotelsBuy = 400;
	wifiBuy = 30;
	GasConnectionbuy = 50;
	ElectricityBuy = 50;
	houseIncreseRent = 30;
	shopeIncreseRent = 60;
	hotelIncreseRent = 80;
	wifiIncreseRent = 10;
	gasConnectionIncreseRent = 20;
	electricityIncreseRent = 20;
}
int build::getHouses() {
	return Houses;
}
int build::getshopes() {
	return shopes;
}
int build::getHotels(){
	return hotels;
}
int build::getWifi() {
	return wifi;
}
int build::getgasConnection() {
	return gasConnection;
}
int build::getElectricity() {
	return Electricity;
}


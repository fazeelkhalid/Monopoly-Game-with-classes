#ifndef property_H
#define property_H
#include<string.h>
#include<iostream>
#include"Build.h"
#include"player.h"

class property:public build {
private:
	int owner; // decide ownner of the property
	char *group; // store property group
	int propertyId; //set propertyid
	int rent;
	bool upgradeStatus;
	bool buyStatus;
	bool Mortage;
	int salePrice;
public:
	property() {
		Mortage = 0;
		owner = -1;
		propertyId = 0;
		rent = 0;
		group = NULL;
		upgradeStatus = false;
		buyStatus = false;
		salePrice = 0;
	}

	property(int p) {
		propertyId = p;
	}

	void setOwner(int);
	void setRent(int);
	void setPropertyId(int);
	void setSalePrice(int);
	void setUpgradeStatus(bool,bool);
	void setGroup(const char*);
	void setMortage(bool);
	void UpdateProperty(player *p, int opetion);

	char* getGroup();
	int getOwner();
	int getPropertyId();
	bool getMortage();
	int getRent();
	int getUpgradeStatus();
	int getBuyStatus();
	int getSalePrice();
	friend ofstream& operator<<(ofstream& fout, property& p);
	friend ifstream& operator>>(ifstream& fin, property& p);
};

bool property::getMortage() {
	return Mortage;
}
void property::setMortage(bool m) {
	Mortage = m;
}
void property::setUpgradeStatus(bool u, bool b) {
	upgradeStatus = u;
	buyStatus = b;
}
void property::setGroup(const char *g) {
	int size = strlen(g);
	group = new char[size + 1];
	strcpy_s(group, size+1, g);
	group[size] = '\0';
}
void property::setOwner(int o) {
	owner = o;
}
void property::setPropertyId(int p) {
	propertyId = p;
}
void property::setRent(int r) {
	rent = r;
}
void property::setSalePrice(int s) {
	salePrice = s;
}
char* property::getGroup() {
	return group;
}
int property::getOwner() {
	return owner;
}
int property::getPropertyId() {
	return propertyId;
}
int property::getRent() {
	return rent;
}
int property::getUpgradeStatus() {
	return upgradeStatus;
}
int property::getBuyStatus() {
	return buyStatus;
}
int property::getSalePrice() {
	return salePrice;
}



void property::UpdateProperty(player*p, int opetion) { // perform operation according to build operation decrease Money etc
	if (opetion == 0 && Houses < 4 && p[owner].getMoney()>=100) {
			p[propertyId].decreaseMoney(houseBuy);
			Houses++;
			rent += (rent * houseIncreseRent) / 100;
			salePrice += (salePrice * houseIncreseRent) / 100;
	}
	else if (opetion == 1 && Houses == 3 && p[owner].getMoney() > 300) {
		Houses -= 3;
		p[propertyId].decreaseMoney(shopeBuy);
		shopes += 1;
		rent += (rent * shopeIncreseRent) / 100;
		salePrice += (salePrice * shopeIncreseRent) / 100;
	}
	else if (opetion == 2 && p[owner].getMoney() >= 400 && Houses == 4) {
		Houses -= 4;
		p[propertyId].decreaseMoney(hotelsBuy);
		hotels = 1;
		rent += (rent * hotelIncreseRent) / 100;
		salePrice += (salePrice * hotelIncreseRent) / 100;
	} 
	else if (opetion == 3 && p[owner].getMoney() >= 400) {
		p[propertyId].decreaseMoney(wifiBuy);
		wifi = 1;
		rent += (rent * wifiIncreseRent) / 100;
		salePrice += (salePrice * wifiIncreseRent) / 100;
	}
	else if (opetion == 4 && p[owner].getMoney() >= 30) {
		p[propertyId].decreaseMoney(GasConnectionbuy);
		gasConnection = 1;
		rent += (rent * gasConnectionIncreseRent) / 50;
		salePrice += (salePrice * gasConnectionIncreseRent) / 100;
	}
	else if (opetion == 5 && p[owner].getMoney() >= 50) {
		p[propertyId].decreaseMoney(ElectricityBuy);
		Electricity = 1;
		rent += (rent * electricityIncreseRent) / 100;
		salePrice += (salePrice * electricityIncreseRent) / 100;
	}
}

ofstream& operator<<(ofstream& fout, property& p) {

	fout << p.propertyId;
	fout << "\t ";
	fout << p.owner;
	fout << "\t";
	fout << p.rent;
	fout << "\t";
	if (p.group != NULL) {
		fout << p.group;
	}
	fout << "\t";
	fout << p.upgradeStatus;
	fout << "\t";
	fout << p.buyStatus;
	fout << "\t";
	fout << p.Mortage;
	fout << "\t";
	fout << p.salePrice;
	fout << "\t";
	fout << p.Electricity;
	fout << "\t";
	fout << p.gasConnection;
	fout << "\t";
	fout << p.hotels;
	fout << "\t";
	fout << p.Houses;
	return fout;
}

ifstream& operator>>(ifstream& fin, property& p) {
	fin>> p.propertyId;
	fin >> p.owner;
	fin >>p.rent;
	if (p.group != NULL) {
		fin >> p.group;
	}
	fin >> p.upgradeStatus;
	fin >> p.buyStatus;
	fin >> p.Mortage;
	fin >> p.salePrice;
	fin >> p.Electricity;
	fin >> p.gasConnection;
	fin >> p.hotels;
	fin >> p.Houses;
	return fin;
}






/*
int owner; // decide ownner of the property
	char *group; // store property group
	int propertyId; //set propertyid
	int rent;
	bool upgradeStatus;
	bool buyStatus;
	bool Mortage;
	int salePrice;*/



#endif // !property_H

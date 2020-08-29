#ifndef Money_H
#define Money_H

class money {
private:
	int ammount;
public:
	money();
	void increaseMoney(int);
	void decreaseMoney(int);
	void setMoney(int);
	void selestMoneyFromCalculator(int x, int y, int&);
	int getMoney();
	~money();
};
void money::selestMoneyFromCalculator(int x, int y, int& number) {
	if (y > 281 && y < 301) {
		if (x > 263 && x < 287) {
			number = (number * 10) + 1;
		}
		else if (x > 315 && x < 339) {
			number = (number * 10) + 2;
		}
		else if (x > 367 && x < 393) {
			number = (number * 10) + 3;
		}
	}
	else if (y > 323 && y < 347) {
		if (x > 263 && x < 287) {
			number = (number * 10) + 4;
		}
		else if (x > 315 && x < 339) {
			number = (number * 10) + 5;
		}
		else if (x > 367 && x < 393) {
			number = (number * 10) + 6;
		}

	}
	else if (y > 359 && y < 381) {
		if (x > 263 && x < 287) {
			number = (number * 10) + 7;
		}
		else if (x > 315 && x < 339) {
			number = (number * 10) + 8;
		}
		else if (x > 367 && x < 393) {
			number = (number * 10) + 9;
		}
	}
	else if (x > 293 && x < 371) {
		if (y > 387 && y < 407) {
			number = (number * 10) + 0;

		}
	}
}


int money::getMoney() {
	return ammount;
}
money::money() {
	ammount = 0;
}
void money::increaseMoney(int m) {
	ammount += m;
}
void money::decreaseMoney(int m) {
	ammount -= m;
}
void money::setMoney(int m) {
	ammount = m;
}
money::~money() {

}


#endif // !Money_H

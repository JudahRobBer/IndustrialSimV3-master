#pragma once
#include <iostream>
#include <vector>

class Market
{
public:
	Market();
	~Market();

	void calculateNewPrices();
	void newTransaction(int, int);
	std::vector<int> getPrices();

private:
	std::vector<int> prices;
	int transactionTracker[4][2]; 


	enum RESOURCETYPE { COAL = 0, LUMBER, IRON, FISH };
	enum TRANSACTIONTYPE {BOUGHT = 0, SOLD};
};
#include "Market.h"

Market::Market()
{
	for (int a = 0; a < 4; a++)
	{
		prices.push_back(6);
		prices.push_back(4);
	}
}

Market::~Market()
{
}

//application of supply and demand principles to adjust price
void Market::calculateNewPrices()
{
	int bought, sold;
	
	for (int a = 0; a < 4; a++)
	{
		bought = transactionTracker[a][BOUGHT];
		sold = transactionTracker[a][SOLD];
		if (rand() % (bought + sold + 50) < sold && prices[a * 2 + 1] > 0)
		{
			prices[a * 2]--;
			prices[a * 2 + 1]--;
		}
		else if (rand() % (bought + sold + 50) > (sold + 50))
		{
			prices[a * 2]++;
			prices[a * 2 + 1]++;
		}

		else if (rand() % 5 == 1 && prices[a * 2] > 6) // Brings market back to normal levels
		{
			prices[a * 2]--;
			prices[a * 2 + 1]--;
		}
		else if (rand() % 5 == 1 && prices[a * 2 + 1] < 4) // Brings market back to normal levels
		{
			prices[a * 2]++;
			prices[a * 2 + 1]++;
		}
	}
	
	//Reset Monthly Transaction
	for (int c = 0; c < 4; c++)
	{
		transactionTracker[c][0] = 0;
		transactionTracker[c][1] = 0;
	}

}	

void Market::newTransaction(int type, int amount)
{
	transactionTracker[(type/3) % 4][type / 12] += amount;
	switch ((type / 3) % 4)
	{
	case 0:
		std::cout << "COAL\n";
		break;
	case 1:
		std::cout << "WOOD\n";
		break;
	case 2:
		std::cout << "IRON\n";
		break;
	case 3:
		std::cout << "FISH\n";
		break;

	}
}

std::vector<int> Market::getPrices()
{
	return prices;
}

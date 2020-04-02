#include <fstream>
#include <iostream>


using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("sortland.in", ios_base::in);
	output.open("sortland.out", ios_base::out);

	int population;
	input >> population;
	double residents[2][population];
	for (int j = 0; j < population; ++j)
	{
		input >> residents[0][j];
		residents[1][j] = j + 1;
	}

	for (int j = 0; j < population; ++j)
	{
		int k = j - 1;
		double moneyKey = residents[0][j];
		int numberKey = (int) residents[1][j];
		while (residents[0][k] > moneyKey && k >= 0)
		{
			residents[0][k + 1] = residents[0][k];
			residents[1][k + 1] = residents[1][k];
			--k;
		}
		residents[0][k + 1] = moneyKey;
		residents[1][k + 1] = (double) numberKey;
	}

	output << (int) residents[1][0] << " " << (int) residents[1][population / 2] << " "
		   << (int) residents[1][population - 1] << endl;


	input.close();
	output.close();
	return 0;
}

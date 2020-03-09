#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);

	int size;
	input >> size;
	int matrix[size][size];
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			input >> matrix[i][j];
		}
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (matrix[i][j] == 1 && matrix[j][i] != 1)
			{
				output << "NO";
				return 0;
			}
			if (i == j && matrix[i][j] == 1)
			{
				output << "NO";
				return 0;
			}
		}
	}
	output << "YES";

	input.close();
	output.close();
	return 0;
}

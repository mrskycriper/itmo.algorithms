#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);

	int numberOfNodes;
	int numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	int adjacencyMatrix[numberOfNodes][numberOfNodes];
	for (int i = 0; i < numberOfNodes; ++i)
	{
		for (int j = 0; j < numberOfNodes; ++j)
		{
			adjacencyMatrix[i][j] = 0;
		}
	}

	int row, column;
	for (int i = 0; i < numberOfEdges; ++i)
	{
		input >> row >> column;
		if (adjacencyMatrix[row - 1][column - 1] == 1)
		{
			output << "YES";
			return 0;
		}
		adjacencyMatrix[row - 1][column - 1] = 1;
	}

//	for (int i = 0; i < numberOfNodes; i++)
//	{
//		for (int j = 0; j < numberOfNodes; j++)
//		{
//			cout << adjacencyMatrix[i][j] << " ";
//		}
//		cout << endl;
//	}

	for (int i = 0; i < numberOfNodes; ++i)
	{
		for (int j = 0; j < numberOfNodes; ++j)
		{
			if (adjacencyMatrix[i][j] == 1 && adjacencyMatrix[j][i] == 1)
			{
				if (i != j)
				{
					output << "YES";
					return 0;
				}
			}
		}
	}
	output << "NO";

	input.close();
	output.close();
	return 0;
}

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
	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfNodes; j++)
		{
			adjacencyMatrix[i][j] = 0;
		}
	}

	int row, column;
	for (int k = 0; k < numberOfEdges; k++)
	{
		input >> row >> column;
		adjacencyMatrix[row - 1][column - 1] = 1;
	}

	for (int i = 0; i < numberOfNodes; i++)
	{
		for (int j = 0; j < numberOfNodes; j++)
		{
			output << adjacencyMatrix[i][j] << " ";
		}
		output << endl;
	}

	input.close();
	output.close();
	return 0;
}

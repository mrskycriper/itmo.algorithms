#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	vector <vector <int>> adjacencyList(numberOfNodes, vector <int>());
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int firstNode, secondNode;
		input >> firstNode >> secondNode;
		adjacencyList[firstNode - 1].push_back(secondNode);
		adjacencyList[secondNode - 1].push_back(firstNode);
	}

	for (int i = 0; i < numberOfNodes; ++i)
	{
		output << adjacencyList[i].size() << " ";
	}

	input.close();
	output.close();
	return 0;
}
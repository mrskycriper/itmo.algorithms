#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dfs(vector <vector <int>>& adjacencyList, vector <int>& components, const int& currentNode,
		 const int& currentComponentNumber)
{
	components[currentNode] = currentComponentNumber;
	for (int i = 0; i < adjacencyList[currentNode].size(); ++i)
	{
		if (components[adjacencyList[currentNode][i] - 1] == -1)
		{
			dfs(adjacencyList, components, adjacencyList[currentNode][i] - 1, currentComponentNumber);
		}
	}
}

void componentsSearch(int& currentComponentNumber, const int& numberOfNodes, vector <vector <int>>& adjacencyList,
					  vector <int>& components)
{
	for (int i = 0; i < numberOfNodes; ++i)
	{
		if (components[i] == -1 && adjacencyList[i].empty())
		{
			++currentComponentNumber;
			components[i] = currentComponentNumber;
			continue;
		}
		else if (components[i] == -1 && !adjacencyList[i].empty())
		{
			++currentComponentNumber;
			dfs(adjacencyList, components, i, currentComponentNumber);
		}
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("components.in", ios::in);
	output.open("components.out", ios::out);

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

//	for (int i = 0; i < numberOfNodes; ++i)
//	{
//		cout << i + 1 << ": ";
//		for (int j : adjacencyList[i])
//		{
//			cout << j << " ";
//		}
//		cout << "\n";
//	}

	vector <int> components(numberOfNodes, -1);
	int currentComponentNumber = 0;
	componentsSearch(currentComponentNumber, numberOfNodes, adjacencyList, components);

	output << currentComponentNumber << "\n";
	for (int i : components)
	{
		output << i << " ";
	}

	input.close();
	output.close();
	return 0;
}

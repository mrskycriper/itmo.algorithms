#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("pathbge1.in", ios::in);
	output.open("pathbge1.out", ios::out);

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

	vector <int> distance(numberOfNodes, 0);
	distance[0] = 0;
	vector <bool> visited(numberOfNodes, false);
	visited[0] = true;

	queue <int> connectedNodes;
	for (int i : adjacencyList[0])
	{
		visited[i - 1] = true;
		distance[i - 1] = 1;
		connectedNodes.push(i - 1);
	}

	while (!connectedNodes.empty())
	{
		visited[connectedNodes.front()] = true;
		for (int i = 0; i < adjacencyList[connectedNodes.front()].size(); ++i)
		{
			if (!visited[adjacencyList[connectedNodes.front()][i] - 1])
			{
				visited[adjacencyList[connectedNodes.front()][i] - 1] = true;
				distance[adjacencyList[connectedNodes.front()][i] - 1] = distance[connectedNodes.front()] + 1;
				connectedNodes.push(adjacencyList[connectedNodes.front()][i] - 1);
			}
		}
		connectedNodes.pop();
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

	for (int i : distance)
	{
		output << i << " ";
	}

	input.close();
	output.close();
	return 0;
}

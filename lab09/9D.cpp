#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

enum Colors
{
	WHITE = 0,
	GREY = 1,
	BLACK = -1,
};

void dfs(vector <vector <int>>& transposedGraph, const int& currentNode, vector <int>& colors, stack <int>& nodes)
{
	if (colors[currentNode] == WHITE)
	{
		colors[currentNode] = GREY;
		if (transposedGraph[currentNode].empty())
		{
			colors[currentNode] = BLACK;
			nodes.push(currentNode);
		}
		else
		{
			for (int i = 0; i < transposedGraph[currentNode].size(); ++i)
			{
				dfs(transposedGraph, transposedGraph[currentNode][i], colors, nodes);
			}
		}
		colors[currentNode] = BLACK;
		nodes.push(currentNode);

	}
	else if (colors[currentNode] == BLACK)
	{
		return;
	}
}

void
dfs(vector <vector <int>>& normalGraph, const int& currentNode, vector <int>& colors, const int& currentComponentNumber,
	vector <int>& componentNumber)
{
	if (colors[currentNode] == WHITE)
	{
		colors[currentNode] = GREY;
		if (normalGraph[currentNode].empty())
		{
			colors[currentNode] = BLACK;
			componentNumber[currentNode] = currentComponentNumber;
		}
		else
		{
			for (int i = 0; i < normalGraph[currentNode].size(); ++i)
			{
				dfs(normalGraph, normalGraph[currentNode][i], colors, currentComponentNumber, componentNumber);
			}
		}
		colors[currentNode] = BLACK;
		componentNumber[currentNode] = currentComponentNumber;
		cerr << currentNode + 1 << endl;
		cerr << "#" << endl;
	}
	else if (colors[currentNode] == BLACK)
	{
		return;
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("cond.in", ios_base::in);
	output.open("cond.out", ios_base::out);

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	vector <vector <int>> adjacencyList(numberOfNodes, vector <int>());
	vector <vector <int>> transposedAdjacencyList(numberOfNodes, vector <int>());
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int from, to;
		input >> from >> to;
		adjacencyList[from - 1].push_back(to - 1);
		transposedAdjacencyList[to - 1].push_back(from - 1);
	}

//	for (int i = 0; i < numberOfNodes; ++i)
//	{
//		cout << i + 1 << ": ";
//		for (int j : transposedAdjacencyList[i])
//		{
//			cout << j + 1 << " ";
//		}
//		cout << endl;
//	}

	vector <int> colors(numberOfNodes, WHITE);
	vector <bool> visited(numberOfNodes, false);
	vector <int> componentNumber(numberOfNodes);
	stack <int> nodes;
	int currentComponentNumber = 1;

	for (int i = 0; i < numberOfNodes; ++i)
	{
		dfs(transposedAdjacencyList, i, colors, nodes);
	}

	for (int i = 0; i < numberOfNodes; ++i)
	{
		colors[i] = WHITE;
	}

	while (!nodes.empty())
	{
		cerr << colors[nodes.top()] << endl;
		if (colors[nodes.top()] == WHITE)
		{
			dfs(adjacencyList, nodes.top(), colors, currentComponentNumber, componentNumber);
			++currentComponentNumber;

		}
		nodes.pop();
	}

	output << currentComponentNumber - 1 << endl;
	for (int i = 0; i < numberOfNodes; ++i)
	{
		output << currentComponentNumber - componentNumber[i] << " ";
	}
	input.close();
	output.close();
	return 0;
}

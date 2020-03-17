#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool dfs(vector <vector <int>>& adjacencyList, const int& currentNode, bool& bipartite, int color, vector <bool>& visited, vector <int>& colors)
{
	colors[currentNode] = color;
	visited[currentNode] = true;
	for (int i = 0; i < adjacencyList[currentNode].size(); ++i)
	{
		if (colors[adjacencyList[currentNode][i]] == 0)
		{
			if (!dfs(adjacencyList, adjacencyList[currentNode][i], bipartite, -color, visited, colors))
			{
				bipartite = false;
				return false;
			}
		}
		else if (colors[adjacencyList[currentNode][i]] == color)
		{
			bipartite = false;
			return false;
		}
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream input;
	ofstream output;
	input.open("bipartite.in", ios_base::in);
	output.open("bipartite.out", ios_base::out);

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	vector <vector <int>> adjacencyList(numberOfNodes, vector <int>());
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int from, to;
		input >> from >> to;
		adjacencyList[from - 1].push_back(to - 1);
	}
	bool bipartite = true;
	vector <bool> visited(numberOfNodes, false);
	vector <int> colors(numberOfNodes, 0);
	for (int i = 0; i < numberOfNodes; ++i)
	{
		if (!visited[i])
		{
			for (int j = 0; j < numberOfNodes; ++j)
			{
				colors[j] = 0;
			}
			if (!dfs(adjacencyList, i, bipartite, 1, visited, colors))
			{
				break;
			}
		}
	}

	if (bipartite)
	{
		output << "YES" << endl;
	}
	else
	{
		output << "NO" << endl;
	}
//	for (int i = 0; i < numberOfNodes; ++i)
//	{
//		cout << i + 1 << ": ";
//		for (int j : adjacencyList[i])
//		{
//		cout << j + 1 << " ";
//		}
//		cout << endl;
//	}
	input.close();
	output.close();
	return 0;
}

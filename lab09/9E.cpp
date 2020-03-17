#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Colors
{
	WHITE = 0,
	GREY = 1,
	BLACK = -1,
};

bool edgeExist(const int& from, const int& to, const vector <vector <int>>& adjacencyList)
{
	for (int i : adjacencyList[from])
	{
		if (i == to)
		{
			return true;
		}
	}
	return false;
}

void dfs(vector <vector <int>>& normalGraph, const int& currentNode, vector <int>& colors, vector <bool>& visited,
		 vector <int>& topsort)
{
	if (colors[currentNode] == WHITE)
	{
		visited[currentNode] = true;
		colors[currentNode] = GREY;
		if (!normalGraph[currentNode].empty())
		{
			for (int i = 0; i < normalGraph[currentNode].size(); ++i)
			{
				dfs(normalGraph, normalGraph[currentNode][i], colors, visited, topsort);
			}
		}

		colors[currentNode] = BLACK;
		topsort.push_back(currentNode);
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
	input.open("hamiltonian.in", ios_base::in);
	output.open("hamiltonian.out", ios_base::out);

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	vector <vector <int>> adjacencyList(numberOfNodes, vector <int>());
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int from, to;
		input >> from >> to;
		adjacencyList[from - 1].push_back(to - 1);
	}

//	for (int i = 0; i < numberOfNodes; ++i)
//	{
//		cout << i + 1 << ": ";
//		for (int j : adjacencyList[i])
//		{
//			cout << j + 1 << " ";
//		}
//		cout << endl;
//	}

	vector <int> colors(numberOfNodes, WHITE);
	vector <bool> visited(numberOfNodes, false);
	vector <int> topsort;
	bool hamiltonWayExist = true;

	for (int i = 0; i < numberOfNodes; ++i)
	{
		if (!visited[i])
		{
			dfs(adjacencyList, i, colors, visited, topsort);
		}
	}

//	for (int i : topsort)
//	{
//		cout << i + 1 << " ";
//	}
//	cout << endl;

	for (int i = numberOfNodes - 1; i > 0; --i)
	{
		if (!edgeExist(topsort[i], topsort[i - 1], adjacencyList))
		{
//			cerr << topsort[i] << " " << topsort[i - 1] << endl;
			hamiltonWayExist = false;
			break;
		}
	}

	if (hamiltonWayExist)
	{
		output << "YES" << endl;
	}
	else
	{
		output << "NO" << endl;
	}

	input.close();
	output.close();
	return 0;
}

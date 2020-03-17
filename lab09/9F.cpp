#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

enum Colors
{
	FIRST = true,
	SECOND = false,
};

void dfs(vector <vector <int>>& adjacencyList, int& currentNode, vector <bool>& player, vector <bool>& visited)
{
	bool currentPlayer = SECOND;
	visited[currentNode] = true;
	for (int i = 0; i < adjacencyList[currentNode].size(); ++i)
	{
		if (!visited[adjacencyList[currentNode][i]])
		{
			dfs(adjacencyList, adjacencyList[currentNode][i], player, visited);
		}
		if (!player[adjacencyList[currentNode][i]])
		{
			currentPlayer = FIRST;
		}
	}
	player[currentNode] = currentPlayer;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("game.in", ios_base::in);
	output.open("game.out", ios_base::out);

	int numberOfNodes, numberOfEdges, start;
	input >> numberOfNodes >> numberOfEdges >> start;
	vector <vector <int>> adjacencyList(numberOfNodes, vector <int>());
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int from, to;
		input >> from >> to;
		adjacencyList[from - 1].push_back(to - 1);
	}

	vector <bool> visited(numberOfNodes, false);
	vector <bool> player(numberOfNodes, SECOND);
	--start;
	dfs(adjacencyList, start, player, visited);

	if (player[start])
	{
		output << "First player wins" << endl;
	}
	else
	{
		output << "Second player wins" << endl;
	}

	input.close();
	output.close();
	return 0;
}

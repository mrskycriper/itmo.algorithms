#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

enum COLOR
{
	WHITE,
	GRAY,
	BLACK
};

class Node
{
public:
	COLOR color;
	vector <int> connected;
	Node()
	{
		color = WHITE;
	}
};

void dfs(vector <Node>& adjacencyList, stack <int>& result, const int& currentNode, bool& cycle)
{
	if (adjacencyList[currentNode].color == WHITE)
	{
		adjacencyList[currentNode].color = GRAY;
		if (adjacencyList[currentNode].connected.empty())
		{
			adjacencyList[currentNode].color = BLACK;
			result.push(currentNode + 1);
		}
		else
		{
			for (int i = 0; i < adjacencyList[currentNode].connected.size(); ++i)
			{
				dfs(adjacencyList, result, adjacencyList[currentNode].connected[i], cycle);
			}
			adjacencyList[currentNode].color = BLACK;
			result.push(currentNode + 1);
		}
	}
	else if (adjacencyList[currentNode].color == GRAY)
	{
		cycle = true;
	}
	else if (adjacencyList[currentNode].color == BLACK)
	{
		return;
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("topsort.in", ios::in);
	output.open("topsort.out", ios::out);

	bool cycle = false;

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;
	vector <Node> adjacencyList(numberOfNodes);
//	for (int i = 0; i < numberOfNodes; ++i)
//	{
//		adjacencyList[i].color = WHITE;
//	}
	for (int i = 0; i < numberOfEdges; ++i)
	{
		int firstNode, secondNode;
		input >> firstNode >> secondNode;
		adjacencyList[firstNode - 1].connected.push_back(secondNode - 1);
	}

	stack <int> result;

	for (int i = 0; i < numberOfNodes; ++i)
	{
		dfs(adjacencyList, result, i, cycle);
	}

	if (cycle)
	{
		output << "-1";
	}
	else
	{
		while (!result.empty())
		{
			output << result.top() << " ";
			result.pop();
		}
	}

	input.close();
	output.close();
	return 0;
}

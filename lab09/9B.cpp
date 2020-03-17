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

bool dfs(vector <Node>& adjacencyList, stack <int>& result, const int& currentNode, bool& cycle, int& cycleStart)
{
	if (adjacencyList[currentNode].color == WHITE)
	{
		adjacencyList[currentNode].color = GRAY;
		result.push(currentNode + 1);
		if (adjacencyList[currentNode].connected.empty())
		{
			adjacencyList[currentNode].color = BLACK;
			result.pop();
			return false;
		}
		else
		{
			for (int i = 0; i < adjacencyList[currentNode].connected.size(); ++i)
			{
				if (dfs(adjacencyList, result, adjacencyList[currentNode].connected[i], cycle, cycleStart))
				{
					return true;
				}
			}
			adjacencyList[currentNode].color = BLACK;
			return false;
		}
	}
	else if (adjacencyList[currentNode].color == GRAY)
	{
		cycleStart = currentNode;
		cycle = true;
		return true;
	}
	return false;

}

int main()
{
	ifstream input;
	ofstream output;
	input.open("cycle.in", ios::in);
	output.open("cycle.out", ios::out);

	bool cycle = false;
	int cycleStart = -1;
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
		if (dfs(adjacencyList, result, i, cycle, cycleStart))
		{
			break;
		}
	}

	if (!cycle)
	{
		output << "NO";
	}
	else
	{
		output << "YES" << endl;
		stack <int> reverseAnswer;

		while (result.top() != cycleStart + 1)
		{
			reverseAnswer.push(result.top());
			result.pop();
		}
		reverseAnswer.push(result.top());
		while (!reverseAnswer.empty())
		{
			output << reverseAnswer.top() << " ";
			reverseAnswer.pop();
		}
	}

	input.close();
	output.close();
	return 0;
}

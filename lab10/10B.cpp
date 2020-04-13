#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const double Inf = 10000000.0;

class Node
{
public:
	int x;
	int y;
};

double getWeight(const Node& from, const Node& to)
{
	return sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
}

void Prim(const vector <Node>& nodesList, vector <bool>& visited, vector <double>& priorityQueue, const int& numberOfNodes)
{
	int currentNode = 0;
	priorityQueue[currentNode] = 0.0;
	for (int i = 0; i < numberOfNodes; ++i)
	{
		double minPriority = Inf;
		visited[currentNode] = true;
		for (int j = 1; j < numberOfNodes; ++j)
		{
			if ((!visited[j]) && (getWeight(nodesList[currentNode], nodesList[j]) < priorityQueue[j]))
			{
				priorityQueue[j] = getWeight(nodesList[currentNode], nodesList[j]);
			}
		}
		for (int j = 1; j < numberOfNodes; ++j)
		{
			if((!visited[j]) && (priorityQueue[j] < minPriority))
			{
				minPriority = priorityQueue[j];
				currentNode = j;
			}
		}
	}
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("spantree.in", ios::in);
	output.open("spantree.out", ios::out);

	int numberOfNodes;
	input >> numberOfNodes;

	vector <Node> nodesList(numberOfNodes);
	vector <bool> visited(numberOfNodes, false);
	vector <double> priorityQueue(numberOfNodes, Inf);
	for (int i = 0; i < numberOfNodes; ++i)
	{
		input >> nodesList[i].x >> nodesList[i].y;
	}

//	for (auto i : nodesList)
//	{
//		input >> i.x >> i.y;
//	}

	Prim(nodesList, visited, priorityQueue, numberOfNodes);

	double result = 0.0;
	for (double i : priorityQueue)
	{
		result += i;
	}

	output.precision(10);
	output << result << endl;

	input.close();
	output.close();
	return 0;
}

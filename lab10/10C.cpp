#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

using namespace std;

//const double Inf = 100000000.0;

long long Prim(vector <bool>& visited, vector <vector <pair <long long, long long>>>& graph,
			   priority_queue <pair <long long, long long>, vector <pair <long long, long long>>, greater <>>& priorityQueue)
{
	pair <long long, long long> currentPair = priorityQueue.top();
	priorityQueue.pop();
	long long distanceFrom = currentPair.first;
	long long connectedNodeFrom = currentPair.second;
	if (visited[connectedNodeFrom])
	{
		return 0;
	}
	visited[connectedNodeFrom] = true;
	for (auto & i : graph[connectedNodeFrom])
	{
		long long connectedNode = i.first;
		long long distanceTo = i.second;
		if (!visited[connectedNode])
		{
			priorityQueue.push(make_pair(distanceTo, connectedNode));
		}
	}
	return distanceFrom;
}

int main()
{
	ifstream input;
	ofstream output;
	input.open("spantree3.in", ios::in);
	output.open("spantree3.out", ios::out);

	int numberOfNodes, numberOfEdges;
	input >> numberOfNodes >> numberOfEdges;

	vector <bool> visited(numberOfNodes, false);
	vector <vector <pair <long long, long long>>> graph(numberOfNodes);

	for (int i = 0; i < numberOfEdges; ++i)
	{
		int from, to, weight;
		input >> from >> to >> weight;
		graph[from - 1].push_back({to - 1, weight});
		graph[to - 1].push_back({from - 1, weight});
	}

	priority_queue <pair <long long, long long>, vector <pair <long long, long long>>, greater <>> priorityQueue;
	priorityQueue.push({0, 0});
	long long result = 0;
	while (!priorityQueue.empty())
	{
		result += Prim(visited, graph, priorityQueue);
	}
	output << result;


	input.close();
	output.close();
	return 0;
}

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

class edgeFlows
{
public:
	int startFlow;
	int currentFlow;
};

void Edmonds_Karp (std::vector <std::vector <edgeFlows>>& Graph, const int& vertexCount, bool& flowsExists)
{
	std::queue <int> Q;
	std::vector <bool> visited (vertexCount, false);
	std::vector <int> parents (vertexCount, -1);
	Q.push (0);

	while (!Q.empty ())
	{
		int currentVertex = Q.front ();
		if (currentVertex == vertexCount - 1)
		{
			break;
		}
		Q.pop ();
		visited[currentVertex] = true;

		for (int i = 0; i < vertexCount; ++i)
		{
			if (!visited[i] && (Graph[currentVertex][i].startFlow != Graph[currentVertex][i].currentFlow))
			{
				Q.push (i);
				parents[i] = currentVertex;
			}
		}
	}

	if (parents[vertexCount - 1] == -1)
	{
		flowsExists = false;
		return;
	}

	int currentVertex = vertexCount - 1, currentMinFlow = 1e5;
	for (int i = 0; i < vertexCount; ++i)
	{
		if (currentVertex > 0)
		{
			if (Graph[parents[currentVertex]][currentVertex].startFlow -
				Graph[parents[currentVertex]][currentVertex].currentFlow < currentMinFlow)
			{
				currentMinFlow = Graph[parents[currentVertex]][currentVertex].startFlow -
								 Graph[parents[currentVertex]][currentVertex].currentFlow;
			}
			currentVertex = parents[currentVertex];
		}
		else
		{
			break;
		}
	}

	currentVertex = vertexCount - 1;
	for (int i = 0; i < vertexCount; ++i)
	{
		if (currentVertex > 0)
		{
			Graph[currentVertex][parents[currentVertex]].currentFlow -= currentMinFlow;
			Graph[parents[currentVertex]][currentVertex].currentFlow += currentMinFlow;
			currentVertex = parents[currentVertex];
		}
		else
		{
			break;
		}
	}

}

int main ()
{
	std::ifstream input ("maxflow.in", std::ios_base::in);
	std::ofstream output ("maxflow.out", std::ios_base::out);

	int vertexCount, edgesCount;
	input >> vertexCount >> edgesCount;
	std::vector <std::vector <edgeFlows>> Graph (vertexCount, std::vector <edgeFlows> (vertexCount, {0, 0}));
	for (int i = 0; i < edgesCount; ++i)
	{
		int from, to, flow;
		input >> from >> to >> flow;
		Graph[--from][--to].startFlow = flow;
	}

	bool flowsExists = true;
	while (flowsExists)
	{
		Edmonds_Karp (Graph, vertexCount, flowsExists);
	}

	long long answer = 0;
	for (auto i : Graph)
	{
		answer += i[vertexCount - 1].currentFlow;
	}
	output << answer << std::endl;

	input.close ();
	output.close ();
	return 0;
}

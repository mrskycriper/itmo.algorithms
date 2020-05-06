#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

class Edge
{
public:
	int from, to, capacity, flow, number;
};

bool bfs (const std::vector <std::vector <int>>& Graph, std::vector <Edge>& EdgesList, std::vector <int>& level,
		  const int& t, const int& vertexCount)
{
	level.assign (vertexCount, 0);
	std::queue <int> q;
	q.push (0);
	level[0] = 1;
	while (!q.empty () && !level[t])
	{
		int from = q.front ();
		q.pop ();
		for (auto& edge : Graph[from])
		{
			if (!level[EdgesList[edge].to] && EdgesList[edge].capacity > EdgesList[edge].flow)
			{
				q.push (EdgesList[edge].to);
				level[EdgesList[edge].to] = level[from] + 1;
			}
		}
	}

	return level[t];
}

int
dfs (int currentVertex, int flow, const std::vector <std::vector <int>>& Graph, std::vector <Edge>& EdgesList,
	 std::vector <int>& level, std::vector <int>& ptr, const int& t, const int& vertexCount)
{
	if (!flow)
	{
		return 0;
	}
	if (currentVertex == t)
	{
		return flow;
	}
	while (ptr[currentVertex] < Graph[currentVertex].size ())
	{
		int edge = Graph[currentVertex][ptr[currentVertex]];
		if (level[currentVertex] + 1 == level[EdgesList[edge].to])
		{
			int pushed = dfs (EdgesList[edge].to, std::min (flow, EdgesList[edge].capacity - EdgesList[edge].flow),
							  Graph, EdgesList, level, ptr, t, vertexCount);
			if (pushed)
			{
				EdgesList[edge].flow += pushed;
				EdgesList[edge ^ 1].flow -= pushed;
				return pushed;
			}
		}
		ptr[currentVertex]++;
	}
	return 0;
}

void circulation (const std::vector <std::vector <int>>& Graph,
				  std::vector <Edge>& EdgesList, const int& t,
				  std::vector <int>& level, std::vector <int>& ptr, const int& vertexCount)
{
	while (bfs (Graph, EdgesList, level, t, vertexCount))
	{
		while (dfs (0, 1e9, Graph, EdgesList, level, ptr, t, vertexCount))
		{}
		ptr.assign (vertexCount, 0);
	}
}

void add (int from, int to, int capacity, std::vector <std::vector <int>>& Graph,
		  std::vector <Edge>& EdgesList)
{
	Graph[from].push_back (EdgesList.size ());
	EdgesList.emplace_back (Edge {from, to, capacity, 0});
	Graph[to].push_back (EdgesList.size ());
	EdgesList.emplace_back (Edge {to, from, 0, 0});
}


int main ()
{
	std::ifstream input ("circulation.in", std::ios_base::in);
	std::ofstream output ("circulation.out", std::ios_base::out);
	int vertexCount, edgesCount;
	input >> vertexCount >> edgesCount;
	vertexCount += 2;
	std::vector <std::vector <int>> Graph (vertexCount);
	std::vector <Edge> EdgesList;
	std::vector <int> ptr (vertexCount, 0);
	std::vector <int> level;
	for (int i = 0; i < edgesCount; ++i)
	{
		int from, to, minFlow, maxFlow;
		input >> from >> to >> minFlow >> maxFlow;
		add (0, to, minFlow, Graph, EdgesList);
		add (from, to, maxFlow - minFlow, Graph, EdgesList);
		add (from, vertexCount - 1, minFlow, Graph, EdgesList);
	}

	circulation (Graph, EdgesList, vertexCount - 1, level, ptr, vertexCount);

	for (int edge : Graph[0])
	{
		if (EdgesList[edge].flow < EdgesList[edge].capacity)
		{
			output << "NO" << std::endl;
			return 0;
		}
	}
	output << "YES" << std::endl;
	for (int i = 0; i < EdgesList.size (); i += 6)
	{
		output << EdgesList[i + 2].flow + EdgesList[i + 4].flow << std::endl;
	}


	input.close ();
	output.close ();
	return 0;
}

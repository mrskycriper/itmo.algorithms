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

int decomposition (int currentVertex, int minFlow, const std::vector <std::vector <int>>& Graph,
				   std::vector <Edge>& EdgesList, const int& t, std::vector <std::vector <int>>& answer)
{
	if (currentVertex == t)
	{
		answer.emplace_back ();
		return minFlow;
	}
	for (int edge : Graph[currentVertex])
	{
		if (EdgesList[edge].flow > 0)
		{
			int result = decomposition (EdgesList[edge].to, std::min (minFlow, EdgesList[edge].flow), Graph, EdgesList,
										t, answer);
			if (result)
			{
				answer.back ().push_back (EdgesList[edge].number);
				if (currentVertex == 0)
				{
					answer.back ().push_back (answer[answer.size () - 1].size ());
					answer.back ().push_back (result);
					reverse (answer.back ().begin (), answer.back ().end ());
				}
				EdgesList[edge].flow -= result;
				return result;
			}
		}
	}
	return 0;
}

void fullDecomposition (const std::vector <std::vector <int>>& Graph,
						std::vector <Edge>& EdgesList, const int& t, std::vector <std::vector <int>>& answer,
						std::vector <int>& level, std::vector <int>& ptr, const int& vertexCount)
{

	while (bfs (Graph, EdgesList, level, t, vertexCount))
	{
		while (dfs (0, 1e9, Graph, EdgesList, level, ptr, t, vertexCount))
		{}
		ptr.assign (vertexCount, 0);
	}
	while (decomposition (0, 1e9, Graph, EdgesList, t, answer))
	{}
}

int main ()
{
	std::ifstream input ("decomposition.in", std::ios_base::in);
	std::ofstream output ("decomposition.out", std::ios_base::out);

	int vertexCount, edgesCount;
	input >> vertexCount >> edgesCount;
	std::vector <std::vector <int>> Graph (vertexCount);
	std::vector <std::vector <int>> answer;
	std::vector <Edge> EdgesList;
	for (int i = 0; i < edgesCount; ++i)
	{
		int from, to, capacity;
		input >> from >> to >> capacity;
		Graph[from - 1].push_back (EdgesList.size ());
		EdgesList.emplace_back (Edge {from - 1, to - 1, capacity, 0, i + 1});
		Graph[to - 1].push_back (EdgesList.size ());
		EdgesList.emplace_back (Edge {to - 1, from - 1, 0, 0, i + 1});
	}

	std::vector <int> ptr (vertexCount, 0);
	std::vector <int> level;

	int t = vertexCount - 1;

	fullDecomposition (Graph, EdgesList, t, answer, level, ptr, vertexCount);

	output << answer.size () << "\n";
	for (auto& i : answer)
	{
		for (auto j : i)
		{
			output << j << ' ';
		}
		output << "\n";
	}

	input.close ();
	output.close ();
	return 0;
}

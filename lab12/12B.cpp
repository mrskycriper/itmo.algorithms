#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

bool try_ (int from, const std::vector <std::vector <int>>& Graph, std::vector <int>& matching,
		   std::vector <bool>& visited, std::vector <bool>& used)
{
	if (visited[from])
	{
		return false;
	}
	visited[from] = true;
	for (int i = 0; i < Graph[from].size (); ++i)
	{
		int to = Graph[from][i];
		if (matching[to] == -1 || try_ (matching[to], Graph, matching, visited, used))
		{
			matching[to] = from;
			return true;
		}
	}
	return false;
}

void Kuhn (const std::vector <std::vector <int>>& Graph, std::vector <int>& matching,
		   std::vector <bool>& visited, std::vector <bool>& used, const int& vertexCount1)
{
	for (int i = 0; i < vertexCount1; i++)
	{
		for (int j = 0; j < Graph[i].size (); j++)
		{
			if (matching[Graph[i][j]] == -1)
			{
				matching[Graph[i][j]] = i;
				used[i] = true;
				break;
			}
		}
	}
	for (int i = 0; i < vertexCount1; i++)
	{
		if (used[i])
		{
			continue;
		}
		for (int j = 0; j < vertexCount1; j++)
		{
			visited[j] = false;
		}
		try_ (i, Graph, matching, visited, used);
	}
}

int main ()
{
	std::ifstream input ("matching.in", std::ios_base::in);
	std::ofstream output ("matching.out", std::ios_base::out);

	int vertexCount1, vertexCount2, edgesCount;
	input >> vertexCount1 >> vertexCount2 >> edgesCount;
	std::vector <std::vector <int>> Graph (vertexCount1);
	std::vector <int> matching (vertexCount2, -1);
	std::vector <bool> visited (vertexCount1, false);
	std::vector <bool> used (vertexCount1, false);
	for (int i = 0; i < edgesCount; ++i)
	{
		int from, to;
		input >> from >> to;
		Graph[--from].push_back (--to);
	}

	Kuhn (Graph, matching, visited, used, vertexCount1);

	int answer = 0;
	for (auto i : matching)
	{
		if (i != -1)
		{
			++answer;
		}
	}
	output << answer << std::endl;

	input.close ();
	output.close ();
	return 0;
}

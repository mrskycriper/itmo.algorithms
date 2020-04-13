#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int64_t INF = 1000000000000000;

void Dijkstra (const std::vector <std::vector <std::pair <int32_t, int32_t>>>& Graph, std::vector <bool>& Visited,
			   std::vector <int64_t>& Distance)
{
	std::priority_queue <std::pair <int64_t, int32_t>, std::vector <std::pair <int64_t, int32_t>>, std::greater <>> queue;
	Visited[0] = true;
	Distance[0] = 0;
	queue.emplace (0, 0);
	while (!queue.empty ())
	{
		if (queue.top ().first >= INF)
		{
			queue.pop ();
			continue;
		}

		int32_t from = queue.top ().second;
		Visited[from] = true;
		queue.pop ();

		for (int32_t i = 0; i < Graph[from].size (); ++i)
		{
			if ((Distance[from] + Graph[from][i].second < Distance[Graph[from][i].first]) &&
				!Visited[Graph[from][i].first])
			{
				Distance[Graph[from][i].first] = Distance[from] + Graph[from][i].second;
				queue.emplace (Distance[Graph[from][i].first], Graph[from][i].first);
			}
		}
	}
}

int main ()
{
	std::ifstream input ("pathbgep.in", std::ios_base::in);
	std::ofstream output ("pathbgep.out", std::ios_base::out);

	int32_t VerticesCount, EdgesCount;
	input >> VerticesCount >> EdgesCount;

	std::vector <std::vector <std::pair <int32_t, int32_t>>> Graph (VerticesCount);
	std::vector <bool> Visited (VerticesCount, false);
	std::vector <int64_t> Distance (VerticesCount, INF);

	for (int32_t i = 0; i < EdgesCount; ++i)
	{
		int32_t from, to, weight;
		input >> from >> to >> weight;
		Graph[from - 1].push_back ({to - 1, weight});
		Graph[to - 1].push_back ({from - 1, weight});
	}

	Dijkstra (Graph, Visited, Distance);

	for (int32_t i : Distance)
	{
		output << i << " ";
	}
	output << std::endl;

	input.close ();
	output.close ();
	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int64_t INF = 1000000000000000;

void Dijkstra (const std::vector <std::vector <int32_t>>& GraphMatrix, std::vector <bool>& Visited,
			   std::vector <int64_t>& Distance, const int32_t& VerticesCount, const int32_t& StartVertex,
			   const int32_t& FinishVertex)
{
	std::priority_queue <std::pair <int64_t, int32_t>, std::vector <std::pair <int64_t, int32_t>>, std::greater <>> queue;
	Distance[StartVertex] = 0;
	Visited[StartVertex] = true;
	queue.emplace (0, StartVertex);

	while (!queue.empty ())
	{
		if (queue.top ().first >= INF)
		{
			queue.pop ();
			continue;
		}

		int32_t from = queue.top ().second;
		if (from == FinishVertex)
		{
			return;
		}
		Visited[from] = true;
		queue.pop ();

		for (int32_t i = 0; i < VerticesCount; i++)
		{
			if (GraphMatrix[from][i] == -1 || GraphMatrix[from][i] == 0)
			{
				continue;
			}
			if ((Distance[from] + GraphMatrix[from][i] < Distance[i]) && !Visited[i])
			{
				Distance[i] = Distance[from] + GraphMatrix[from][i];
				queue.emplace (Distance[i], i);
			}
		}
	}
}

int main ()
{
	std::ifstream input ("pathmgep.in", std::ios_base::in);
	std::ofstream output ("pathmgep.out", std::ios_base::out);

	int32_t VerticesCount, StartVertex, FinishVertex;
	int64_t result = 0;
	input >> VerticesCount >> StartVertex >> FinishVertex;
	--StartVertex;
	--FinishVertex;

	std::vector <std::vector <int32_t>> GraphMatrix (VerticesCount);
	std::vector <bool> Visited (VerticesCount, false);
	std::vector <int64_t> Distance (VerticesCount, INF);

	for (int32_t i = 0; i < VerticesCount; ++i)
	{
		for (int32_t j = 0; j < VerticesCount; ++j)
		{
			int32_t Vertex;
			input >> Vertex;
			GraphMatrix[i].push_back (Vertex);
		}
	}

	Dijkstra (GraphMatrix, Visited, Distance, VerticesCount, StartVertex, FinishVertex);
	result = Distance[FinishVertex];

	if (result < INF)
	{
		output << result << std::endl;
	}
	else
	{
		output << -1 << std::endl;
	}

	input.close ();
	output.close ();
	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>

const int64_t INF = 1e18;

class Vertex
{
public:
	int32_t from, to, weight;
};

int main ()
{
	std::ifstream input ("negcycle.in", std::ios_base::in);
	std::ofstream output ("negcycle.out", std::ios_base::out);

	int32_t VerticesCount;
	input >> VerticesCount;
	std::vector <int32_t> Parents (VerticesCount, -1);
	std::vector <int64_t> Weights (VerticesCount, 0);
	std::vector <Vertex> Graph;

	for (int32_t i = 0; i < VerticesCount; ++i)
	{
		for (int32_t j = 0; j < VerticesCount; ++j)
		{
			int32_t weight;
			input >> weight;
			if (weight != 1e9)
			{
				Graph.push_back ({i, j, weight});
			}
		}
	}

	int32_t ChangeStatus = -1; // -1 == NO
	for (int32_t i = 0; i < VerticesCount; ++i)
	{
		ChangeStatus = -1;
		for (auto& j : Graph)
		{
			if ((j.weight + Weights[j.from] < Weights[j.to]) && (Weights[j.from] != INF))
			{
				Weights[j.to] = std::max (j.weight + Weights[j.from], -INF);
				Parents[j.to] = j.from;
				ChangeStatus = j.to;
			}

		}
	}

	if (ChangeStatus == -1)
	{
		output << "NO" << std::endl;
	}
	else
	{
		std::vector <int64_t> NegativeCycle;

		for (int32_t i = 0; i < VerticesCount; ++i)
		{
			ChangeStatus = Parents[ChangeStatus];
		}

		output << "YES" << std::endl;
		NegativeCycle.push_back (ChangeStatus);
		int32_t CycleStart = ChangeStatus;
		ChangeStatus = Parents[ChangeStatus];

		while (ChangeStatus != CycleStart)
		{
			NegativeCycle.push_back (ChangeStatus);
			ChangeStatus = Parents[ChangeStatus];
		}
		NegativeCycle.push_back (ChangeStatus);

		output << NegativeCycle.size () << std::endl;
		for (int32_t i = NegativeCycle.size() - 1; i >= 0; --i)
		{
			output << NegativeCycle[i] + 1 << " ";
		}
		output << std::endl;
	}

	input.close ();
	output.close ();
	return 0;
}

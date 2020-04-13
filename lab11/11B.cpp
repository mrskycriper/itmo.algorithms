#include <iostream>
#include <fstream>
#include <vector>

const int64_t INF = 1000000000000000;

int main ()
{
	std::ifstream input ("pathsg.in", std::ios_base::in);
	std::ofstream output ("pathsg.out", std::ios_base::out);

	int32_t VerticesCount, EdgesCount;
	input >> VerticesCount >> EdgesCount;

	std::vector <std::vector <int64_t>> Weights (VerticesCount, std::vector <int64_t> (VerticesCount, INF));

	for (int32_t i = 0; i < EdgesCount; ++i)
	{
		int32_t from, to, weight;
		input >> from >> to >> weight;
		Weights[from - 1][to - 1] = weight;
	}

	for (int32_t i = 0; i < VerticesCount; ++i)
	{
		for (int32_t j = 0; j < VerticesCount; ++j)
		{
			for (int32_t k = 0; k < VerticesCount; ++k)
			{
				Weights[j][k] = std::min (Weights[j][k], Weights[j][i] + Weights[i][k]);
			}
		}
	}

	for (int32_t i = 0; i < VerticesCount; ++i)
	{
		for (int32_t j = 0; j < VerticesCount; ++j)
		{
			if (i == j)
			{
				output << "0 ";
			}
			else
			{
				output << Weights[i][j] << " ";
			}
		}
		output << std::endl;
	}

	input.close ();
	output.close ();
	return 0;
}

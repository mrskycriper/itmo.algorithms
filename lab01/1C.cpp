#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("turtle.in", ios_base::in);
	output.open("turtle.out", ios_base::out);

	const int MAX_SIZE = 1001;
	int height, width, line[MAX_SIZE][2], virtualHeight = 0;

	input >> height >> width;
	for (int i = 0; i < height; i++)
	{
		virtualHeight = i % 2;
		for (int j = width; j > 0; j--)
		{
			input >> line[j][virtualHeight];
		}
		if (i == 0)
		{
			for (int k = 1; k <= width; k++)
			{
				line[k][0] += line[k - 1][0];
			}
		}
		else
		{
			for (int k = 1; k <= width; k++)
			{
				if (line[k][1 - virtualHeight] > line[k - 1][virtualHeight])
				{
					line[k][virtualHeight] += line[k][1 - virtualHeight];
				}
				else
				{
					line[k][virtualHeight] += line[k - 1][virtualHeight];
				}
			}
		}

	}
	output << line[width][virtualHeight];

	input.close();
	output.close();
	return 0;
}

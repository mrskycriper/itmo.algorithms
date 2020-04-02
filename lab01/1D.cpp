#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("smallsort.in", ios_base::in);
	output.open("smallsort.out", ios_base::out);

	int length;
	input >> length;
	long long array[length];
	for (int i = 0; i < length; ++i)
	{
		input >> array[i];
	}

	for (int j = 1; j < length; ++j)
	{
		int k = j - 1;
		long long key = array[j];
		while (array[k] > key && k >= 0)
		{
			array[k + 1] = array[k];
			--k;
		}
		array[k + 1] = key;
	}

	for (auto i : array)
	{
		output << i << " ";
	}
	output << endl;

	input.close();
	output.close();
	return 0;
}

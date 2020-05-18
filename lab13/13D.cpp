#include <iostream>
#include <string>
#include <vector>

std::vector <int> GetPrefixFunction(const std::string& String)
{
	std::vector <int> prefix_function(String.length(), 0);
	prefix_function[0] = 0;
	for (int i = 1; i < String.length(); ++i)
	{
		int k = prefix_function[i - 1];
		while (k > 0 && String[i] != String[k])
		{
			k = prefix_function[k - 1];
		}
		if (String[i] == String[k])
		{
			++k;
		}
		prefix_function[i] = k;
	}
	return prefix_function;
}

std::vector <std::vector <int>> Knuth_Morris_Pratt(const std::string& String, const int& AlphabetSize)
{
	std::vector <int> prefix_function = GetPrefixFunction(String);
	std::vector <std::vector <int>> delta(String.length() + 1, std::vector <int>(AlphabetSize, 0));
	for (int i = 0; i < String.length() + 1; ++i)
	{
		for (int j = 0; j < AlphabetSize; ++j)
		{
			if (i != 0 && String[i] - 'a' != j)
			{
				delta[i][j] = delta[prefix_function[i - 1]][j];
			}
			else if (String[i] - 'a' == j)
			{
				delta[i][j] = i + 1;
			}
			else
			{
				delta[i][j] = i;
			}
		}
	}
	return delta;
}

int main()
{
	std::string String;
	int AlphabetSize;
	std::cin >> AlphabetSize;
	std::cin >> String;

	std::vector <std::vector <int>> result(String.length() - 1, std::vector <int>(AlphabetSize, 0));

	result = Knuth_Morris_Pratt(String, AlphabetSize);

	for (auto& i : result)
	{
		for (int j : i)
		{
			std::cout << j << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}



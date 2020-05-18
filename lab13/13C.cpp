#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector <int> GetPrefixFunction(const std::string& String)
{
	std::vector <int> prefix_function(String.length(), 0);

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

int main()
{
	std::ifstream input("prefix.in", std::ios_base::in);
	std::ofstream output("prefix.out", std::ios_base::out);

	std::string String;
	input >> String;

	std::vector <int> result;
	result = GetPrefixFunction(String);

	for (int i : result)
	{
		output << i << ' ';
	}
	output << std::endl;

	input.close();
	output.close();
	return 0;
}



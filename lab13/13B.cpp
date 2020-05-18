#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
			prefix_function[i] = k + 1;
		}
		else
		{
			prefix_function[i] = k;
		}
	}
	return prefix_function;
}

std::vector <int> FastSubstringSearch(const std::string& String, const std::string& Pattern)
{
	std::vector <int> result;
	std::vector <int> prefix_function = GetPrefixFunction(Pattern + '#' + String);
	for (int i = 0; i < String.length(); ++i)
	{
		if (prefix_function[Pattern.length() + 1 + i] == Pattern.length())
		{
			result.push_back(i - Pattern.length() + 2);
		}
	}
	return result;
}

int main()
{
	std::ifstream input("search2.in", std::ios_base::in);
	std::ofstream output("search2.out", std::ios_base::out);
	std::string Pattern, String;
	input >> Pattern >> String;

	std::vector <int> result = FastSubstringSearch(String, Pattern);

	output << result.size() << std::endl;
	for (auto i : result)
	{
		output << i << ' ';
	}
	output << std::endl;

	input.close();
	output.close();
	return 0;
}



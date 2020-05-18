#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::string GetInterval(const std::string& InString, const int& From, const int& To)
{
	std::string interval;

	for (int i = From; i <= To; ++i)
	{
		interval.push_back(InString[i]);
	}

	return interval;
}

std::vector <int> NaiveStringMatcher(const std::string& Pattern, const std::string& Text)
{
	std::vector <int> answer;

	for (int i = 0; i < Text.length() - Pattern.length() + 1; ++i)
	{
		if (GetInterval(Text, i, i + Pattern.length() - 1) == Pattern)
		{
			answer.push_back(i);
		}
	}

	return answer;
}

int main()
{
	std::ifstream input("search1.in", std::ios_base::in);
	std::ofstream output("search1.out", std::ios_base::out);

	std::string pattern, text;
	input >> pattern >> text;

	std::vector <int> result;
	if (text.length() > pattern.length())
	{
		result = NaiveStringMatcher(pattern, text);
	}
	output << result.size() << std::endl;
	for (int i : result)
	{
		output << i + 1 << ' ';
	}
	output << std::endl;

	input.close();
	output.close();

	return 0;
}

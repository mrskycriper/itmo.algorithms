#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("aplusbb.in", ios_base::in);
	output.open("aplusbb.out", ios_base::out);

	long long a, b;
	input >> a >> b;
	output << a + (b * b) << endl;

	input.close();
	output.close();
	return 0;
}

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream input;
	ofstream output;
	input.open("aplusb.in", ios_base::in);
	output.open("aplusb.out", ios_base::out);

	int a, b;
	input >> a >> b;
	output << a + b << endl;

	input.close();
	output.close();
	return 0;
}

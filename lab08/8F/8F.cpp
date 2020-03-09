#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class node
{
public:
	string pathFromStart;
	int upNode;
	int rightNode;
	int downNode;
	int leftNode;

	node()
	{
		pathFromStart = "";
		upNode = -1;
		rightNode = -1;
		downNode = -1;
		leftNode = -1;
	}
};

int main()
{
	ifstream input;
	ofstream output;
	input.open("input.txt", ios::in);
	output.open("output.txt", ios::out);

	int height, width;
	input >> height >> width;
	vector <vector <char>> maze(height, vector <char>(width, 0));
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			input >> maze[i][j];
		}
	}

//	for (int i = 0; i < height; ++i)
//	{
//		for (int j = 0; j < width; ++j)
//		{
//			cout << maze[i][j];
//		}
//		cout << endl;
//	}

	node* adjacencyList = new node[height * width];
	int startNode = 0;
	int finishNode = 0;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (maze[i][j] != '#')
			{
				if (i > 0)
				{
					if (maze[i - 1][j] != '#')
					{
						adjacencyList[i * width + j].upNode = (i - 1) * width + j;
					}
				}
				if (j < width - 1)
				{
					if (maze[i][j + 1] != '#')
					{
						adjacencyList[i * width + j].rightNode = i * width + j + 1;
					}
				}
				if (i < height - 1)
				{
					if (maze[i + 1][j] != '#')
					{
						adjacencyList[i * width + j].downNode = (i + 1) * width + j;
					}
				}
				if (j > 0)
				{
					if (maze[i][j - 1] != '#')
					{
						adjacencyList[i * width + j].leftNode = i * width + j - 1;
					}
				}
			}
			if (maze[i][j] == 'S')
			{
				startNode = i * width + j;
			}
			if (maze[i][j] == 'T')
			{
				finishNode = i * width + j;
			}
		}
	}

	vector <bool> visited(height * width, false);
	queue <int> connectedNodes;
	connectedNodes.push(startNode);
	while (!connectedNodes.empty())
	{
		if (adjacencyList[connectedNodes.front()].upNode != -1 && !visited[adjacencyList[connectedNodes.front()].upNode])
		{
			visited[adjacencyList[connectedNodes.front()].upNode] = true;
			adjacencyList[adjacencyList[connectedNodes.front()].upNode].pathFromStart = adjacencyList[connectedNodes.front()].pathFromStart + 'U';
			connectedNodes.push(adjacencyList[connectedNodes.front()].upNode);
		}
		if (adjacencyList[connectedNodes.front()].rightNode != -1 && !visited[adjacencyList[connectedNodes.front()].rightNode])
		{
			visited[adjacencyList[connectedNodes.front()].rightNode] = true;
			adjacencyList[adjacencyList[connectedNodes.front()].rightNode].pathFromStart = adjacencyList[connectedNodes.front()].pathFromStart + 'R';
			connectedNodes.push(adjacencyList[connectedNodes.front()].rightNode);
		}
		if (adjacencyList[connectedNodes.front()].downNode != -1 && !visited[adjacencyList[connectedNodes.front()].downNode])
		{
			visited[adjacencyList[connectedNodes.front()].downNode] = true;
			adjacencyList[adjacencyList[connectedNodes.front()].downNode].pathFromStart = adjacencyList[connectedNodes.front()].pathFromStart + 'D';
			connectedNodes.push(adjacencyList[connectedNodes.front()].downNode);
		}
		if (adjacencyList[connectedNodes.front()].leftNode != -1 && !visited[adjacencyList[connectedNodes.front()].leftNode])
		{
			visited[adjacencyList[connectedNodes.front()].leftNode] = true;
			adjacencyList[adjacencyList[connectedNodes.front()].leftNode].pathFromStart = adjacencyList[connectedNodes.front()].pathFromStart + 'L';
			connectedNodes.push(adjacencyList[connectedNodes.front()].leftNode);
		}
		connectedNodes.pop();
	}

	if (!adjacencyList[finishNode].pathFromStart.empty())
	{
		output << adjacencyList[finishNode].pathFromStart.size() << '\n' << adjacencyList[finishNode].pathFromStart;
	}
	else
	{
		output << -1;
	}

	input.close();
	output.close();
	return 0;
}

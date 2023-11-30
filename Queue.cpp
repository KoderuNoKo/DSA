#include <queue>
#include <iostream>

using namespace std;

vector<int> topologicalSorting(vector<vector<int>> graph)
{
	int size = graph.size();
	vector<int> in_degree(size, 0);

	vector<int>::iterator itr;
	for (int i = 0; i < size; i++) {
		for (itr = graph[i].begin(); itr < graph[i].end(); itr++) {
			in_degree[*itr]++;
		}
	}

	queue<int> zero_Order;
	for (int i = 0; i < size; i++) {
		if (in_degree.at(i) == 0) {
			zero_Order.push(i);
		}
	}

	int cnt = 0;

	vector<int> res;
	while (!zero_Order.empty())
	{
		int curr = zero_Order.front();
		res.push_back(curr);
		zero_Order.pop();

		for (itr = graph[curr].begin(); itr < graph[curr].end(); itr++) {
			if (--in_degree[*itr] == 0) {
				zero_Order.push(*itr);
			}
		}

		cnt++;
	}

	if (cnt != size) {
		res.clear();
		res.push_back(-1);
	}
	return res;
}

/*
int main()
{
	int n = 6;
	int G[6][6] = {
		{0,1,0,1,0,0},
		{0,0,1,1,0,0},
		{0,0,0,1,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,0,1},
		{0,1,0,0,0,0}
	};
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (G[i][j] == 1) graph[i].push_back(j);
		}
	}

	vector<int> res = topologicalSorting(graph);
	if (res.empty()) {
		printf("-1");
	}
	else {
		for (int e : res) {
			cout << e << " ";
		}
	}
}
*/
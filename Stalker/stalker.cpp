#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<list>
#include<iterator>
#include<deque>

using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

class Graph
{
private:
	int buildings_n;
	int maps_n;
	vector<int> distances; // :/
	deque<int> queue;
	vector<pair<int, int>> vertices; // first - map, second - building
	vector<vector<pair<int, int>>> adj; // NK + N ~ buildings_n * maps_n + buildings_n

public:
	Graph()
	{
		ifstream input;
		input.open(iname);
		input >> buildings_n;
		input >> maps_n;
		int vn = buildings_n * maps_n + buildings_n;
		adj.resize(vn);
		distances.resize(buildings_n);
		vertices.resize(vn);
		adj.resize(vn);
		for (int i = 1; i <= buildings_n; i++)
			vertices.push_back(make_pair(0, i));
		for (int i = 1; i <= buildings_n; i++)
			for (int j = 1; j <= maps_n; j++)
				vertices.push_back(make_pair(i, j));
 	}

	void make_adj()
	{
		//Добавим для каждого x вершину (x, 0), и проведем для каждого y дуги (x, y) → (x, 0) с весом 0
		// и (x, 0) → (x, y) с весом 1
		for (int i = 1; i <= maps_n; i++)
			for (int j = 1; j <= buildings_n; j++)
				adj[j].emplace_back(buildings_n * (i - 1) + j, 1);
	}

	void bfs()
	{
		// Инициализация
		queue.push_back(0);
		distances[0] = 0;
		// Главный цикл
		while (!queue.empty())
		{
			int v = queue.front();
			queue.pop_front();
			for (int i = 0; i < (int)adj[v].size(); ++i)
				if (distances[adj[v][i].first] > distances[v] + adj[v][i].second)
				{
					distances[adj[v][i].first] = distances[v] + adj[v][i].second;
					if (adj[v][i].second == 0)
						queue.push_front(adj[v][i].first);
					else
						queue.push_back(adj[v][i].first);
				}
		}
	}
};


int main()
{
	Graph g = Graph();
	ofstream output;
	output.open(oname);
	output.clear();

	getchar();
}




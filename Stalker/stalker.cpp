#include<string>
#include<fstream>
#include<vector>
#include<deque>
#include<climits>

using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

class Graph
{
private:
	int maps_n;
	deque<int> queue;
	vector<pair<int, int>> vertices; // first - map, second - building
	vector<vector<pair<int, int>>> adj; // NK + N ~ buildings_n * maps_n + buildings_n
	vector<vector<pair<int, int>>> maps;
	int max_vertices;
public:
	vector<int> distances;
	int buildings_n;
	Graph()
	{
		ifstream input;
		input.open(iname);
		input >> buildings_n;
		input >> maps_n;
		input.close();
		max_vertices = buildings_n * maps_n + buildings_n;
		adj.resize(max_vertices);
		distances.resize(max_vertices);
		for (int i = 0; i < max_vertices; i++)
			distances[i] = INT_MAX;
 	}

	void make_adj()
	{
		//Добавим для каждого x вершину (x, 0), и проведем для каждого y дуги (x, 0) → (x, y) с весом 1  
		for (int i = 0; i < maps_n; i++)
			for (int j = 0; j < buildings_n; j++)
				adj[j].emplace_back(buildings_n * i + j + buildings_n, 1);
		// и (x, y) → (x, 0) с весом 0
		for (int i = buildings_n; i < max_vertices; i++)
		{
			int t = i % buildings_n;
			adj[i].emplace_back(t, 0);
		}
		// остальные (между зданиями в пределах одной карты, вес = 0)
		ifstream input;
		input.open(iname);
		string ignore;
		getline(input, ignore);
		for (int i = 1; i <= maps_n; i++)
		{
			int n_roads_temp;
			input >> n_roads_temp;
			for (int j = 1; j <= n_roads_temp; j++)
			{
				int from;
				int to;
				input >> from; // дорога между from и to на карте с номером  i
				input >> to;
				// информация об i-й карте в adj с i * buildings_n по i * buildings_n + buildings_n - 1
				// здания определяются по остатку от деления на buildings_n
				// индекс состояния (m, b) в массиве adj = m * buildings_n + b % buildings_n
				int ind_i_from = i * buildings_n + ((from - 1) % buildings_n);
				int ind_i_to = i * buildings_n + ((to - 1) % buildings_n);
				adj[ind_i_from].emplace_back(ind_i_to, 0);
				adj[ind_i_to].emplace_back(ind_i_from, 0);
			}
		}
		input.close();
	}

	void bfs()
	{
		queue.push_back(0);
		distances[0] = 0;
		while (!queue.empty())
		{
			int v = queue.front();
			queue.pop_front();
			for (int i = 0; i < adj[v].size(); ++i)
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
	g.make_adj();
	g.bfs();
	ofstream output;      
	output.open(oname);
	output.clear();
	if (g.distances[g.buildings_n - 1] == INT_MAX)
		output << -1;
	else
		output << g.distances[g.buildings_n - 1];
}




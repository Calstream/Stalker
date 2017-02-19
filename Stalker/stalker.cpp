#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<list>
#include<iterator>

using namespace std; // ссылки, выкинуть ненужное + комментарии, add_edge, private/public

string const iname = "input2.txt";
string const oname = "output.txt";

class Graph
{
public:
	int buildings_n;
	int maps_n;
	vector<vector<pair<int, int>>> maps;
	list<unordered_set<int>> groups;
	vector<unordered_set<int>> vertices; // &*?
	vector<list<int>> adj;
	vector<int> distances;

	Graph()
	{
		ifstream input;
		input.open(iname);
		input >> buildings_n;
		input >> maps_n;
		maps.resize(maps_n);
		for (int i = 0; i < maps_n; i++)
		{
			int roads_n;
			input >> roads_n;
			for (int j = 1; j <= roads_n; j++)
			{
				int f, s;
				input >> f;
				input >> s;
				maps[i].push_back(make_pair(f, s));
			}
		}
	}

	void make_vertices()
	{
		vertices.resize(groups.size() + 2);
		unordered_set<int> temp;
		temp.insert(-1);
		vertices[0] = temp;
		vertices[vertices.size() - 1] = temp;
		int counter = 1;
		for (unordered_set<int> g : groups)
				vertices[counter++] = g;
	}

	// 1 map -> group(s)
	void map_to_groups(vector<pair<int, int>> & roads, list<unordered_set<int>> & new_groups)
	{
		unordered_set<int> temp;
		temp.insert(roads[0].first);
		temp.insert(roads[0].second);
		new_groups.push_back(temp);
		temp.clear();
		
		for (int i = 1; i < roads.size(); i++)
		{
			bool f = false; // false - make new group
			for (unordered_set<int> & g : new_groups)
			{
				if (g.find(roads[i].first) != g.end() || g.find(roads[i].second) != g.end()) // ins same val
				{
					g.insert(roads[i].first);
					g.insert(roads[i].second); 
					f = true;
				}
			}
			if (!f)
			{
				temp.insert(roads[i].first);
				temp.insert(roads[i].second);
				new_groups.push_back(temp);
				temp.clear();
			}
		}
}
	
	void all_maps_to_groups()
	{
		list<unordered_set<int>> temp;
		for(auto map : maps)
		{
			map_to_groups(map, temp);
			for(auto s : temp)
				groups.push_back(s);
			temp.clear();
		}
	}
	
	void inline add_edge(int from, int to)
	{
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	bool inline edge_exists(int from, int to)
	{
		if (adj[from].empty())
			return false;
		return(find(adj[from].begin(), adj[from].end(),to) != adj[from].end());
	}

	void make_adj()
	{
		adj.resize(vertices.size()); // 0 - supersource, adj.size() - supersink 
		for (int i = 1; i < vertices.size(); i++)
		{
			if (vertices[i].find(1) != vertices[i].end())
				add_edge(0, i);
			if (vertices[i].find(buildings_n) != vertices[i].end())
				add_edge(adj.size() - 1, i);

			for (int j = i+1; j < vertices.size(); j++) 
			{
				if (edge_exists(i, j)) // true?
					continue;
				for (int x : vertices[i])
				{
					if (vertices[j].find(x) != vertices[j].end())
					{
						add_edge(i, j);
						continue;
					}
				}
				
			}
		}
	}

	void bfs(int start)
	{
		vector<bool> visited;
		visited.resize(vertices.size());
		for (int i = 0; i < visited.size(); i++)
			visited[i] = false;

		list<int> queue;

		visited[start] = true;
		queue.push_back(start);

		while (!queue.empty())
		{
			start = queue.front();
			queue.pop_front();

			for(auto v: adj[start])
			{
				if (!visited[v])
				{
					visited[v] = true;
					queue.push_back(v);
					distances[v] = distances[start] + 1;
				}
			}
		}
	}

	int get_result()
	{
		all_maps_to_groups();
		make_vertices();
		make_adj();
		distances.resize(vertices.size());
		bfs(0);
		return distances[distances.size() - 1] - 1;
	}
};


int main()
{
	Graph g = Graph();
	ofstream output;
	output.open(oname);
	output.clear();
	output << g.get_result();

	getchar();
}




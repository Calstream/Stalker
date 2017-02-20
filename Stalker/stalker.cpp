#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<list>
#include<iterator>

using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

class Graph
{
private:
	int buildings_n;
	int maps_n;
	vector<vector<pair<int, int>>> maps;
	list<set<int>> groups;

	void map_to_groups(vector<pair<int, int>> & roads, list<set<int>> & new_groups)
	{
		set<int> temp;
		temp.insert(roads[0].first);
		temp.insert(roads[0].second);
		new_groups.push_back(temp);
		temp.clear();

		for (int i = 1; i < roads.size(); i++)
		{
			bool f = false; // false - make new group
			for (set<int> & g : new_groups)
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
		list<set<int>> temp;
		for (auto map : maps)
		{
			map_to_groups(map, temp);
			for (auto s : temp)
				groups.push_back(s);
			temp.clear();
		}
	}

public:
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

	int DIMAS()
	{
		int result = 1;
		set<int> layer;
		bool remove_prev = false;
		list<set<int>>::iterator it;
		for (set<int> g : groups)
		{
			if (remove_prev)
			{
				remove_prev = false;
				groups.erase(it);
			}
			if (g.find(1) != g.end())
			{
				set_union(g.begin(), g.end(), layer.begin(), layer.end(), inserter(layer,layer.end()));
				remove_prev = true;
				it = find(groups.begin(), groups.end(), g);
			}
		}

		set<int> next_layer;
		while (true)
		{
			for (set<int> g : groups)
			{
				if (remove_prev)
				{
					remove_prev = false;
					groups.erase(it);
				}
				set<int> intersection_temp;
				set_intersection(g.begin(), g.end(), layer.begin(), layer.end(),
					inserter(intersection_temp, intersection_temp.begin()));
				if (!intersection_temp.empty())
				{
					set<int> dif_temp;
					set_difference(g.begin(), g.end(), layer.begin(), layer.end(),
						inserter(dif_temp, dif_temp.begin()));
					set_union(dif_temp.begin(), dif_temp.end(),
						next_layer.begin(), next_layer.end(), inserter(next_layer, next_layer.end()));
					remove_prev = true;
					it = find(groups.begin(), groups.end(), g);
				}
			}
			if (remove_prev)
			{
				remove_prev = false;
				groups.erase(it);
			}
			result++;
			if (next_layer.find(buildings_n) != next_layer.end())
				return result;
			if (next_layer.empty())
				break;
			layer = next_layer;
			next_layer.clear();
		}
		
		if (groups.size() != 0)
			result = -1;
		return result;
	}

	int get_result()
	{
		all_maps_to_groups();
		int r = DIMAS();
		return r;
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




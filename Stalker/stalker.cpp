#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>
#include<list>
using namespace std;

string const iname = "input.txt";
string const oname = "output.txt";

bool is_connected(vector<pair<int,int>> v)
{
	if (v.size() == 1)
		return true;
	int b = v.size(); // number of buildings
	vector<int> temp;
	temp.push_back(v[0].first);
	temp.push_back(v[0].second);
	for (int i = 1; i < v.size(); i++)
	{
		auto resf = find(temp.begin(), temp.end(), v[i].first);
		auto ress = find(temp.begin(), temp.end(), v[i].second);
		if (resf == temp.end() && ress == temp.end())
			return false;
		temp.push_back(v[i].first);
		temp.push_back(v[i].second);
	}
	return true;
}
//
//bool road_on_map(vector<pair<int, int>> map, pair<int, int> road)
//{
//	for (int i = 0; i < map.size(); i++)
//	{
//		auto resf = find(map.begin(), map.end(), road[i].first);
//		auto ress = find(temp.begin(), temp.end(), v[i].second);
//		if (resf == temp.end() && ress == temp.end())
//			return false;
//	}
//}

//void split(vector<vector<pair<int, int>>> maps, vector<pair<int, int>> tbs)
//{
//	remove(maps.begin(), maps.end(), tbs);
//	vector<vector<pair<int, int>>> temp;
//	int parts = 1;
//	temp.resize(parts);
//	temp[0].push_back(tbs[0]);
//	for (int i = 1; i < tbs.size; i++)
//	{
//		auto resf = find(temp.begin(), temp.end(), tbs[i].first);
//		auto ress = find(temp.begin(), temp.end(), tbs[i].second);
//		if (resf == temp.end() && ress == temp.end())
//		{
//			parts++;
//			temp.resize(parts);
//			temp[parts - 1].push_back(tbs[i]);
//		}
//	}
//}

//pair<vector<pair<int, int>>, vector<pair<int, int>>> split_in_two(vector<pair<int, int>> tbs)
//{
//	vector<int> temp;
//	temp.push_back(tbs[0].first);
//	temp.push_back(tbs[0].second);
//	for (int i = 1; i < tbs.size(); i++)
//	{
//		auto resf = find(temp.begin(), temp.end(), tbs[i].first);
//		auto ress = find(temp.begin(), temp.end(), tbs[i].second);
//		if (resf == temp.end() && ress == temp.end())
//		{
//
//		}
//		temp.push_back(tbs[i].first);
//		temp.push_back(tbs[i].second);
//	}
//	return true;
//}

class Graph
{
public:
	int buildings_n;
	int maps_n;
	vector<vector<pair<int, int>>> maps;
	list<set<int>> groups;
	vector<pair<int, int>> edges;
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

	// 1 map -> group(s)
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
					g.insert(roads[i].second); // iterator
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
		for each(auto map in maps)
		{
			map_to_groups(map, temp);
			for each(auto s in temp)
				groups.push_back(s);
			temp.clear();
		}
	}
	
	void make_edges()
	{

	}

	int get_path_length()
	{

	}
};


int main()
{
	Graph g = Graph();
	g.all_maps_to_groups();

	//for each (auto x in maps)
	{
		//cout << is_connected(x) << endl;
		/*if (!is_connected(x))
			split(maps, x);*/
	}

	getchar();
	/*
	
	string s = "";
	int n = 0;
	input >> n;
	int m = 0;
	input >> m;
	//input.ignore();
	Graph g1(n, m);
	for (size_t i = 0; i <= m-1; i++)
	{
		int v1;
		int v2;
		int w;
		input >> v1;
		input >> v2;
		input >> w;
		g1.AddEdge(v1, v2, w);
	}
	input.close();

	*/

}



/*

bool inline conn(pair<int, int> p, set<int> s)
{
auto resf = find(s.begin(), s.end(), p.first);
auto ress = find(s.begin(), s.end(), p.second);
if (resf == s.end() && ress == s.end())
return false;
return true;
}

void make_groups()
{
set<int> temp;
temp.insert(maps[0][0].first);
temp.insert(maps[0][0].second);
groups.push_back(temp);
temp.clear();
for each(auto x in maps)
{
bool f = false;
for (size_t i = 1; i < x.size(); i++)
{
for each (auto g in groups)
{
f = false;
if (conn(x[i], g))
{
g.insert(x[i].first);
g.insert(x[i].second);
f = true;
continue;
}
}
if (!f)
{
temp.insert(x[i].first);
temp.insert(x[i].second);
groups.push_back(temp);
temp.clear();
}
}
}
}
*/
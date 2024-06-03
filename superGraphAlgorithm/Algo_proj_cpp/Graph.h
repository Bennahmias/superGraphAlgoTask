#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
using namespace std;

class Graph
{
private:

	int verteices_number=0; 
	int edges_number=0;
	vector<list<int>> arrayOfList;
	Graph* TransposeGraph = nullptr;
	vector<int> arrayOfRoots;


public:
	
	~Graph();
	void setVerteicesNumber(const int number);
	void setEdgesNumber(const int number);

	void MakeEmptyGraph();
	bool IsAdjacent(int u, int v)  ;
	list<int> GetAdjList(int u) const;
	void AddEdge(int v, int u);
	void RemoveEdge(int u, int v);

	vector<int> DFS(vector<int>& mainLoop, int& verteices, int& edges);

	void MakeGtrans();

	void MakeSuperGraph(int& verteices, int& edges);

	void Visit(int vertex, int currentRoot, int& edges,
		vector<int>& start, vector<int>& end,
		vector<int>& color,int& counter, 
		vector<pair<int, int>>& edgeCount);




};


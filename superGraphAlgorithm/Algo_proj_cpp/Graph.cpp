
#include "Graph.h"
#include <list>
using namespace std;

enum DfsColor { WHITE, GRAY, BLACK };
Graph::~Graph()
{
	if (TransposeGraph)
		delete TransposeGraph;
}
void Graph::setVerteicesNumber(const int number)
{
	verteices_number = number;
}
void Graph::setEdgesNumber(const int number)
{
	edges_number = number;
}
void Graph::MakeEmptyGraph()
{
	arrayOfList.resize(verteices_number+1); //resize the list of neighbors to contain |vertex| elements
	arrayOfRoots.resize(verteices_number+1); //resize the root array to have |vertex| elements
}
bool Graph::IsAdjacent(int u, int v)
{
	list<int>::iterator i = arrayOfList[u].begin();
	 

	for (i; i != arrayOfList[u].end(); ++i)
	{
		if (*i == v)
			return true;
	}
	return false;

}
list<int> Graph::GetAdjList(int u) const
{
	return arrayOfList[u];
}
void Graph::AddEdge(int u, int v)
{
	list<int>::iterator i = arrayOfList[u].begin();
	
	for (i; i != arrayOfList[u].end(); ++i)
	{
		try
		{
			if (*i == v)
				throw "There is already a edge like this";
		}
		catch (const char* error)
		{
			cout << error << endl;
			exit(1);
		}
	}
	arrayOfList[u].push_back(v); //added a u->v
}
void Graph::RemoveEdge(int u, int v)
{
	list<int>::iterator i = arrayOfList[u].begin();
	
	try
	{
		for (i; i != arrayOfList[u].end(); ++i)
		{
			if (*i == v)
			{
				arrayOfList[u].remove(v); //remove v from the list.
				return;
			}
		}
		throw "There is not such an edge..";
	}
	catch (const char* error)
	{
		cout << error << endl;
		exit(1);
	}
}
void Graph::MakeGtrans()
{
	TransposeGraph = new Graph;
	TransposeGraph->setEdgesNumber(edges_number);
	TransposeGraph->setVerteicesNumber(verteices_number);
	TransposeGraph->MakeEmptyGraph();
	for (int i = 1; i <= verteices_number; ++i)
	{
		list<int> adjlist = this->GetAdjList(i);
		for (list<int>::iterator itr = adjlist.begin(); itr != adjlist.end(); ++itr)
		{
			TransposeGraph->AddEdge(*itr, i);
		}
	}
}
vector<int> Graph::DFS(vector<int>& mainLoop, int& verteices, int& edges)
{
	vector<pair<int, int>> edgeCount;
	verteices = edges = 0;
	vector<int> start(verteices_number+1, 0);
	vector<int> end;
	vector<int> color(verteices_number+1, DfsColor::WHITE);
	int counter = 0;

	//Main Loop 
	for (vector<int>::iterator itr = mainLoop.begin(); itr != mainLoop.end(); ++itr)
	{
		if (color[*itr] == DfsColor::WHITE)
		{
			++verteices;
			Visit(*itr, *itr, edges, start, end, color, counter, edgeCount);
		}
	}
	return end;
}
void Graph::MakeSuperGraph(int& verteices, int& edges)
{
	vector<int> mainLoop(verteices_number);
	iota(mainLoop.begin(), mainLoop.end(), 1); // fill the mainloop from 1 to |vertex|
	vector<int> endList = DFS(mainLoop, verteices, edges);
	this->MakeGtrans();
	reverse(endList.begin(), endList.end());
	TransposeGraph->DFS(endList, verteices, edges);
}
void Graph::Visit(int vertex, int currentRoot, int& edges,
	vector<int>& start, vector<int>& end, vector<int>& color, int& counter,
	vector<pair<int, int>>& edgeCount)
{
	bool foundAnEdge = false;
	arrayOfRoots[vertex] = currentRoot;
	color[vertex] = DfsColor::GRAY;
	start[vertex] = counter++;
	list<int> adj = GetAdjList(vertex);
	for (list<int>::iterator itr = adj.begin(); itr != adj.end(); ++itr)
	{
		if (color[*itr] == DfsColor::WHITE) //recursive
		{
			Visit(*itr, currentRoot, edges, start, end, color, counter, edgeCount);
		}

		else if (color[*itr] == DfsColor::BLACK)
		{
			if (start[vertex] > start[*itr] && arrayOfRoots[vertex]!=arrayOfRoots[*itr])  // if it a crossarc 
			{

				pair<int, int> temp = { arrayOfRoots[vertex],arrayOfRoots[*itr] };

				for (auto& pair : edgeCount) //check if the edge is already in the graph
				{
					if (pair == temp)
					{
						foundAnEdge = true;
						break;
					}
				}
				if (!foundAnEdge)//its a new edge add it to the edgecount
				{
					foundAnEdge = false;
					edgeCount.push_back(temp);
					++edges;
				}

				//edges of the super graph 
				//works only on dfs+Sharir algo
				//when doing a regular dfs, these parametest wont be used.
				//this is not correct when using dfs with random mainloop.
			}
		}
	}
	color[vertex] = DfsColor::BLACK;
	end.push_back(vertex);
	++counter;
}
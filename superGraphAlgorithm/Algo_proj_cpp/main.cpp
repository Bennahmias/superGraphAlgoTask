#include "Graph.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
	int verteices_number = 0; 
	int edges_number = 0;
	cout << "Please enter the numbers of verteices" << endl;
	cin >> verteices_number; 
	cout << "Please enter the numbers of edges" << endl;
	cin >> edges_number;
	
	try
	{
		if (verteices_number < 0 || edges_number < 0)
			throw "invalid input";

		Graph graph;
		graph.setEdgesNumber(edges_number);
		graph.setVerteicesNumber(verteices_number);
		graph.MakeEmptyGraph();


		for (int i = 1; i <= edges_number; ++i)
		{
			int v1, v2;
			cin >> v1 >> v2;

			try
			{
				if (v1 > verteices_number || v1 < 1 || v2 > verteices_number || v2 < 1)
				{
					throw "invalid input";
				}
			}
			catch (const char* error)
			{
				cout << error << endl;
				exit(1);
			}
			graph.AddEdge(v1, v2);
		}
		graph.MakeSuperGraph(verteices_number, edges_number); //by reference 
		cout << verteices_number << " " << edges_number << endl;

	}
	catch (const char* error)
	{
		cout << error << endl;
		exit(1);
	}

	return 0;
}

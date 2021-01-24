#include <iostream>
#include"Graph.h"
#include"File.h"
using namespace std;

int main()
{
	File file("input.txt");
	Graph graph = file.loadTextToGraph();

	graph.print();
	cout << graph.isReachable("BSFS", "NDK") << endl; // prints 1 if it is possible to go from BSFS to NDK
	cout << graph.isReachableToAllNodes("BSFS") << endl; // prints 1 if it is possible to go everywhere from BSFS
	
	map<string, string> deadEnds = graph.findDeadEnds(); // prints the streets which are dead ends
	if (deadEnds.size() == 0) {
		cout << "Nqma zaduneni ulici!" << endl;
	}
	map<string, string>::iterator it = deadEnds.begin();
	for (; it != deadEnds.end(); it++)
	{
		cout << it->first << " -> " << it->second << endl;
	}

	cout << graph.isCyclicFromNode("RuskiPametnik") << endl; // prints 1 if there is a cycle starting from RuskiPametnik
	list<string> closedNodes;
	closedNodes.push_back("NDK"); // we close the node NDK
	graph.getShortestPaths("Popa", "RuskiPametnik"); // finds the shortest path from Popa to RuskiPametnik
	cout << endl;
	graph.getShortestPaths("Popa", "RuskiPametnik", closedNodes); // finds the shortest path from Popa to RuskiPametnik when there are closed nodes
}

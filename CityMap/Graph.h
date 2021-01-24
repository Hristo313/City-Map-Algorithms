#pragma once
#include <map>
#include <list>
#include <string>
#include <queue>
#include <vector>
#include <iostream>
class Graph
{
private:
	int V;
	std::map<int, std::string> nodes;
	std::list<std::pair<int, int>>* edges;

	int searchKeyInMap(std::string city);
	std::list<std::pair<int, int>> searchInEdges(int toSearch);

	void shortestPathAlgorithm(int, int, bool*, std::vector<int>, int&, int&, std::vector<std::pair<std::vector<int>, int>>&);
	void bubbleSort(std::vector<std::pair<std::vector<int>, int>>&);
	void swap(std::pair<std::vector<int>, int>*, std::pair<std::vector<int>, int>*);
	void deleteNodes(std::vector<int>);
	bool isCyclicUtil(int, bool*, bool*);
	int countPaths();

public:
	Graph(int n);
	Graph(int n, std::map<int, std::string> nodes, std::list<std::pair<int, int>>* edges);
	Graph(const Graph&);
	Graph& operator = (const Graph&);
	~Graph();
	void addNode(int, std::string);
	void addPath(int a, int b, int weigth);
	void print();
	bool isReachable(std::string, std::string);
	bool isReachableToAllNodes(std::string);
	std::map<std::string, std::string> findDeadEnds();
	void getShortestPaths(std::string, std::string);
	void getShortestPaths(std::string, std::string, std::list<std::string>);
	bool isCyclicFromNode(std::string);
};

